#include "Frame.hpp"
//Construtor para métodos não estáticos
Frame::Frame(Objeto *objeto, string nomeMetodo, string descritorMetodo)
{

   /* for (int i = 0; i < arguments.size(); i++) {
		variaveisLocais[i] = argumentos[i];
	}*/

	pc = 0;
	method_info *metodoAux = (method_info *)objeto->javaClass->getMetodo(nomeMetodo, descritorMetodo);
	assert(metodoAux != NULL);
	if(objeto->instancia != NULL)
	{
		assert((metodoAux->getAccessFlags() & 0x0008) == 0); // o método não pode ser estático
	}
	else
	{
		assert((metodoAux->getAccessFlags() & 0x0008) != 0); // o método precisa ser estático
	}
	metodo = metodoAux;
	pegarAtributos();
}

void Frame::pegarAtributos()
{
	vector<cp_info*> constantPool = objeto->javaClass->getConstantPool();
	vector<attribute_info *> attributesAux = metodo->getAttributes();

	codeAttribute = NULL;
	exceptionsAttribute = NULL;

	for (int i = 0; i < metodo->getAttributesCount(); i++) {

		CONSTANT_Utf8_info *attributeName = (CONSTANT_Utf8_info*)(constantPool[attributesAux[i]->getAttributeNameIndex()-1]);

		if ((*attributeName) == "Code") {

			codeAttribute = (Code_attribute*)(attributesAux[i]);

			if (exceptionsAttribute != NULL) break;

		}

		else if (*attributeName == "Exceptions") {

			exceptionsAttribute = (Exceptions_attribute*)(attributesAux[i]);

			if (codeAttribute != NULL) break;
		}
	}
}

Valor Frame::getValorVariavelLocal(uint32_t indice) {

	if (indice >= codeAttribute->getMaxLocals()) {

		cerr <<"Tentativa de acesso a variavel local inexistente" << endl;
		exit(1);

	}

	return variaveisLocais[indice];
}

void Frame::mudarVariavelLocal(Valor valorDaVariavel, uint32_t indice) {

	if (indice >= codeAttribute->getMaxLocals()) {

		cerr << "Tentativa de alteração de variavel local inexistente" << endl;
		exit(1);

	}

	variaveisLocais[indice] = valorDaVariavel;

}

void Frame::empilharOperando(Valor operando) {

	pilhaOperandos.push(operando);

}

Valor Frame::desempilhaOperando() {

	if (pilhaOperandos.size() == 0) {

		cerr << "IndexOutOfBoundsException" << endl;
		exit(1);

	}

	Valor topo = pilhaOperandos.top();

	pilhaOperandos.pop();

	return topo;
}

stack<Valor> Frame::retornaPilhaOperandos()
{

	return pilhaOperandos;

}


void Frame::setaPilhaOperandos(stack<Valor> pilha){

	pilhaOperandos = pilha;

}

uint8_t *Frame::getCode() {

	return codeAttribute->getCode() + pc;

}

uint16_t Frame::tamanhoVetorVariaveis() {

	return codeAttribute->getMaxLocals();

}

uint32_t Frame::tamanhoCode() {

	return codeAttribute->getCodeLength();

}

void Frame::incrementaPC(int32_t offset){
	pc = pc + offset;
}

int32_t Frame::getPC(){

return pc;

}

Objeto getObjeto(){

    return objeto;

}

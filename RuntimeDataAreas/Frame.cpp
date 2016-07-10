#include "Frame.hpp"
#include "Erro.hpp"

//#define DEBUG
//Construtor para métodos estáticos
Frame::Frame(JavaClass *javaClass, string nomeMetodo, string descritor, RuntimeDataArea *runtimeDataArea)
{
#ifdef DEBUG
	cout<< "Frame::Frame(JavaClass *javaClass, string nomeMetodo, string descritor, RuntimeDataArea *runtimeDataArea)"<< endl;
#endif
	pc=0;
	this->javaClass= javaClass;
#ifdef DEBUG
	cout<< "\t1"<< endl;
#endif
	objeto=NULL;
#ifdef DEBUG
	cout<< "\t2"<< endl;
#endif
	method_info *metodoAux = BuscarMetodo(javaClass, nomeMetodo, descritor, runtimeDataArea);
#ifdef DEBUG
	cout<< "\t3"<< endl;
#endif
	assert(metodoAux != NULL);
#ifdef DEBUG
	cout<< "\t4"<< endl;
#endif
	metodo= metodoAux;
#ifdef DEBUG
	cout<< "\t5"<< endl;
#endif
	assert(metodo->FlagAtivada(METHOD_STATIC));
#ifdef DEBUG
	cout<< "\t6"<< endl;
#endif
	pegarAtributos(javaClass);
#ifdef DEBUG
	cout<< "Retornando"<< endl;
#endif
}

Frame::Frame(JavaClass *javaClass, string nomeMetodo, string descritor, vector<Valor> argumentos, RuntimeDataArea *runtimeDataArea)
{
#ifdef DEBUG
	cout<< "Frame::Frame(JavaClass *javaClass, string nomeMetodo, string descritor, RuntimeDataArea *runtimeDataArea)"<< endl;
#endif
	pc=0;
	this->javaClass= javaClass;
#ifdef DEBUG
	cout<< "\t1"<< endl;
#endif
	objeto=NULL;
#ifdef DEBUG
	cout<< "\t2"<< endl;
#endif
	method_info *metodoAux = BuscarMetodo(javaClass, nomeMetodo, descritor, runtimeDataArea);
#ifdef DEBUG
	cout<< "\t3"<< endl;
#endif
	assert(metodoAux != NULL);
#ifdef DEBUG
	cout<< "\t4"<< endl;
#endif
	metodo= metodoAux;
#ifdef DEBUG
	cout<< "\t5"<< endl;
#endif
	assert(metodo->FlagAtivada(METHOD_STATIC));
#ifdef DEBUG
	cout<< "\t6"<< endl;
#endif
	for(unsigned int cont = 0; cont < argumentos.size(); cont++)
	{
		variaveisLocais[cont]= argumentos[cont];
	}
	pegarAtributos(javaClass);
#ifdef DEBUG
	cout<< "Retornando"<< endl;
#endif
}


Frame::Frame(ObjetoInstancia *objeto, string nomeDoMetodo, string descritorMetodo, vector<Valor> argumentos, RuntimeDataArea *runtimeDataArea)
{
	pc =0;
	this->objeto= objeto;
	this->javaClass= objeto->ObterJavaClass();
	for (unsigned int cont = 0; cont < argumentos.size(); cont++) {
		variaveisLocais[cont] = argumentos[cont];
	}
	
	metodo = BuscarMetodo(objeto->ObterJavaClass(), nomeDoMetodo, descritorMetodo, runtimeDataArea);
	assert(metodo != NULL);
	assert(!metodo->FlagAtivada(METHOD_STATIC));
	
	pegarAtributos();
}

Frame::Frame(ObjetoInstancia *objeto, JavaClass *classe, string nomeDoMetodo, string descritorMetodo, vector<Valor> argumentos, RuntimeDataArea *runtimeDataArea)
{
	pc =0;
	this->objeto= objeto;
	this->javaClass= objeto->ObterJavaClass();
	for (unsigned int cont = 0; cont < argumentos.size(); cont++) {
		variaveisLocais[cont] = argumentos[cont];
	}
	
	metodo = BuscarMetodo(classe, nomeDoMetodo, descritorMetodo, runtimeDataArea);
	assert(metodo != NULL);
	assert(!metodo->FlagAtivada(METHOD_STATIC));
	
	pegarAtributos();
}

void Frame::pegarAtributos(JavaClass *classe)
{
	if(objeto == NULL && classe == NULL)
	{
		throw new Erro ("javaClass e objeto não instanciado", "Frame", "pegarAtributos");
	}
	JavaClass *javaClass= (classe ==NULL)? ((ObjetoInstancia*)objeto)->ObterJavaClass() : classe;
#ifdef DEBUG
	cout<< "Frame::pegarAtributos()" << endl;
#endif
	if(objeto != NULL)
	{
		if(objeto->ObterTipoObjeto() != TipoObjeto::INSTANCIA)
		{
			throw new Erro ("Isso não é uma instância de objeto!", "Frame", "pegarAtributos");
		}
	}
#ifdef DEBUG
	cout<< "\t1"<< endl;
#endif
	vector<cp_info*> constantPool = javaClass->getConstantPool();
#ifdef DEBUG
	cout<< "\t2"<< endl;
#endif
	cout<<"pegando atributos" << endl;
#ifdef DEBUG
	cout<< "\t3"<< endl;
#endif
	vector<attribute_info *> attributesAux = metodo->getAttributes();
#ifdef DEBUG
	cout<< "\t4"<< endl;
#endif
	cout<<"pegando atributos" << endl;
#ifdef DEBUG
	cout<< "\t5"<< endl;
#endif
	codeAttribute = NULL;
	exceptionsAttribute = NULL;
#ifdef DEBUG
	cout<< "\t6"<< endl;
#endif

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
#ifdef DEBUG
	cout<< "Retornando"<< endl;
#endif
}

Valor Frame::getValorVariavelLocal(uint32_t indice) {

	if (indice >= codeAttribute->getMaxLocals()) {
		throw new Erro("Tentativa de acesso a variavel local inexistente", "Frame", "getValorVariaavelLocal");

	}

	return variaveisLocais[indice];
}

void Frame::mudarVariavelLocal(Valor valorDaVariavel, uint32_t indice) {

	if (indice >= codeAttribute->getMaxLocals()) {
		throw new Erro("Tentativa de alteração de variavel local inexistente", "Frame", "mudarVariavelLocal");
	}

	variaveisLocais[indice] = valorDaVariavel;

}

void Frame::empilharOperando(Valor operando) {

	pilhaOperandos.push(operando);

}

Valor Frame::desempilhaOperando() {

	if (pilhaOperandos.size() == 0) {
		throw new Erro("IndexOutOfBoundsException(Valor Frame::desempilhaOperando()");
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
void Frame::alteraPC(int32_t novoPC){
	pc = novoPC;
}

int32_t Frame::getPC(){

return pc;

}

Objeto* Frame::getObjeto(){

	return objeto;

}

method_info* Frame::BuscarMetodo(JavaClass* javaClass, string nomeMetodo, string descritor, RuntimeDataArea *runtimeDataArea)
{
	method_info* retorno;
	JavaClass *classeComMetodo= javaClass;
	//procurar em classes pai
	do
	{
		retorno= (method_info*)classeComMetodo->getMetodo(nomeMetodo, descritor);
		if(retorno != NULL)
		{//Bingo!
			return retorno;
		}
		if(javaClass->ObterSuperClasse()!=0)
		{
			string nomeDoPai= javaClass->getUTF8(javaClass->ObterSuperClasse());
			classeComMetodo= runtimeDataArea->CarregarClasse(nomeDoPai);
		}
		else
		{
			classeComMetodo= NULL;
		}
	}
	while(classeComMetodo!= NULL);
	return NULL;
}

JavaClass *Frame::ObterJavaClass(void)
{
	return javaClass;
}


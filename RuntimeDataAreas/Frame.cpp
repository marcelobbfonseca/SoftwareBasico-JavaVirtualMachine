
//Construtor para métodos não estáticos
Frame::Frame(Objeto objeto, string nomeMetodo, string descritorMetodo, vector<Value> argumentos){
{

    for (int i = 0; i < arguments.size(); i++) {
        variaveisLocais[i] = arguments[i];
    }

    pc = 0;

    method_info *metodoAux = objeto->javaClass.getMetodoChamado(nomeMetodo, descritorMetodo);
    assert(method != NULL);
    metodo = *metodoAux;
    if(objeto.instancia != NULL){
        assert((metodo.access_flags & 0x0008) == 0); // o método não pode ser estático
        }
    else{
        assert((_method.access_flags & 0x0008) != 0); // o método precisa ser estático
    }

    pegarAtributos();
}

Frame::~Frame() {

}

void Frame::pegarAtributos() {
    vector<cp_info*> constantPool = objeto->javaClass.getConstantPool();

    codeAttribute = NULL;
    exceptionsAttribute = NULL;

    for (int i = 0; i < _method.attributes_count; i++) {

        attribute_info *attribute_aux = &(method.attributes[i]);
        CONSTANT_Utf8_info *attributeName = (CONSTANT_Utf8_info*)(constantPool[attribute_aux->GetAttributeNameIndex()-1]);

        if ((*attributeName) == "Code") {

            codeAttribute = &(attributeAux->info.code_info);

            if (exceptionsAttribute != NULL) break;

        }

        else if (attrName == "Exceptions")) {

            exceptionsAttribute = &(attribute_aux->info.exceptions_info);

            if (codeAttribute != NULL) break;
        }
    }
}

Valor Frame::getValorVariavelLocal(uint32_t indice) {

    if (indice >= codeAttribute->max_locals) {

        cerr <<"Tentativa de acesso a variavel local inexistente" << endl;
        exit(1);

    }

    return variaveisLocais[indice];
}

void Frame::mudarVariavelLocal(Valor valorDaVariavel, uint32_t indice) {

    if (indice >= _codeAttribute->max_locals) {

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

    return top;
}

stack<Valor> Frame::retornaPilhaOperandos(){}

    return pilhaOperandos;

}


void Frame::setaPilhaOperandos(stack<Valor> pilha){

    pilhaOperandos = pilha;

}

uint8_t* Frame::getCode(uint32_t endereco) {

    return codeAttribute->code + endereco;

}

uint16_t Frame::tamanhoVetorVariaveis() {

	return codeAttribute->max_locals;

}

uint32_t Frame::tamanhoCode() {

	return codeAttribute->code_length;

}

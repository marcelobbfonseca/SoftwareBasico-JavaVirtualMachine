Class Frame
{
	private:
		map<uint32_t,Valor> variaveisLocais;
		method_info *metodos;
		uint32_t PC;
		pilhaOperandos stack<Valor>;
		Objeto *objeto;
        //Ponteiro para o atributo Code referente ao método.
        Code_attribute *_codeAttribute;
        //Atributo Exceptions referente ao método.
        Exceptions_attribute *_exceptionsAttribute;

        void Frame::pegarAtributos();

	public:
		Frame(Objeto objeto, string nomeMetodo, string descritorMetodo, vector<Value> argumentos);
		Valor getValorVariavelLocal(uint32_t indice);
		void mudarVariavelLocal(Valor valorDaVariavel, uint32_t indice);
		void empilharOperando(Valor operando);
		Valor desempilhaOperando();
		stack<Valor> retornaPilhaOperandos();
		void setaPilhaOperandos(stack<Valor> pilha);
		uint8_t* getCode(uint32_t endereco);
        uint16_t Frame::tamanhoVetorVariaveis();
        uint32_t Frame::tamanhoCode() ;
}

class Objeto {

    DadosDaInstancia *instancia;
    JavaClass *classe;

};


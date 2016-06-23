#ifndef FRAME_H
#define FRAME_H


class Frame{

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
        
        // Obter um ponteiro para a pool de constantes referente ao frame atual.
		cp_info *cpInfo;        


        void Frame::pegarAtributos();

	public:
		//Construtor para metodos nao estaticos
		Frame(Objeto objeto, string nomeMetodo, string descritorMetodo, vector<Value> argumentos);
		//Construtor para metodo estatico
		Frame(string nomeMetodo, string descritorMetodo, vector<Value> argumentos = vector<Value>());


		Valor getValorVariavelLocal(uint32_t indice);
		void mudarVariavelLocal(Valor valorDaVariavel, uint32_t indice);
		void empilharOperando(Valor operando);
		Valor desempilhaOperando();
		stack<Valor> retornaPilhaOperandos();
		void setaPilhaOperandos(stack<Valor> pilha);
		uint8_t* getCode(uint32_t endereco);
        uint16_t Frame::tamanhoVetorVariaveis();
        uint32_t Frame::tamanhoCode() ;
        ~Frame();
};

class Objeto {

    DadosDaInstancia *instancia;
    JavaClass *classe;

};

#endif
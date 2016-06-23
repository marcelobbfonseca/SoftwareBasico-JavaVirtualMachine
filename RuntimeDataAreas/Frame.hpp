#ifndef FRAME_H
#define FRAME_H


class Frame{

	public:
	Frame();
	~Frame();
	
	private:
		map <uint32_t,Valor> VariaveisLocais;
		method_info *metodo;
		uint32_t PC;
		pilhaOperandos stack<Valor>;
		Objeto *objeto;
        //Ponteiro para o atributo Code referente ao método.
        Code_attribute *_codeAttribute;
        //Atributo Exceptions referente ao método.
        Exceptions_attribute *_exceptionsAttribute;
        
        // Obter um ponteiro para a pool de constantes referente ao frame atual.
		cp_info *cpInfo;        


};

class Objeto {

    DadosDaInstancia *instancia;
    JavaClass *classe;

};

#endif
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

	public:
		Frame();
}

class Objeto {

    DadosDaInstancia *instancia;
    JavaClass *classe;

};


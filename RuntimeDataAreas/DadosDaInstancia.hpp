#include<map>
#include"JavaClass.hpp"
#include"Tipos.h"

class DadosDaInstancia{
	public:
		DadosDaInstancia(JavaClass *javaClass);
	private:
		map<string, Valor> fieldsInstancia;
};

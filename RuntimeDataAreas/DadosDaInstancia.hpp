#ifndef DADOS_DA_INSTANCIA_HPP
#define DADOS_DA_INSTANCIA_HPP

#include<iostream>
#include<map>
#include"JavaClass.hpp"
#include"Tipos.h"

class DadosDaInstancia{
	public:
		DadosDaInstancia(JavaClass *javaClass);
	private:
		map<string, Valor> fieldsInstancia;
};

#endif

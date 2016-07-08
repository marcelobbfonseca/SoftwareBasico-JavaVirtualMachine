#ifndef DADOS_DA_INSTANCIA_HPP
#define DADOS_DA_INSTANCIA_HPP

#include<iostream>
#include<map>
#include"JavaClass.hpp"
#include"Tipos.hpp"

class DadosDaInstancia{
	public:
		DadosDaInstancia(JavaClass *javaClass);
		Valor getValorDoField(string nomeField);
	private:
		map<string, Valor> fieldsInstancia;
};

#endif

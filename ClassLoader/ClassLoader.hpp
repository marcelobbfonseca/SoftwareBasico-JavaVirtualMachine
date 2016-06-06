#include<string>
#include
#include"JavaClass.hpp"

#ifndef CLASSLOADER_HPP
#define CLASSLOADER_HPP

class ClassLoader
{
	private:
		std::map<std::string, JavaClass> classesCarregadas;
	public:
		DadosDaClasse CarregarClasse(string nomeClasse);
		ClassLoader();
		SetRuntimeDataArea(RuntimeDataArea *runtimeDataArea);
//		GetMetodos(string nomeDaClasse);
		//a descobrir
}
	
class DadosDaClasse
{
	private:
		string nomeDaClasse;
		vector<stributo> atributos;
		vector<metodo> metodos
	public:
		
}

class Metodo
{
	private:
		string nomeMetodo;
		vector<uint8_t> bytecode;
		vector<atributo> variaveisLocais;
		TipoDeRetorno tipoDeRetorno;
		vector<atributo> argumentos;
	public:
		
}

#endif

#include<string>
#include
#include"JavaClass.hpp"

#ifndef CLASSLOADER_HPP
#define CLASSLOADER_HPP

class ClassLoader
{
	private:
		std::map<std::string, JavaClass *> classesCarregadas;
	public:
		JavaClass* CarregarClasse(string nomeClasse);
		ClassLoader();
		SetRuntimeDataArea(RuntimeDataArea *runtimeDataArea);
//		GetMetodos(string nomeDaClasse);
		//a descobrir
};
	

#endif

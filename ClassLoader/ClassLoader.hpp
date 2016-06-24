#ifndef CLASSLOADER_HPP
#define CLASSLOADER_HPP
#include<string>
#include<map>
#include"JavaClass.hpp"
#include"RuntimeDataArea.hpp"

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

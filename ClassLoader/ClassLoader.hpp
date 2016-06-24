#ifndef CLASSLOADER_HPP
#define CLASSLOADER_HPP
#include<string>
#include<map>
#include"JavaClass.hpp"
#include"RuntimeDataArea.hpp"

#ifndef RUNTIMEDATAAREA
class RuntimeDataArea;
#endif

#define CLASSLOADER
class ClassLoader
{
	private:
		std::map<std::string, JavaClass *> classesCarregadas;
		RuntimeDataArea *runtimeDataArea;
	public:
		JavaClass* CarregarClasse(string nomeClasse);
		ClassLoader();
		void SetRuntimeDataArea(RuntimeDataArea *runtimeDataArea);
//		GetMetodos(string nomeDaClasse);
		//a descobrir
};
//#endif

#endif

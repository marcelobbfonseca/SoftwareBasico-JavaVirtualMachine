#ifndef RUNTIMEDATAAREA_HPP
#define RUNTIMEDATAAREA_HPP

#include<stack>
#include<map>
#include"Frame.hpp"
#include"ExecutionEngine.hpp"
#include"ClassLoader.hpp"
#include "Heap.cpp"

#ifndef CLASSLOADER
class ClassLoader;
#endif
#ifndef EXECUTIONENGINE
class ExecutionEngine;
#endif

#define RUNTIMEDATAAREA
class RuntimeDataArea
{
	private:
//		map<string, DadosDaClasse> InformacoesDeClasses;
//Necessário?	map<string, JavaClass*> classes;/
		stack<Frame> PilhaJVM;
		ClassLoader *classLoader;
		ExecutionEngine *executionEngine;

		//a descobrir
	public:
		RuntimeDataArea();
		void SetClassLoader(ClassLoader *classLoader);
		void SetExecutionEngine(ExecutionEngine *executionEngine);
		bool MetodoExiste(string nomeClasse, string nomeMetodo, string descritor);
		void empilharFrame(Frame frame);
		JavaClass* CarregarClasse(const string &nomeDaClasse);
		Frame topoPilha();
		Frame desempilhaFrame();

		//a descobrir
};


#endif

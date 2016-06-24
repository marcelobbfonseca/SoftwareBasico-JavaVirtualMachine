#ifndef RUNTIMEDATAAREA_HPP
#define RUNTIMEDATAAREA_HPP

#include<stack>
#include<map>
#include"Frame.hpp"
#include"ExecutionEngine.hpp"
#include"ClassLoader.hpp"
#include "Heap.cpp"

class RuntimeDataArea
{
	private:
//		map<string, DadosDaClasse> InformacoesDeClasses;
//Necessário?	map<string, JavaClass*> classes;/
		JavaClass* CarregarClasse(const string &nomeDaClasse);
		stack<Frame> PilhaJVM;

		//a descobrir
	public:
		RuntimeDataArea();
		void SetClassLoader(ClassLoader *classLoader);
		void SetExecutionEngine(ExecutionEngine *executionEngine);
		bool MetodoExiste(string nomeClasse, string nomeMetodo, string descritor);
		void empilharFrame(Frame frame);
		Frame topoPilha();
		Frame desempilhaFrame();

		ClassLoader classLoader;
		ExecutionEngine executionEngine;
		//a descobrir
};

#endif

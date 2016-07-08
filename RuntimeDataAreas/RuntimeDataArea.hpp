#ifndef RUNTIMEDATAAREA_HPP
#define RUNTIMEDATAAREA_HPP

#include<stack>
#include<map>
#include"Frame.hpp"
#include"ExecutionEngine.hpp"
#include"ClassLoader.hpp"

#ifndef CLASSLOADER
class ClassLoader;
#endif
#ifndef EXECUTIONENGINE
class ExecutionEngine;
#endif
#ifndef FRAME
class Frame;
#endif

#define RUNTIMEDATAAREA
class RuntimeDataArea
{
	private:
//		map<string, DadosDaClasse> InformacoesDeClasses;
		map<string, JavaClass*> classes;
		ClassLoader *classLoader;
		ExecutionEngine *executionEngine;
		stack<Frame*> pilhaJVM;
		//a descobrir
	public:
		RuntimeDataArea();
		void SetClassLoader(ClassLoader *classLoader);
		void SetExecutionEngine(ExecutionEngine *executionEngine);
		bool MetodoExiste(string nomeClasse, string nomeMetodo, string descritor);
		void empilharFrame(Frame *frame);
		int ObterTamanhoDaPilhaDeFrames(void);
		JavaClass* CarregarClasse(const string &nomeDaClasse);
		Frame *topoPilha();
		void desempilharFrame();

		//a descobrir
};


#endif

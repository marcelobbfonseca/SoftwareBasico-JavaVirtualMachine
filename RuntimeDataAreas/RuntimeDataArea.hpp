#ifndef RUNTIMEDATAAREA_HPP
#define RUNTIMEDATAAREA_HPP

#include<stack>
#include<map>
#include"Frame.hpp"
#include"ExecutionEngine.hpp"
#include"ClassLoader.hpp"
#include"Tipos.h"

class RuntimeDataArea
{
	private:
//		map<string, DadosDaClasse> InformacoesDeClasses;
		map<string, JavaClass*> classes;//Necessário?
		map<JavaClass*, vector<Objeto*>  listaDeObjetos;//Necessário?
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
		ExecutionEngine ExecutionEngine;
		//a descobrir
}

class Heap {


private:

    Heap(Heap const&); //não permite implementação cópia
    void operator=(Heap const&); // não permite atribuição

    vector<Objeto*> vetorObjetos;

public:

    Heap();

    void Heap::adcObjeto(Objeto *objeto) {
        vetorObjetos.push_back(objeto);
    }
};


#endif

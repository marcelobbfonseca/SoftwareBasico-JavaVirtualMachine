#ifndef RUNTIMEDATAAREA_HPP
#define RUNTIMEDATAAREA_HPP

class RuntimeDataArea
{
	private:
//		map<string, DadosDaClasse> InformacoesDeClasses;
		map<string, JavaClass*> classes;
		map<JavaClass*, Objeto*> listaDeObjetos;
		stack<Frame> pilhaFrames;

		JavaClass* CarregarClasse(const string &nomeDaClasse);
		JavaClass* ObterDadosDaClasse(const string &nomeDaClasse);
		//a descobrir
	public:
		RuntimeDataArea();
		void SetClassLoader(ClassLoader *classLoader);
		void SetExecutionEngine(ExecutionEngine *executionEngine);
		/*A decidir*/ ObterInstrucao(string nomeDaClasse, char * nomeMetodo, offset);
		bool MetodoExiste(string nomeClasse, string nomeMetodo, string descritor);
		//a descobrir
}

#endif

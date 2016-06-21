#ifndef RUNTIMEDATAAREA_HPP
#define RUNTIMEDATAAREA_HPP

class RuntimeDataArea
{
	private:
//		map<string, DadosDaClasse> InformacoesDeClasses;
		map<string, DadosDaClasse*> classes;
		map<DadosDaClasse*, Objeto*> listaDeObjetos;
		stack<Frame> pilhaFrames;
		MethodArea methodArea;

		DadosDaClasse* CarregarClasse(const string &nomeDaClasse);
		DadosDaClasse* ObterDadosDaClasse(const string &nomeDaClasse);
		//a descobrir
	public:
		RuntimeDataArea();
		SetClassLoader(ClassLoader *classLoader);
		SetExecutionEngine(ExecutionEngine *executionEngine);
		 ObterInstrucao(string nomeDaClasse, char * nomeMetodo, offset);
		bool MetodoExiste(string nomeClasse, string nomeMetodo, string descritor);
		//a descobrir
}

#endif

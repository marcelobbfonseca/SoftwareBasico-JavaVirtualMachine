#ifndef RUNTIMEDATAAREA_HPP
#define RUNTIMEDATAAREA_HPP

class RuntimeDataArea
{
	private:
//		map<string, DadosDaClasse> InformacoesDeClasses;
		map<DadosDaClasse*, Objeto*> listaDeObjetos;
		stack<Frame> frames;
		MethodArea methodArea;
		//a descobrir
	public:
		RuntimeDataArea();
		SetClassLoader(ClassLoader *classLoader);
		SetExecutionEngine(ExecutionEngine *executionEngine);
		 ObterInstrucao(string nomeDaClasse, char * nomeMetodo, offset);
		//a descobrir
}

Class Frame
{
	private:
		vector<atributo> VariaveisLocais;
		Metodo *metodo;
		int PC;
		PilhaOperandos pilha;
		ObjetoTratado *obj;
		vector<excecao> TabelaDeExcecoes;
	public:
		Frame();
}
#endif

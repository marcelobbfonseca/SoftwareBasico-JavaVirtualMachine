#ifndef RUNTIMEDATAAREA_HPP
#define RUNTIMEDATAAREA_HPP

class RuntimeDataArea
{
	private:
		map<string, DadosDaClasse> InformacoesDeClasses;
		map<DadosDaClasse*, Objeto*> listaDeObjetos;
		stack<Frame> frames;
		//a descobrir
	public:
		RuntimeDataArea();
		SetClassLoader(ClassLoader *classLoader);
		SetExecutionEngine(ExecutionEngine *executionEngine);
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
		
}
#endif

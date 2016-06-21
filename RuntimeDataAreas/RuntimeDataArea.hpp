#ifndef RUNTIMEDATAAREA_HPP
#define RUNTIMEDATAAREA_HPP

class RuntimeDataArea
{
	private:
//		map<string, DadosDaClasse> InformacoesDeClasses;
		map<DadosDaClasse*, Objeto*> listaDeObjetos;
		stack<Frame> pilhaFrames;
		MethodArea methodArea;
		//a descobrir
	public:
		RuntimeDataArea();
		SetClassLoader(ClassLoader *classLoader);
		SetExecutionEngine(ExecutionEngine *executionEngine);
		//a descobrir
}

#endif

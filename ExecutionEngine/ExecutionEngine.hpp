#ifndef EXECUTIONENGINE_HPP
#define EXECUTIONENGINE_HPP
#include<vector>
#include"RuntimeDataArea.hpp"

#ifndef RUNTIMEDATAAREA
class RuntimeDataArea;
#endif

#define EXECUTIONENGINE
class ExecutionEngine
{
	private:

		void (*vetorDePonteirosParaFuncao[250])();
		RuntimeDataArea *runtimeDataArea;

	public:
		void SetRuntimeDataArea(RuntimeDataArea *runtimeDataArea);
		void Play(string classComMain);

};
//#endif

#endif

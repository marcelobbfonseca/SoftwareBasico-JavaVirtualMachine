#include"ExecutionEngine.hpp"
void ExecutionEngine::Play(string classComMain)
{

    uint8_t *instruction;
    Objeto *obj = new Objeto();

    obj->classe = runtimeDataArea->CarregarClasse(classComMain);
    obj->instancia = NULL;

    runtimeDataArea->empilharFrame(new Frame(obj, "main", "([Ljava/lang/String;)V"));
    runtimeDataArea->empilharFrame(new Frame(obj, "<init>"),"()V");

	do
	{

        instruction = runtimeDataArea->topoPilha().getCode()];
		vetorDePonteirosParaFuncao[instrucao];

	}
	while(runtimeDataArea.PilhaJVM.size > 0);
}









void ExecutionEngine::Play(string classComMain)
{
    uint8_t *instruction

    runtimeDataArea->empilharFrame(new Frame(classComMain, "main", "([Ljava/lang/String;)V"));
    runtimeDataArea->empilharFrame(new Frame(classComMain, "<init>"),"()V");

	do
	{

        instruction = runtimeDataArea.topoPilha().pc;
		vetorDePonteirosParaFuncao[instrucao];

	}
	while(runtimeDataArea.frameStack.size > 0);
}









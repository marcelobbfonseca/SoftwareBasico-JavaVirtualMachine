void ExecutionEngine::Play(string classComMain)
{

    uint8_t *instruction
    new Objeto() obj;

    obj->classe = runtimeDataArea.ClassLoader.carregarClasse(classComMain);
    obj->instancia = NULL;

    runtimeDataArea->empilharFrame(new Frame(obj, "main", "([Ljava/lang/String;)V"));
    runtimeDataArea->empilharFrame(new Frame(obj, "<init>"),"()V");

	do
	{

        instruction = runtimeDataArea.topoPilha().getCode(pc)];
		vetorDePonteirosParaFuncao[instrucao];

	}
	while(runtimeDataArea.PilhaJVM.size > 0);
}









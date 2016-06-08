void ExecutionEngine::Play(string classComMain)
{
	int offset=0;
	int proximaInstrucao = runtimeDataArea.ObterInstrucao(classComMain, "main", offset);
	do
	{
		vetorDePonteirosParaFuncao[proximaInstrucao];
		offset++;
		proximaInstrucao = runtimeDataArea.ObterInstrucao(classComMain, "main", offset);
	}
	while(indiceDaProximaInstrucao == "return");
}



ClassLoader::CarregarClasse(string nomeClasse)
{
	//ler a porra toda e mandar pro DataArea
	if(!classesCarregadas.Existe(nomeClasse))
	{
		map[nomeClasse] = *(new JavaClass(nomeClasse));
	}
	//gerar dados da classe retornar o DadosDaClasse

}


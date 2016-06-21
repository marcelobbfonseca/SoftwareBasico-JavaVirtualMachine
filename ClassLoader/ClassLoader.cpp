
JavaClass* ClassLoader::CarregarClasse(string nomeClasse)
{
	//Se não tiver.class no nome da classe .class é adicionado
	if(!nomeClasse.substr(nomeClasse.length() - 6)== ".class")
	{
		nomeClasse+= ".class";
	}
	//ler a porra toda e mandar pro DataArea
	if(!classesCarregadas.Existe(nomeClasse))
	{
		map[nomeClasse] = (new JavaClass(nomeClasse));
	}
	//gerar dados da classe retornar o DadosDaClasse
	return classesCarregadas[nomeClasse];

}


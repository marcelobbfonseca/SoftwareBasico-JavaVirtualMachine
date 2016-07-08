#include"ClassLoader.hpp"

JavaClass* ClassLoader::CarregarClasse(string nomeClasse)
{
/*	//ler a porra toda e mandar pro DataArea
	if(classesCarregadas.find(nomeClasse) == classesCarregadas.end()){

		classesCarregadas[nomeClasse] = (new JavaClass(nomeClasse));

	}
	//gerar dados da classe retornar o DadosDaClasse
	return classesCarregadas[nomeClasse];
*/
	static bool primeiraVezQueCarrega= true;
	if(primeiraVezQueCarrega)
	{
		if(nomeClasse.find('\\') != string::npos || nomeClasse.find('/') != string::npos)
		{
			
		}
		primeiraVezQueCarrega= false;
	}
	JavaClass *retorno;
	try
	{
		retorno= new JavaClass(nomeClasse);
		return retorno;
	}
	catch(Erro *err)
	{
		cerr<< "---------------------------------------------------------------" << endl;
		cerr<< "Erro no carregamento da classe " << nomeClasse << endl;
		cerr<< err->GetMensagem() << endl;
		cerr<< "Supondo que esta tudo bem..." << endl;
		cerr<< "---------------------------------------------------------------" << endl;
	}
	return NULL;
}

ClassLoader::ClassLoader(void)
{
	caminho = "";
}

void ClassLoader::SetRuntimeDataArea(RuntimeDataArea *runtimeDataArea)
{
	this->runtimeDataArea= runtimeDataArea;
}

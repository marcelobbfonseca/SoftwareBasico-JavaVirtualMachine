#include"ClassLoader.hpp"

JavaClass* ClassLoader::CarregarClasse(string nomeClasse)
{
	static bool primeiraVezQueCarrega= true;
	if(primeiraVezQueCarrega)
	{
		if(nomeClasse.find('\\') != string::npos || nomeClasse.find('/') != string::npos)
		{
			caminho= nomeClasse;
			while(caminho[caminho.length()-1] != '/' && caminho[caminho.length()-1] != '\\')
			{
				caminho= caminho.substr(0, caminho.length()-1);
			}
		}
		cout<<"-----------Caminho: " << caminho << "--------------------"<< endl;
		primeiraVezQueCarrega= false;
	}
	else
	{
		if(nomeClasse.find("java/")== string::npos)
		{
			nomeClasse= caminho + nomeClasse;
		}
	}
	JavaClass *retorno;
	try
	{
		retorno= new JavaClass(nomeClasse);
		return retorno;
	}
	catch(Erro *err1)
	{
		try
		{
			retorno= new JavaClass(nomeClasse);
			return retorno;
		}
	catch(Erro* err2)
	{
		cerr<< "---------------------------------------------------------------" << endl;
		cerr<< "Erro no carregamento da classe " << nomeQueSeraUsado << endl;
		cerr<< err1->GetMensagem() << endl << endl;
		cerr<< "Supondo que esta tudo bem. Farei uma segunda tentativa na pasta do excutavel" << endl << endl;
		cerr<< "Erro no carregamento da classe " << nomeClasse << endl;
		cerr<< err2->GetMensagem() << endl;
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

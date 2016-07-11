#include"ClassLoader.hpp"

JavaClass* ClassLoader::CarregarClasse(string nomeClasse)
{
	static bool primeiraVezQueCarrega= true;
	string nomeQueSeraUsado= nomeClasse;
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
			nomeQueSeraUsado= caminho + nomeQueSeraUsado;
		}
	}
	JavaClass *retorno;
	try
	{
		retorno= new JavaClass(nomeQueSeraUsado);
		return retorno;
	}
	catch(Erro *)
	{
		try
		{
			retorno= new JavaClass(nomeClasse);
			return retorno;
		}
		catch(Erro* err)
		{
			cerr<< "---------------------------------------------------------------" << endl;
			cerr<< "Erro no carregamento da classe " << nomeClasse << endl;
			cerr<< err->GetMensagem() << endl;
			cerr<< "Supondo que esta tudo bem..." << endl;
			cerr<< "---------------------------------------------------------------" << endl;
		}
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

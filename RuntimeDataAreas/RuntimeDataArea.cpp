#include"UtilidadesParaString.hpp"
#include"RuntimeDataArea.hpp"

#define DEBUG

RuntimeDataArea::RuntimeDataArea(void)
{
	
}

JavaClass *RuntimeDataArea::CarregarClasse(const string &nomeDaClasse)
{
	string nomeSemExtensao= nomeDaClasse;
	if(StringUtilidades::TerminaCom(nomeDaClasse, ".class") )
	{
		nomeSemExtensao= StringUtilidades::RemoverNoFinal(nomeSemExtensao, ".class");
	}
	string nomeComExtensao= nomeDaClasse;
	if (!StringUtilidades::TerminaCom(nomeComExtensao, ".class") )
	{
		nomeComExtensao+= ".class";
	}
	string nomeSemExtensaoNemCaminho = nomeDaClasse;
	nomeSemExtensaoNemCaminho = StringUtilidades::RemoverCaminhoEExtensao(nomeSemExtensaoNemCaminho, ".class");
	if(classes.count(nomeSemExtensaoNemCaminho) >0)
	{
		return classes[nomeSemExtensaoNemCaminho];
	}
	JavaClass *temp=classLoader->CarregarClasse(nomeComExtensao);
	if(temp == NULL)
	{
		return NULL;
	}
	classes[nomeSemExtensaoNemCaminho] = temp;
	// adicionando <clinit> da classe (se existir) na stack frame.
	static bool primeiraVez= true;//se for a primeira classe a ser carregada, deixa a execution engine carregar o clinit
	cout<< "chegou ate aqui" << endl;
	if(!primeiraVez)
	{
		if(MetodoExiste(nomeSemExtensao, "<clinit>", "()V"))
		{
	cout<< "chegou ate aqui3" << endl;
			//pseudocodigo:
			string clinit= "<clinit>";
			string V= "()V";
			Frame *novoFrame= new Frame(classes[nomeSemExtensao], clinit, V, this);
			empilharFrame(novoFrame);
		}
	}
	cout<< "chegou ate aqui2" << endl;
	primeiraVez= false;
	if(classes[nomeSemExtensaoNemCaminho]== NULL)
	printf("deu ruim\n");
	return classes[nomeSemExtensaoNemCaminho];
}

void RuntimeDataArea::SetClassLoader(ClassLoader *classLoader)
{
	this->classLoader =classLoader;
}

void RuntimeDataArea::SetExecutionEngine(ExecutionEngine *executionEngine)
{
	this->executionEngine = executionEngine;
}

void RuntimeDataArea::empilharFrame(Frame *frame)
{
#ifdef DEBUG
	printf("RuntimeDataArea::empilharFrame");
	cout <<endl;
	printf("\tframe= %p", (void*)frame);
	cout <<endl;
#endif
	this->pilhaJVM.push(frame);
#ifdef DEBUG
	cout<< "Retornando" << endl;
#endif

}

Frame *RuntimeDataArea::topoPilha()
{
	return (this->pilhaJVM.top());
}

void RuntimeDataArea::desempilharFrame()
{
	if (pilhaJVM.size() == 0)
	{
		throw new Erro("IndexOutOfBoundsException");
	}
	Frame* topo = pilhaJVM.top();
	pilhaJVM.pop();
	delete topo;
	return;
}

bool RuntimeDataArea::MetodoExiste(string nomeClasse, string nomeMetodo, string descritor)
{
	string nomeSemExtensao= nomeClasse;
	if(StringUtilidades::TerminaCom(nomeClasse, ".class"))
	{
		nomeSemExtensao= StringUtilidades::RemoverNoFinal(nomeSemExtensao, ".class");
	}
	if(classes.count(nomeSemExtensao) >0)
	{
		return ( (classes[nomeSemExtensao])->getMetodo(nomeMetodo, descritor) ) != NULL;
	}
	return false;
}

int RuntimeDataArea::ObterTamanhoDaPilhaDeFrames(void)
{
	return pilhaJVM.size();
}


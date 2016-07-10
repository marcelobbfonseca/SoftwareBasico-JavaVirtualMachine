#include"UtilidadesParaString.hpp"
#include"RuntimeDataArea.hpp"

#define DEBUG_RDA
//#define DEBUG_RDA_CARREGAR_CLASSE

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
	#ifdef DEBUG_RDA_CARREGAR_CLASSE
	cout<< "RuntimeDataArea::CarregarClasse(const string &nomeDaClasse) 0" << endl;
	#endif
	if(!primeiraVez)
	{
		if(MetodoExiste(nomeSemExtensao, "<clinit>", "()V"))
		{
	#ifdef DEBUG_RDA_CARREGAR_CLASSE
	cout<< "RuntimeDataArea::CarregarClasse(const string &nomeDaClasse) 1" << endl;
	#endif
			//pseudocodigo:
			string clinit= "<clinit>";
			string V= "()V";
			Frame *novoFrame= new Frame(classes[nomeSemExtensao], clinit, V, this);
			empilharFrame(novoFrame);
		}
	}
	#ifdef DEBUG_RDA_CARREGAR_CLASSE
	cout<< "RuntimeDataArea::CarregarClasse(const string &nomeDaClasse) 2" << endl;
	#endif
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
#ifdef DEBUG_RDA
	printf("RuntimeDataArea::empilharFrame");
	cout <<endl;
	printf("\tframe= %p", (void*)frame);
	cout <<endl;
#endif
	this->pilhaJVM.push(frame);
#ifdef DEBUG_RDA
	cout<< "Retornando do empilharFrame" << endl;
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
#ifdef DEBUG_RDA
	cout<< "FrameSendoDesempilhado. Numero de frames apos desempilhar: " << pilhaJVM.size() << endl;
#endif
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


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
	if(classes.count(nomeSemExtensao) >0)
	{
		return classes[nomeSemExtensao];
	}
	string nomeComExtensao= nomeDaClasse;
	if (!StringUtilidades::TerminaCom(nomeComExtensao, ".class") )
	{
		nomeComExtensao+= ".class";
	}
	classes[nomeSemExtensao] = classLoader->CarregarClasse(nomeComExtensao);

	// adicionando <clinit> da classe (se existir) na stack frame.
	static bool primeiraVez= true;//se for a primeira classe a ser carregada, deixa a execution engine carregar o clinit
	if(!primeiraVez)
	{
		if(MetodoExiste(nomeSemExtensao, "<clinit>", "()V"))
		{
			//pseudocodigo:
			string clinit= "<clinit>";
			string V= "()V";
			//TODO: Colocar o construtor de frame para métodos estáticos
			Frame *novoFrame= new Frame(classes[nomeSemExtensao], clinit, V, this);
			empilharFrame(novoFrame);
		}
	}
	primeiraVez= false;
	return classes[nomeSemExtensao];
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
	this->pilhaJVM.push(*frame);
}

Frame *RuntimeDataArea::topoPilha()
{
	return &(this->pilhaJVM.top());
}

Frame RuntimeDataArea::desempilharFrame()
{
	if (pilhaJVM.size() == 0)
	{
		cerr << "IndexOutOfBoundsException" << endl;
		exit(1);
	}
	Frame topo = pilhaJVM.top();
	pilhaJVM.pop();
	return topo;
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


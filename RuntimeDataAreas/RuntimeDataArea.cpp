#include"UtilidadesParaString.hpp"
#include"RuntimeDataArea.hpp"

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

	if(MetodoExiste(nomeSemExtensao, "<clinit>", "()V"))
	{
		//pseudocodigo:
		string clinit= "<clinit>";
		string V= "()V";
		Objeto *obj= new Objeto();
		obj->instancia = NULL;
		obj->javaClass= classes[nomeSemExtensao];
		Frame *novoFrame= new Frame(obj, clinit, V);
		empilharFrame(novoFrame);
	}
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
	cout<< "RuntimeDataArea::empilharFrame" << endl << "\tframe= " << frame <<endl << "\tpilhaJVM= "<< pilhaJVM << endl;
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


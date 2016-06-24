#include"RuntimeDataArea.hpp"
JavaClass *RuntimeDataArea::CarregarClasse(const string &nomeDaClasse)
{
	string nomeSemExtensao= nomeDaClasse;
	if(StringUtilidadesTerminaCom(nomeClasse, ".class")
	{
		nomeSemExtensao= RemoverNoFinal(nomeSemExtensao, ".class");
	}
	if(classes.count(nomeSemExtensao) >0)
	{
		return classes[nomeSemExtensao];
	}
	string nomeComExtensao= nomeDaClasse;
	if (!StringUtilidades::TerminaCom(nomeComExtensao, ".class")
	{
		nomeComExtensao+= ".class";
	}
	classes[nomeSemExtensao] = classLoader->CarregarClasse(nomeComExtensao);

	// adicionando <clinit> da classe (se existir) na stack frame.

	if(MetodoExiste(nomeSemExtensao, "<clinit>", "()V"))
	{
		//pseudocodigo:
		Frame *novoFrame= new Frame(classes[nomeSemExtensao], "<clinit>", "()V");
		EmpilharFrame(novoFrame);

}

void RuntimeDataArea::SetClassLoader(ClassLoader *classLoader)
{
	this.classLoader =classLoader;
}

void RuntimeDataArea::SetExecutionEngine(ExecutionEngine *executionEngine)
{
	this.executionEngine =executionEngine;
}

void RuntimeDataArea::EmpilharFrame(Frame *frame){

    this->pilhaFrames.push(frame);

}

Frame RuntimeDataArea::topoPilha(){

    return this->pilhaFrames.top();

}

Frame RuntimeDataArea::desempilhaFrame() {

    if (pilhaJVM.size() == 0) {

        cerr << "IndexOutOfBoundsException" << endl;
        exit(1);

    }

    Frame topo = pilhaJVM.top();

    pilhaJVM.pop();

    return top;
}

bool RuntimeDataArea::MetodoExiste(string nomeClasse, string nomeMetodo, string descritor)
{
	string nomeSemExtensao= nomeDaClasse;
	if(StringUtilidadesTerminaCom(nomeClasse, ".class")
	{
		nomeSemExtensao= RemoverNoFinal(nomeSemExtensao, ".class");
	}
	if(classes.count(nomeSemExtensao) >0)
	{
		return (classes[nomeSemExtensao])->MetodoExiste(nomeMetodo, descritor);
	}
	return false;
}


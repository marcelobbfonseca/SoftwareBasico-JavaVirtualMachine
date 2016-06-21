#include"MethodArea.hpp"
#include"UtilidadesParaString.hpp"

MethodArea::MethodArea(){}

MethodArea::~MethodArea(){}

DadosDaClasse *MethodArea::CarregarClasse(const string &nomeDaClasse)
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

	if(MetodoExiste, "<clinit>", "()V")
	{
		//pseudocodigo:
		Frame *novoFrame= new Frame(classes[nomeSemExtensao], "<clinit>", "()V");
		runtimeDataArea.EmpilharFrame(novoFrame);
	}
}

void MethodArea::SetClassLoader(ClassLoader *classLoader)
{
	this.classLoader =classLoader;
}

void MethodArea::SetExecutionEngine(ExecutionEngine *executionEngine)
{
	this.executionEngine =executionEngine;
}

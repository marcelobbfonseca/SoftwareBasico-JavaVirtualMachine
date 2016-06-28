#include"ClassLoader.hpp"

JavaClass* ClassLoader::CarregarClasse(string nomeClasse)
{
	//Se não tiver.class no nome da classe .class é adicionado
	if(!(nomeClasse.substr(nomeClasse.length() - 6)== ".class" )){

		nomeClasse+= ".class";

	}
	//ler a porra toda e mandar pro DataArea
	if(classesCarregadas.find(nomeClasse) == classesCarregadas.end()){

		classesCarregadas[nomeClasse] = (new JavaClass(nomeClasse));

	}
	//gerar dados da classe retornar o DadosDaClasse
	return classesCarregadas[nomeClasse];

}

ClassLoader::ClassLoader(void)
{
	
}

void ClassLoader::SetRuntimeDataArea(RuntimeDataArea *runtimeDataArea)
{
	this->runtimeDataArea= runtimeDataArea;
}

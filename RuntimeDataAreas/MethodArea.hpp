#include<string>
#include<map>
#include"DadosDaClasse.hpp"

#ifndef METHOD_AREA_HPP
#define METHOD_AREA_HPP

using namespace std;

class MethodArea
{
	public:
		MethodArea();
		DadosDaClasse* CarregarClasse(const string nomeDaClasse);
		DadosDaClasse* ObterDadosDaClasse(const string nomeDaClasse);
	private:
		map<string, DadosDaClasse*> classes;
}

#endif

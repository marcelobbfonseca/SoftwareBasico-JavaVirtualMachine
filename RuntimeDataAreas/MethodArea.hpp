#include<string>
#include"DadosDaClasse.hpp"

using namespace std;

class MethodArea
{
	public:
		MethodArea();
		DadosDaClasse* CarregarClasse(const string nomeDaClasse);
		DadosDaClasse* ObterDadosDaClasse(const string nomeDaClasse);
	private:
		map<string, DadosDaClasse*>
}

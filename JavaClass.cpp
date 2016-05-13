#include"JavaClass.hpp"
#include "Erro.hpp"
#include "Leitura.hpp"

using namespace std;
using namespace Leitura;

void JavaClass::LerArquivo(string nomeArquivo)
{
	FILE *arq= fopen(nomeArquivo.c_str(), "rb");
	if(arq == NULL)
	{
		throw(new Erro("Falha na abertura do arquivo!"));
	}
	LerAtributo(&magic, 4, arq);
	LerAtributo(&minor_version, 2, arq);
	LerAtributo(&major_version, 2, arq);
	LerAtributo(&constant_pool_count, 2, arq);
	for(int cont=0; cont < constant_pool_count; cont++)
	{
		try{
			cp_info &cpInfo = LerCpInfo(arq);
			constant_pool.push_back(cpInfo);
		}
		catch(CONSTANT_Long_info longInfo)
		{
			constant_pool.push_back(longInfo);
			NaoUsavel &naoUsavel= new NaoUsavel();
			costant_pool.push_back(naoUsavel);
			cont++;
		}
		catch(CONSTANT_Double_info doubleInfo)
		{
			constant_pool.push_back(doubleInfo);
			NaoUsavel &naoUsavel= new NaoUsavel();
			costant_pool.push_back(naoUsavel);
			cont++;
		}
	}
	LerAtributo(&access_flags, 2, arq);
	LerAtributo(&this_class, 2, arq);
	LerAtributo(&super_class, 2, arq);
}

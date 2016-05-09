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
	//ler constant pool aqui
	LerAtributo(&access_flags, 2, arq);
	LerAtributo(&this_class, 2, arq);
	LerAtributo(&super_class, 2, arq);
}

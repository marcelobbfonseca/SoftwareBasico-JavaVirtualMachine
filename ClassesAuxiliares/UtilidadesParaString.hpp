#ifndef UTILIDADES_PARA_STRINGS_HPP
#define UTILIDADES_PARA_STRINGS_HPP

#include<string>
#include<string.h>
#include"Erro.hpp"

namespace StringUtilidades
{
	using namespace std;

	bool TerminaCom(const string &str, char const *final)
	{
		int tamanhoFinal= strlen(final);
		int tamanhoString= str.length();
		if(tamanhoString < tamanhoFinal || tamanhoFinal < 1)
		{
			return false;
		}
		do
		{
			tamanhoFinal--;
			tamanhoString--;
			if(str[tamanhoString] != final[tamanhoFinal])
			{
				return false;
			}
			if(tamanhoFinal == 0)
			{
				return true;
			}
		}while(1);
	}

	string RemoverNoFinal(string &str, char const *final)
	{
		if(!TerminaCom(str, final))
		{
			string msgErro = "'";
			msgErro+= str;
			msgErro+= "'";
			msgErro+= " nao termina com ";
			msgErro+= "'";
			msgErro+= final;
			msgErro+= "'";
			throw new Erro(msgErro, "StringUtilidades", "RemoverNoFinal");
		}
		string retorno= str.substr(0, str.length()-strlen(final));
		return retorno;
	}
}
#endif

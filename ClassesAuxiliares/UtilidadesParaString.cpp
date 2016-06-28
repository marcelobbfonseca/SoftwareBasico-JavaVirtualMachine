#include"UtilidadesParaString.hpp"

using namespace std;

namespace StringUtilidades
{
#define STRING_UTILIDADES
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
	string RemoverCaminho(string &str)
	{
		string retorno= "";
		char temp[2];
		temp[1]= '\0';
		for(int cont =str.size()-1; cont >= 0; cont--)
		{
			temp[0]= str[cont];
			if( (temp[0] == '\\' ) ||  ( temp[0] == '/' ))
			{
				break;
			}
			retorno.insert(0, temp);
		}
		return retorno;
	}
	string RemoverCaminhoEExtensao(string &str, char const *extensao)
	{
		string saida= TerminaCom(str, extensao)? RemoverNoFinal(str, extensao) : str;
		return RemoverCaminho(saida);
	}
}

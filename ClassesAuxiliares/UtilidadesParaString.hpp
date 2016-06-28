#ifndef UTILIDADES_PARA_STRINGS_HPP
#define UTILIDADES_PARA_STRINGS_HPP

#include<string>
#include<string.h>
#include"Erro.hpp"

#ifndef STRING_UTILIDADES
namespace StringUtilidades
{
	bool TerminaCom(const string &str, char const *final);
	string RemoverNoFinal(string &str, char const *final);
}
#endif
#endif

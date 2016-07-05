#include "ObjetoString.hpp"

ObjetoString::ObjetoString(string s): stringInterna(s)
{
	
}

ObjetoString::~ObjetoString()
{
	
}

string ObjetoString::ObterString(void)
{
	return stringInterna;
}

void ObjetoString::SetString(string s)
{
	stringInterna=s;
}

TipoObjeto ObjetoString::ObterTipoObjeto(void)
{
	return TipoObjeto::STRING;
}

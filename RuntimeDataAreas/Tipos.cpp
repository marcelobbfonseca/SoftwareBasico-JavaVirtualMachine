#include"Tipos.hpp"
#include"Erro.hpp"

std::string ObterStringTipo(TipoDado tipo)
{
	if(tipo==BOOLEAN)return "BOOLEAN";
	if(tipo==BYTE)return "BYTE";
	if(tipo==CHAR)return "CHAR";
	if(tipo==SHORT)return "SHORT";
	if(tipo==INT)return "INT";
	if(tipo==FLOAT)return "FLOAT";
	if(tipo==RETURN_ADDR)return "RETURN_ADDR";
	if(tipo==REFERENCE)return "REFERENCE";
	if(tipo==LONG)return "LONG";
	if(tipo==DOUBLE)return "DOUBLE";
	if(tipo==PADDING)return "PADDING";
	int8_t *ptr= NULL;
	*ptr=0;
	throw new Erro("ObterStringTipo recebeu um tipo invalido");
}

#include"Tipos.hpp"
#include"Erro.hpp"

std::string ObterStringTipo(TipoDado tipo)
{
	if(tipo==TipoDado::BOOLEAN)return "BOOLEAN";
	if(tipo==TipoDado::BYTE)return "BYTE";
	if(tipo==TipoDado::CHAR)return "CHAR";
	if(tipo==TipoDado::SHORT)return "SHORT";
	if(tipo==TipoDado::INT)return "INT";
	if(tipo==TipoDado::FLOAT)return "FLOAT";
	if(tipo==TipoDado::RETURN_ADDR)return "RETURN_ADDR";
	if(tipo==TipoDado::REFERENCE)return "REFERENCE";
	if(tipo==TipoDado::LONG)return "LONG";
	if(tipo==TipoDado::DOUBLE)return "DOUBLE";
	if(tipo==TipoDado::PADDING)return "PADDING";
	throw new Erro("ObterStringTipo recebeu um tipo invalido");
}

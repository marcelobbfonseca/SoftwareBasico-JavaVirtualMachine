#include"Tipos.hpp"
#include"Erro.hpp"

std::string ObterStringTipo(TipoDado tipo)
{
<<<<<<< HEAD
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
=======
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
>>>>>>> 681ff0d8cec8c47fff77cb49739e7568e9bebcbe
	throw new Erro("ObterStringTipo recebeu um tipo invalido");
}

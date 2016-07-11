#include"Tipos.hpp"
#include"Erro.hpp"

std::string ObterStringTipo(TipoDado tipo)
{

	if(tipo==BOOLEANO)return "BOOLEANO";
	if(tipo==BYTE)return "BYTE";
	if(tipo==CHAR)return "CHAR";
	if(tipo==SHORT)return "SHORT";
	if(tipo==INTEIRO)return "INTEIRO";
	if(tipo==FLOAT)return "FLOAT";
	if(tipo==ENDERECO_DE_RETORNO)return "ENDERECO_DE_RETORNO";
	if(tipo==REFERENCIA)return "REFERENCIA";
	if(tipo==LONG)return "LONG";
	if(tipo==DOUBLE)return "DOUBLE";
	if(tipo==PREENCHIMENTO)return "PREENCHIMENTO";

	if(tipo==TipoDado::BOOLEANO)return "BOOLEANO";
	if(tipo==TipoDado::BYTE)return "BYTE";
	if(tipo==TipoDado::CHAR)return "CHAR";
	if(tipo==TipoDado::SHORT)return "SHORT";
	if(tipo==TipoDado::INTEIRO)return "INTEIRO";
	if(tipo==TipoDado::FLOAT)return "FLOAT";
	if(tipo==TipoDado::ENDERECO_DE_RETORNO)return "ENDERECO_DE_RETORNO";
	if(tipo==TipoDado::REFERENCIA)return "REFERENCIA";
	if(tipo==TipoDado::LONG)return "LONG";
	if(tipo==TipoDado::DOUBLE)return "DOUBLE";
	if(tipo==TipoDado::PREENCHIMENTO)return "PREENCHIMENTO";
	throw new Erro("ObterStringTipo recebeu um tipo invalido");
}

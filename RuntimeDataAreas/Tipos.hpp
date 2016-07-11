#ifndef TIPOS_H
#define TIPOS_H

#include<stdint.h>
#include<string>
#define TIPODADO
enum TipoDado {
	BOOLEANO,
	BYTE,
	CHAR,
	SHORT,
	INTEIRO,
	FLOAT,
	ENDERECO_DE_RETORNO,
	REFERENCIA,
	LONG,
	DOUBLE,
	PREENCHIMENTO
};
typedef enum TipoDado TipoDado;
#define VALOR
struct Valor {
	TipoDado tipo;
	uint64_t dado;
};
typedef struct Valor Valor;

std::string ObterStringTipo(TipoDado tipo);

#endif

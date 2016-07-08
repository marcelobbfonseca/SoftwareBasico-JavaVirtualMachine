#ifndef TIPOS_H
#define TIPOS_H

#include<stdint.h>
#include<string>
#define TIPODADO
enum TipoDado {
	BOOLEAN,
	BYTE,
	CHAR,
	SHORT,
	INT,
	FLOAT,
	RETURN_ADDR,
	REFERENCE,
	LONG,
	DOUBLE,
	PADDING
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

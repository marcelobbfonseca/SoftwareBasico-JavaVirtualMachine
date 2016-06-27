#ifndef TIPOS_H
#define TIPOS_H

enum TipoDado {
    BOOLEAN,
    BYTE,
    CHAR,
    SHORT,
    INT,
    FLOAT,
    LONG,
    DOUBLE,
    RETURN_ADDR,
    REFERENCE,
    HIGHLONG,
    LOWLONG,
    HIGHDOUBLE,
    LOWDOUBLE
};
typedef enum TipoDado TipoDado;

struct Valor {
    TipoDado tipo;
    uint32_t dado;
};
typedef struct Valor Valor;

#endif

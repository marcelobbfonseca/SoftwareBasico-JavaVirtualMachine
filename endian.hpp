#include<stdint.h>

#ifndef ENDIAN_HPP
#define ENDIAN_HPP

bool EhLittleEndian(void)
{
	uint32_t teste = 1;
	uint8_t *ptr= (uint 8_t *) &teste;
	return(ptr[0] == 1);
}

template <class T>
T InverterEndianess (T num)
{
	T retorno;
	uint8_t *ptRetorno= (uint8_t *) &retorno;
	uint8_t *ptNumero= (uint8_t *) &num;
	for(int cont =0, int cont2= sizeof(T)-1; cont < sizeof(T); cont++, cont2--)
	{
		ptRetorno[cont]= ptNumero[cont2];
	}
	return retorno;
}

#endif

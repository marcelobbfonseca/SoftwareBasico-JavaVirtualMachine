#include"Endian.hpp"

bool EhLittleEndian(void)
{
	uint32_t teste = 1;
	uint8_t *ptr= (uint8_t *) &teste;
	return(ptr[0] == 1);
}
/*
template <typename T>
T InverterEndianess (T num)
{
	if(!EhLittleEndian())
	{
		return num;
	}
	T retorno;
	uint8_t *ptRetorno= (uint8_t *) &retorno;
	uint8_t *ptNumero= (uint8_t *) &num;
	for(unsigned int cont =0, cont2= sizeof(T)-1; cont < sizeof(T); cont++, cont2--)
	{
		ptRetorno[cont]= ptNumero[cont2];
	}
	return retorno;
}
*/

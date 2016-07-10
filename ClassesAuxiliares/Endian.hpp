#include<stdint.h>

#ifndef ENDIAN_HPP
#define ENDIAN_HPP

bool EhLittleEndian(void);

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

template <typename T,typename U>
T ExpandirSinal (T num)
{
	if(sizeof(T)== 8)//expandir para int64
	{
		if(sizeof(U)== 1)
		{
			uint8_t *ptr;
			ptr= &num;
		}
		else if(sizeof(U) == 2)
		{
			
		}
		else if(sizeof(U) == 4)
		{
			
		}
	}
	else if (sizeof(T)== 4)
	{
		
	}
	else if (sizeof(T)== 2)
	{
		
	}
}


#endif

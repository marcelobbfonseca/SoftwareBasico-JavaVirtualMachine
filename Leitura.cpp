#include"Leitura.hpp"
#include<stdio.h>

namespace Leitura
{
	void LerAtributo(void *alvo, int size, FILE *arq)
	{
		if(!fread(alvo, size, 1, arq))
		{
			throw(new Erro("Erro na leitura do arquivo!") );
		}
#ifdef INVERTER_ENDIAN_NA_LEITURA
		if(size == 2)
		{
			uint16_t temp;
			uint8_t *aux=&temp;
			uint8_t *aux2= alvo;
			aux[0]= aux2[1];
			aux[1]= aux2[0];
			
			aux2[0]= aux[0];
			aux2[1]= aux[1];
		}
		else if(size == 4)
		{
			uint32_t temp;
			uint8_t *aux=&temp;
			uint8_t *aux2= alvo;
			aux[0]= aux2[3];
			aux[1]= aux2[2];
			aux[2]= aux2[1];
			aux[3]= aux2[0];
			
			aux2[0]= aux[0];
			aux2[1]= aux[1];
			aux2[2]= aux[2];
			aux2[3]= aux[3];
		}
#endif
	}
}

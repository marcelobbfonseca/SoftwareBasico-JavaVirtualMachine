#include"Leitura.hpp"
#include"Endian.hpp"
#include<stdint.h>
#include<stdio.h>

namespace Leitura
{
	void LerAtributo(void *alvo, int size, FILE *arq, bool ehNumero)
	{
		if(!fread(alvo, size, 1, arq))
		{
			throw(new Erro("Erro na leitura do arquivo!") );
		}
		if(ehNumero)
		{
			if(!EhLittleEndian()) return;
			if(size == 2 )
			{
				uint16_t *auxPtr= (uint16_t *) alvo;
				uint16_t aux= InverterEndianess<uint16_t>( *auxPtr );
				*auxPtr= aux;
				return;
			}
			if(size == 4)
			{
				uint32_t *auxPtr= (uint32_t *) alvo;
				uint32_t aux= InverterEndianess<uint32_t>( *auxPtr );
				*auxPtr= aux;
				return;
			}
		}
	}
}

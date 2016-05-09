#include<cstdio>
#include"Erro.hpp"

#ifndef LEITURA
#define LEITURA

//!  Namespcae com funções gerais de leitura
/*!
  Esse namespace contém funções gerais usadas na leituras dos arquivos
*/
namespace Leitura
{
	//! Função utilizada para leitura de algum arquivo.
	/*!
	Ele faz a leitura do arquivo e, no caso de erro; uma exceção Erro é lançada.
	  \todo Verificar se é necessário inverter os bytes nas leituras de números.
	  \param alvo Onde deve-se armazenar o que vai ser lido
	  \param size Quantidade de bytes a ser lido
	  \param arq Arquivo de onde se deve ler
	*/
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
		}else if(size == 4)
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

#endif

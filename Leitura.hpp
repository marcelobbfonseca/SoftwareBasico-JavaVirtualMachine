#include"Erro.hpp"
#include<stdio.h>

#ifndef LEITURA_HPP
#define LEITURA_HPP

#define EH_NUMERO true
#define IGNORAR_ENDIAN false

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
    void LerAtributo(void *alvo, int size, FILE *arq, bool ehNumero=true);
}

#endif

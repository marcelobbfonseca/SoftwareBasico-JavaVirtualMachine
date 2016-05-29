#include"Buffer.hpp"
#include"Leitura.hpp"
#include"Endian.hpp"
#include<string.h>

using namespace Leitura;

Buffer::Buffer(FILE *arq, int tamanho)
{
	buffer= new uint8_t[tamanho];
	LerAtributo(buffer, tamanho, arq, IGNORAR_ENDIAN);
	this->proximaPosicaoParaLer=0;
	this->tamanhoBuffer= tamanho;
}

Buffer::Buffer(Buffer &buff, int tamanho)
{
	buffer= new uint8_t[tamanho];
	buff.Ler(buffer, tamanho, IGNORAR_ENDIAN);
	this->proximaPosicaoParaLer=0;
	this->tamanhoBuffer= tamanho;
}


void Buffer::Ler(void *alvo, int tamanho, bool ehNumero)
{
	if( tamanhoBuffer < proximaPosicaoParaLer + tamanho)
	{
		throw(new Erro("Buffer overflow na leitura do arquivo!") );
	}
	memcpy(alvo, &(buffer[proximaPosicaoParaLer]), tamanho);
	proximaPosicaoParaLer+= tamanho;
	if(ehNumero)
	{
		if(!EhLittleEndian()) return;
		if(tamanho == 2 )
		{
			uint16_t *auxPtr= (uint16_t *) alvo;
			uint16_t aux= InverterEndianess<uint16_t>( *auxPtr );
			*auxPtr= aux;
			return;
		}
		if(tamanho == 4)
		{
			uint32_t *auxPtr= (uint32_t *) alvo;
			uint32_t aux= InverterEndianess<uint32_t>( *auxPtr );
			*auxPtr= aux;
			return;
		}
	}
}
Buffer::~Buffer()
{
	delete []buffer;
	if(proximaPosicaoParaLer !=  tamanhoBuffer)
	{
		printf("[WARNING] Buffer nao foi lido completamente.\n");
	}
}

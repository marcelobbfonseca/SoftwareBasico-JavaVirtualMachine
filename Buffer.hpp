#include<stdint.h>
#include<stdio.h>

#ifndef BUFFER_HPP
#define BUFFER_HPP

class Buffer
{
	private:
		uint8_t* buffer;
		int tamanhoBuffer;
		int proximaPosicaoParaLer;
	public:
		Buffer(FILE *arq, int tamanho);
		Buffer(Buffer &buff, int tamanho);
		void Ler(void *alvo, int tamanho, bool ehNumero = true);
		~Buffer();
};

#endif

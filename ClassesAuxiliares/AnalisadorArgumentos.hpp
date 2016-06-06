#include<string.h>

#ifndef ANALISADORARGUMENTOS_HPP
#define ANALISADORARGUMENTOS_HPP

#define BUSCA_FALHOU (-1)

namespace AnalisadorArgumentos
{
	//função responsável por procurar por um argumento no 
	int EncontrarArgumento(char const * argumentoEsperado, int argc, char **argv)
	{
		for(int cont =0 ; cont < argc ; cont++)
		{
			if(!strcmp(argumentoEsperado, argv[cont]))
			{
				return cont;
			}
		}
		return BUSCA_FALHOU;
//		throw new Erro("Argumento não existe");
	}
}

#endif

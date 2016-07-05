#ifndef OBJETO_ARRAY_HPP
#define OBJETO_ARRAY_HPP

#include "Objeto.hpp"
#include "Tipos.h"
#include <vector>
#include <stdint.h>

#define OBJETO_ARRAY
class ObjetoArray: public Objeto
{
	public:
		ObjetoArray(TipoDado tipo);
		TipoDado TipoElementosDaArray(void);
		void InserirValor(Valor queSeraInserido);
		Valor RemoverValorDaPosicao(uint32_t posicao);
		Valor RemoverNoFinal(void);
		Valor RemoverNoInicio(void);
		uint32_t ObterTamanho(void);
		Valor ObterValor(uint32_t posicao);
		void AlterarElementoDaPosicao(uint32_t posicao, Valor valor);
		TipoObjeto ObterTipoObjeto(void);
	private:
		TipoDado tipoDado;
		vector<Valor> elementos;
};

#endif

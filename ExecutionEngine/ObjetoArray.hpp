#ifndef OBJETO_ARRAY_HPP
#define OBJETO_ARRAY_HPP

#include "Objeto.hpp"
#include "Tipos.hpp"
#include "Erro.hpp"
#include <vector>
#include <stdint.h>
#include <stack>
#include <assert.h>

using namespace std;

#define OBJETO_ARRAY
class ObjetoArray: public Objeto
{
	public:
		ObjetoArray(TipoDado tipo);
		~ObjetoArray();
		TipoDado TipoElementosDaArray(void) const;
		void InserirValor(Valor queSeraInserido);
		Valor RemoverValorDaPosicao(uint32_t posicao);
		Valor RemoverNoFinal(void);
		Valor RemoverNoInicio(void);
		int ObterTamanho(void) const;
		Valor ObterValor(uint32_t posicao) const;
		void AlterarElementoDaPosicao(uint32_t posicao, Valor valor);
		TipoObjeto ObterTipoObjeto(void);
		void popularSubArray(TipoDado tipoDado, stack<int> count);
		void empilhaValor(Valor valor);
	private:
		TipoDado tipo;
		vector<Valor> elementos;
};

#endif

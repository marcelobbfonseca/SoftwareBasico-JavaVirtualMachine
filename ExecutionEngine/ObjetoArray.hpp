#ifndef OBJETO_ARRAY_HPP
#define OBJETO_ARRAY_HPP

#include<vector>
#include<stack>
#include"Tipos.h"
class ObjetoArray
{
	public:
		ObjetoArray(TipoDado tipo);
		void popularSubArray(TipoDado tipoDado, stack<int> count);
		void empilhaValor(Valor valor);
	private:
		TipoDado tipo;
		vector<Valor> elementos;
};

#endif

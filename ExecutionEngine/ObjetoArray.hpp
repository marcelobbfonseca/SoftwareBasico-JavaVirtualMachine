#include<vector>
#include<stack>
#include"Tipos.h"
class ObjetoArray
{
	public:
		ObjetoArray(TipoDado tipo);
		void popularArray(TipoDado tipoDado, stack<int> count);
		void empilhaValor(Valor valor);
	private:
		TipoDado tipo;
		vector<Valor> elementos;
};

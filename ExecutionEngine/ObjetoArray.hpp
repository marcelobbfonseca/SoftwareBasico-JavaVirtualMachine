#include<vector>
class ObjetoArray{

public:
ObjetoArray(tipoDado tipo);
void popularArray(TipoDado tipoDado, stack<int> count);
void empilhaValor(Valor valor);

private:

TipoDado tipo;
vector<Valor> elementos;


};

#include "ObjetoArray.hpp"
using namespace std;

ObjetoArray::ObjetoArray(tipoDado tipo){

    this->tipo = tipo;

}

void ObjetoArray::popularSubArray(TipoDado tipoDado, stack<int> count){

    int currCount = count.top();
    count.pop();

    TipoDado tipoArr = (count.size() > 1) ? TipoDado::REFERENCE : tipoDado;

    if (count.size() == 0) {
        for (int i = 0; i < currCount; i++) {

            Valor ValorSubArr;
            ValorSubArr.tipo = tipoDado;
            ValorSubArr.dado = 0;
            empilhaValor(ValorSubArr);

        }

    }
    else {
        for (int i = 0; i < currCount; i++) {
            ObjetoArray *subarray = new ObjetoArray(tipoArr);
            subarray->popularSubArray(tipoDado, count);

            Valor ValorSubArr;
            ValorSubArr.tipo = TipoDado::REFERENCE;
            ValorSubArr.dado = (uint32_t)subarray;
            this->empilhaValor(ValorSubArr);
        }
    }
}

void ObjetoArray::empilhaValor(Valor valor) {

    assert(valor.tipo == tipo);

    elementos.push_back(valor);

}

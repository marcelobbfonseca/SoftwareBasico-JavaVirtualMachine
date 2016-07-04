#include "ObjetoArray.hpp"
using namespace std;

void ObjetoArray::popularArray(ObjetoArray *arr, TipoDado tipoDado, stack<int> count) {

    int currCount = count.top();
    count.pop();

    TipoDado tipoArr = (count.size() > 1) ? TipoDado::REFERENCE : tipoDado;

    if (count.size() == 0) {
        for (int i = 0; i < currCount; i++) {
            Valor ValorSubArr;
            ValorSubArr.tipo = tipoDado;
            ValorSubArr.dado = 0;
            arr->empilhaValor(subarrayValue);
        }

    }
    else {
        for (int i = 0; i < currCount; i++) {
            ObjetoArray *subarray = new ObjetoArray(tipoDado);
            popularArray(subarray, tipoDado, count);

            Valor ValorSubArr;
            ValorSubArr.tipo = TipoDado::REFERENCE;
            ValorSubArr.dado = (uint32_t)subarray;
            arr->empilhaValor(ValorSubArr);
        }
    }
}

void ObjetoArray::empilhaValor(Valor valor) {

    assert(valor.tipo == tipo);

    elementos.push_back(valor);

}

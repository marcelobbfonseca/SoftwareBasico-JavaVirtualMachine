#include<vector>
#include"Frame.hpp"

class Heap {


private:

    Heap(Heap const&); //não permite implementação cópia
    void operator=(Heap const&); // não permite atribuição

    vector<Objeto*> vetorObjetos;

public:

    Heap();

    void adcObjeto(Objeto *objeto) {
        vetorObjetos.push_back(objeto);
    }
};

class Heap {


private:

    Heap(Heap const&); //não permite implementação cópia
    void operator=(Heap const&); // não permite atribuição

    vector<Objeto*> vetorObjetos;

public:

    Heap();

    void Heap::adcObjeto(Objeto *objeto) {
        vetorObjetos.push_back(objeto);
    }
};

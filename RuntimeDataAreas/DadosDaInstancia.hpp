#include<map>
#include"JavaClass.hpp"

class DadosDaInstancia{

public:

DadosDaInstancia(JavaClass *javaClass);

private:

 map<string, Valor> fieldsInstancia;

};

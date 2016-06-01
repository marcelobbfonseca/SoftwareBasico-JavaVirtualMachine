#include <stdlib.h>
#include<string>
#include<iostream>
#include"JavaClass.hpp"
#include"Erro.hpp"

int main(int argc, char **argv)
{
		std::string caminho = argv[1];
		try{
			JavaClass *j1= new JavaClass(caminho);
			j1->ExibirInformacoes();
			delete j1;
		}
		catch(Erro* err)
		{
			std::cout<<err->GetMensagem()<<"\n";
		}
		catch(...)
		{
			std::cout << "[ERRO] Exceção desconhecida lançada!" << std::endl;
		}

	return 0;
}

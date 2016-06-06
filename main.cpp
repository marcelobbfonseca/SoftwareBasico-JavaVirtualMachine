#include <stdlib.h>
#include<string>
#include<iostream>
#include"JavaClass.hpp"
#include"Erro.hpp"
#include"AnalisadorArgumentos.hpp"

#define JVM_NAO_FEITA

int main(int argc, char **argv)
{
//pedido de ajuda
	if(AnalisadorArgumentos::EncontrarArgumento("--help", argc, argv) != -1)
	{
//		ExibirMensagemDeAjuda();
	}
//Chamando apenas o exibidor
	else if(AnalisadorArgumentos::EncontrarArgumento("--exibir-informacoes", argc, argv) != -1)
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
	}
	else
	{
//caso queira rodar a JVM
#ifdef JVM_NAO_FEITA
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
#else
//falta codar aqui
#endif
	}
	return 0;
}

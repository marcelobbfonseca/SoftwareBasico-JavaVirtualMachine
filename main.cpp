#include <stdlib.h>
#include<string>
#include<iostream>
#include"JavaClass.hpp"
#include"Erro.hpp"
#include"AnalisadorArgumentos.hpp"
#include"Easter.hpp"
#include"JVM.hpp"

#define JVM_NAO_FEITA

void ExibirMensagemDeAjuda(void);

int main(int argc, char **argv)
{
//pedido de ajuda
	if((AnalisadorArgumentos::EncontrarArgumento("--help", argc, argv) != -1) || argc ==1)
	{
		ExibirMensagemDeAjuda();
	}
	else if(AnalisadorArgumentos::EncontrarArgumento("--goku", argc, argv) != -1)
	{
		MostrarGoku();
	}
	else if(AnalisadorArgumentos::EncontrarArgumento("--goku-na-capivara", argc, argv) != -1)
	{
		MostrarGokuNaCapivara();
	}
//Chamando apenas o exibidor
	else if((AnalisadorArgumentos::EncontrarArgumento("--exibir-informacoes", argc, argv) != -1) || (AnalisadorArgumentos::EncontrarArgumento("-info", argc, argv) != -1) )
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
		//int indiceArquivo= AnalisadorArgumentos::EncontrarArgumento("--run", argc, argv) + 1;
		std::string caminho = argv[1];
		try{
			JVM *jvm = new JVM(caminho);
			//faz o q quiser
			delete jvm;
		}
		catch(Erro *err)
		{
			cout<< err->GetMensagem() << endl;
		}
	}
	return 0;
}

void ExibirMensagemDeAjuda(void)
{
	std::cout << "Bem vindo ao trabalho de SB do grupo MAFRJODEMA. Boa sorte tentando pronunciar isso =D" << std::endl;
	std::cout << "No linux, a sintaxe de uso  ./JVM.out [classeComMain.class] *[argumentosParaMain]\t\tpara rodar um arquivo .class" << std::endl;
	std::cout << "No linux, a sintaxe de uso  ./JVM.out [classe.class] --exibir-informacoes\t\tpara ver as informacoes do .class informado" << std::endl;
	std::cout << "No linux, a sintaxe de uso  ./JVM.out [classe.class] --help\t\t\tpara ver essa mensagem de erro" << std::endl;
//	std::cout << "Este programa tem os poderes do goku na capivara." << std::endl;
}



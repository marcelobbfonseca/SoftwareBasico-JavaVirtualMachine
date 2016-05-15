#include<string>
#include<iostream>
#include"JavaClass.hpp"
#include"Erro.hpp"

int main()
{
	std::string caminho= "Exemplos/HelloWorld.class";
	try{
		JavaClass *j1= new JavaClass(caminho);
		delete j1;
	}
	catch(Erro* err)
	{
		std::cout<<err->GetMensagem()<<"\n";
	}
	return 0;
}
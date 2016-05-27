#include "method_info.hpp"
#include"Leitura.hpp"
#include<iostream>

method_info::method_info(FILE *arq, std::vector<cp_info*> const &constant_pool)
{
	using namespace Leitura;
	
	LerAtributo(&access_flags, 2, arq);
	LerAtributo(&name_index, 2, arq);
	LerAtributo(&descriptor_index, 2, arq);
	LerAtributo(&attributes_count, 2, arq);
	for(int cont =0; cont < attributes_count; cont++)
	{
		attribute_info *p= attribute_info::LerAtributeInfo(arq, constant_pool);
		attributes.push_back(p);
	}
}

void method_info::ExibirInformacoes(void)
{
	cout << "\t\t\taccess_flags =\t\t" << access_flags << endl;
	if(access_flags & 0x0001)
	{
		cout << "\t\t\t\tACC_PUBLIC" << endl;
	}
	if(access_flags & 0x0002)
	{
		cout << "\t\t\t\tACC_PRIVATE" << endl;
	}
	if(access_flags & 0x0004)
	{
		cout << "\t\t\t\tACC_PROTECTED" << endl;
	}
	if(access_flags & 0x0008)
	{
		cout << "\t\t\t\tACC_STATIC" << endl;
	}
	if(access_flags & 0x0010)
	{
		cout << "\t\t\t\tACC_FINAL" << endl;
	}
	if(access_flags & 0x0020)
	{
		cout << "\t\t\t\tACC_SYNCHRONIZED" << endl;
	}
	if(access_flags & 0x0040)
	{
		cout << "\t\t\t\tACC_BRIDGE" << endl;
	}
	if(access_flags & 0x0080)
	{
		cout << "\t\t\t\tACC_VARARGS" << endl;
	}
	if(access_flags & 0x0100)
	{
		cout << "\t\t\t\tACC_NATIVE" << endl;
	}
	if(access_flags & 0x0400)
	{
		cout << "\t\t\t\tACC_ABSTRACT" << endl;
	}
	if(access_flags & 0x0800)
	{
		cout << "\t\t\t\tACC_STRICT" << endl;
	}
	if(access_flags & 0x1000)
	{
		cout << "\t\t\t\tACC_SYNTHETIC" << endl;
	}
	cout << "\t\t\tname_index =\t\t" << name_index << endl;
	cout << "\t\t\tdescriptor_index =\t" << descriptor_index << endl;
	cout << "\t\t\tattributes_count =\t" << attributes_count << endl;
	if(attributes.size() > 0)
	{
		cout << "\t\t\tAttributes:"<<endl;
		cout << "-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -   -" << endl;
		for(int cont =0; cont < attributes_count; cont++)
		{
			cout << "\t\t\t\tAttributes[" << cont << "]:" << endl;;
			attributes[cont]->ExibirInformacoes();
			if(cont < attributes_count -1)
			{
				cout << "-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -   -" << endl;
			}
		}
	}
}

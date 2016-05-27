#include<stdint.h>
#include<iostream>
#include "field_info.hpp"
#include"Leitura.hpp"

field_info::field_info(FILE *arq, std::vector<cp_info*> const &constant_pool)
{
	using namespace Leitura;

	LerAtributo(&access_flags, 2, arq);
	LerAtributo(&name_index, 2, arq);
	LerAtributo(&descriptor_index, 2, arq);
	LerAtributo(&attributes_count, 2, arq);
	for(int cont =0; cont < attributes_count; cont++)
	{
		attribute_info *att= attribute_info::LerAtributeInfo(arq, constant_pool);
		attributes.push_back(att);
	}
	

}

void field_info::ExibirInformacoes(void)
{
	cout << "\t\taccess_flags =\t\t" << access_flags << endl;
	if(access_flags & 0x0001)
	{
		cout << "\t\t\tACC_PUBLIC" << endl;
	}
	if(access_flags & 0x0002)
	{
		cout << "\t\t\tACC_PRIVATE" << endl;
	}
	if(access_flags & 0x0004)
	{
		cout << "\t\t\tACC_PROTECTED" << endl;
	}
	if(access_flags & 0x0008)
	{
		cout << "\t\t\tACC_STATIC" << endl;
	}
	if(access_flags & 0x0010)
	{
		cout << "\t\t\tACC_FINAL" << endl;
	}
	if(access_flags & 0x0040)
	{
		cout << "\t\t\tACC_VOLATILE" << endl;
	}
	if(access_flags & 0x0080)
	{
		cout << "\t\t\tACC_TRANSIENT" << endl;
	}
	if(access_flags & 0x1000)
	{
		cout << "\t\t\tACC_SYNTHETIC" << endl;
	}
	if(access_flags & 0x4000)
	{
		cout << "\t\t\tACC_ENUM" << endl;
	}
	cout << "\t\tname_index =\t\t" << name_index << endl;
	cout << "\t\tdescriptor_index =\t\t" << descriptor_index << endl;
	cout << "\t\tattributes_count =\t\t" << attributes_count << endl;
	if(attributes.size() > 0)
	{
		cout << "\t\tAttributes:"<<endl;
		cout << "-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -   -" << endl;
		for(int cont =0; cont < attributes_count; cont++)
		{
			attributes[cont]->ExibirInformacoes();
			if(cont != attributes_count-1)
			{
				cout << "-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -   -" << endl;
			}
		}
	}
}

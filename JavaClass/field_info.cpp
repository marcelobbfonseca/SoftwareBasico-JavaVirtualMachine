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

void field_info::ExibirInformacoes(string tabs, JavaClass *javaClass)
{
	cout << tabs << "access_flags =\t\t" << access_flags << endl;
	if(access_flags & 0x0001)
	{
		cout << tabs << "\tACC_PUBLIC" << endl;
	}
	if(access_flags & 0x0002)
	{
		cout << tabs << "\tACC_PRIVATE" << endl;
	}
	if(access_flags & 0x0004)
	{
		cout << tabs << "\tACC_PROTECTED" << endl;
	}
	if(access_flags & 0x0008)
	{
		cout << tabs << "\tACC_STATIC" << endl;
	}
	if(access_flags & 0x0010)
	{
		cout << tabs << "\tACC_FINAL" << endl;
	}
	if(access_flags & 0x0040)
	{
		cout << tabs << "\tACC_VOLATILE" << endl;
	}
	if(access_flags & 0x0080)
	{
		cout << tabs << "\tACC_TRANSIENT" << endl;
	}
	if(access_flags & 0x1000)
	{
		cout << tabs << "\tACC_SYNTHETIC" << endl;
	}
	if(access_flags & 0x4000)
	{
		cout << tabs << "\tACC_ENUM" << endl;
	}
	cout << tabs << "name_index =\t\t" << name_index << javaClass->getUTF8(name_index) << endl;
	cout << tabs << "descriptor_index =\t\t" << descriptor_index << javaClass->getUTF8(descriptor_index) << endl;
	cout << tabs << "attributes_count =\t\t" << attributes_count << javaClass->getUTF8(attributes_count) << endl;
	if(attributes.size() > 0)
	{
		cout <<  tabs << "Attributes:"<<endl;
		cout << "-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -   -" << endl;
		for(int cont =0; cont < attributes_count; cont++)
		{
			attributes[cont]->ExibirInformacoes(tabs + "\t", javaClass);
			if(cont != attributes_count-1)
			{
				cout << "-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -   -" << endl;
			}
		}
	}
}

uint16_t field_info::getAccessFlags(void){

    return access_flags;

}

uint16_t field_info::getNameIndex(void){

    return name_index;

}

uint16_t field_info::getDescriptorIndex(void){

        return descriptor_index;

}

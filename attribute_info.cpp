#include<stdint.h>
#include "attribute_info.hpp"
#include"Leitura.hpp"
#include<iostream>

attribute_info::attribute_info(FILE *arq)
{
	using namespace Leitura;
	LerAtributo(&attribute_name_index, 2, arq, EH_NUMERO);
	LerAtributo(&attribute_length, 4, arq, EH_NUMERO);
	info = new uint8_t[attribute_length];
	LerAtributo(info, attribute_length, arq);
}

attribute_info::~attribute_info()
{
//	delete[] info;
}

void attribute_info::ExibirInformacoes(void)
{
	using namespace std;

	cout << "\t\t\tattribute_name_index =\t" << attribute_name_index << endl;
	cout << "\t\t\tattribute_lenght =\t" << attribute_length << endl;
	cout << "\t\t\tinfo =\t0x";
	for(unsigned int cont = 0; cont < attribute_length; cont++)
	{
	int widthAnterior = cout.width(2);
	char fillAnterior = cout.fill('0');
		cout << hex <<( (int) (info[cont] ) ) << dec;
	cout.width(widthAnterior);
	cout.fill(fillAnterior);
	}
	cout<< endl;
}


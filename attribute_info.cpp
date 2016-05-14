#include<stdint.h>
#include "attribute_info.hpp"
#include"Leitura.hpp"

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
	delete info;
}



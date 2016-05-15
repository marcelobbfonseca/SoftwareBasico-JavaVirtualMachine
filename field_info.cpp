#include<stdint.h>
#include "field_info.hpp"
#include"Leitura.hpp"

field_info::field_info(FILE *arq)
{
	using namespace Leitura;

	LerAtributo(&access_flags, 2, arq);
	LerAtributo(&name_index, 2, arq, EH_NUMERO);
	LerAtributo(&descriptor_index, 2, arq, EH_NUMERO);
	LerAtributo(&attributes_count, 2, arq, EH_NUMERO);
	for(int cont =0; cont < attributes_count; cont++)
	{
		attribute_info *att= new attribute_info(arq);
		attributes.push_back(*att);
	}
	

}
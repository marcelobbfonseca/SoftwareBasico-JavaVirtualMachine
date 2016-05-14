#include "method_info.hpp"
#include"Leitura.hpp"

method_info::method_info(FILE *arq)
{
	using namespace Leitura;
	
	LerAtributo(&access_flags, 2, arq);
	LerAtributo(&name_index, 2, arq);
	LerAtributo(&descriptor_index, 2, arq);
	LerAtributo(&attributes_count, 2, arq);
	for(int cont =0; cont < attributes_count; cont++)
	{
		attribute_info *p= new attribute_info(arq);
		attributes.push_back(p);
	}
}

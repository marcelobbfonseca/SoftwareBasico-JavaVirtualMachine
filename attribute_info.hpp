#include<stdint.h>
#include<stdio.h>
//#include<vector>

#ifndef ATTRIBUTE_INFO_HPP
#define ATTRIBUTE_INFO_HPP

class attribute_info
{
	protected:
		uint16_t attribute_name_index;
		uint32_t attribute_length;
//	uint8_t *info;

	public:
	attribute_info * LerAtributeInfo(FILE *arq);
	virtual void ExibirInformacoes(void)=0;
};

#endif

#include<stdint.h>
#include<stdio.h>
//#include<vector>

#ifndef CONSTANTVALUE_ATTRIBUTE_HPP
#define CONSTANTVALUE_ATTRIBUTE_HPP

class constantValue_attribute {

    uint16_t attribute_name_index;
    uint32_t attribute_length;
    uint16_t constantvalue_index;

    public:

	constantValue_attribute(FILE *arq);
	~constantValue_attribute();
	void ExibirInformacoes(void);

}

#endif

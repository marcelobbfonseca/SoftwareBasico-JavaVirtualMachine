#include<stdint.h>
#include<stdio.h>
#include<vector>

#ifndef CODE_ATTRIBUTE_HPP
#define CODE_ATTRIBUTE_HPP


class code_attribute {

    uint16_t attribute_name_index;
    uint32_t attribute_length;
    uint16_t max_stack;
    uint16_t max_locals;
    uint32_t code_length;
    vector<uint8_t> code;
    uint16_t exception_table_length;
    vector<exception_table> exception_table;
    uint16_t attributes_count;
    vector<attribute_info> attributes;

    public:

	code_attribute(FILE *arq);
	~code_attribute();
	void ExibirInformacoes(void);

}

#endif

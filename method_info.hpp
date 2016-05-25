#include "attribute_info.hpp"
#include <stdint.h>
#include<stdio.h>
#include<vector>

#ifndef METHOD_INFO_HPP
#define METHOD_INFO_HPP

using namespace std;

class method_info {

	private:

	uint16_t access_flags;
	uint16_t name_index;
	uint16_t descriptor_index;
	uint16_t attributes_count;
	vector<attribute_info *> attributes;

	public:

	method_info(FILE *arq);
	void ExibirInformacoes(void);

};

#endif

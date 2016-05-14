#include "attribute_info.hpp"
#include <stdint.h>
#include<vector>

#ifndef FIELD_INFO_HPP
#define FIELD_INFO_HPP

using namespace std;


class field_info {

	private:

	uint16_t access_flags;
	uint16_t name_index;
	uint16_t descriptor_index;
	uint16_t attributes_count;
	vector<attribute_info*> attributes;

	public:
	
	field_info(FILE *arq);
};

#endif

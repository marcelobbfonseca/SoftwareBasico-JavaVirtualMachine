#include<stdint.h>
#include "field_info.hpp"

field_info::field_info(uint16_t access_flags,uint16_t name_index,uint16_t descriptor_index,uint16_t attributes_count,attribute_info attributes[attributes_count];)
{

	this.access_flags = access_flags;
	this.name_index =  name_index;
        this.descriptor_index =  descriptor_index;
        this.attributes_count = attributes_count;
	this .attributes = attributes;

	
}

#include "attributes_info.hpp"
#include <stdint.h>

class method_info {

	private:

	uint16_t access_flags;
	uint16_t name_index;
	uint16_t descriptor_index;
	uint16_t attributes_count;
	attribute_info attributes[attributes_count];

	public:

	method_info(uint16_t access_flags,uint16_t name_index,uint16_t descriptor_index,
		uint16_t attributes_count,attribute_info attributes[attributes_count]);

}






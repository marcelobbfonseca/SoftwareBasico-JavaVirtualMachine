#include<stdint.h>

class attribute_info {

	private:

	uint16_t attribute_name_index;
	uint32_t attribute_length;
	uint8_t info[attribute_length];

	public:
	
	attribute_info(uint16_t attribute_name_index,uint32_t attribute_length,uint8_t info[attribute_length]);

}

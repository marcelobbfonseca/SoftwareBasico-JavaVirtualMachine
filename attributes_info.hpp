#include<stdint.h>
#include<stdio.h>
//#include<vector>

class attribute_info
{
	private:
	uint16_t attribute_name_index;
	uint32_t attribute_length;
	uint8_t *info;

	public:
	
	attribute_info(FILE *arq);
	~attribute_info();
};

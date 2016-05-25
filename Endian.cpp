#include"Endian.hpp"

bool EhLittleEndian(void)
{
	uint32_t teste = 1;
	uint8_t *ptr= (uint8_t *) &teste;
	return(ptr[0] == 1);
}

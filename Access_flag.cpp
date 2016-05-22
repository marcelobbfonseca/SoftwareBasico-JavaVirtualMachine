#include "Access_flag.hpp"
#include "Leitura.hpp"
#include "Endian.hpp"
#include <string.h>
#include <iostream>


//validacao da leitura de access_flags.
void Access_flag::validarFlag(uint16_t flag)
{

	//Se for diferente os valores esperados, gera erro.
	switch (flag){
		case ACC_PUBLIC:	
		case ACC_FINAL:		
		case ACC_SUPER:		
		case ACC_INTERFACE: 
		case ACC_ABSTRACT:	
		case ACC_SYNTHETIC:	
		case ACC_ANNOTATION:
		case ACC_ENUM:		break;
		default:cout << "Valor access_flag: 0x" << hex << flag << endl;
				throw(new Erro("Error:Valor invalido para flag"));			
				break;
	}
	return;
}
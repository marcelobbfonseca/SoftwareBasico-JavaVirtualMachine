#include"cp-info.hpp"
#include "Leitura"

using namespace Leitura;


CONSTANT_Class_info::CONSTANT_Class_info(uint16_t nameIndex)
{
	tag= cpInfoTags::CONSTANT_Class;
	this.nameIndex= nameIndex;
}

CONSTANT_Fieldred_info::CONSTANT_Fieldred_info(uint16 classIndex, uint16-t nameAndTypeIndex)
{
	tag= cpInfoTags::CONSTANT_Fieldref;
	this.class_index= classIndex;
	this.name_and_type_index= nameAndTypeIndex;
}
CONSTANT_Methodref_info::CONSTANT_Methodref_info(uint16 classIndex, uint16-t nameAndTypeIndex)
{
	tag= cpInfoTags::CONSTANT_Methodref;
	this.class_index= classIndex;
	this.name_and_type_index= nameAndTypeIndex;
}
CONSTANT_InterfaceMethodref_info::CONSTANT_InterfaceMethodref_info(uint16 classIndex, uint16-t nameAndTypeIndex)
{
	tag= cpInfoTags::CONSTANT_InterfaceMethodref;
	this.class_index= classIndex;
	this.name_and_type_index= nameAndTypeIndex;
}


static cp_info& cp_info::LerCpInfo(FILE *arq)
{
	uint8_t tag;
	LerAtributo(&tag, 1, arq);
	switch(tag)
	{
		case (cpInfoTags::CONSTANT_Class):
			uint16_t nameIndex;
			LerAtributo(&nameIndex, 2, arq);
			return new CONSTANT_Class_info(nameIndex);
		case (cpInfoTags::CONSTANT_Fieldref):
		{
		}
		case CONSTANT_Fieldref:
		case CONSTANT_Methodref:
		case CONSTANT_InterfaceMethodref:
		{
		}
	}
}


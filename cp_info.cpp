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

CONSTANT_String_info(uint16_t stringIndex)
{
	tag= cpInfoTags::CONSTANT_String;
	this.string_index= stringIndex;
}
CONSTANT_Integer_info(uint32_t bytes)
{
	tag= cpInfoTags::CONSTANT_Integer;
	this.bytes= bytes;
}
CONSTANT_Float_info(uint32_t bytes)
{
	tag= cpInfoTags::CONSTANT_Float;
	this.bytes= bytes;
}
CONSTANT_NameAndType_info(uint16_t nameIndex, uint16_t descriptorIndex)
{
	tag= cpInfoTags::CONSTANT_NameAndType;
	descriptor_index= descriptorIndex;
}
CONSTANT_MethodHandle_info(uint8_t referenceKind, uint16_t referenceIndex)
{
	tag= cpInfoTags::CONSTANT_MethodHandle;
	reference_kind= referenceKind;
	reference_index= referenceIndex;
}
CONSTANT_MethodType_info(uint16_t descriptorIndex)
{
	tag= cpInfoTags::CONSTANT_MethodType;
	descriptor_index= descriptorIndex;
}
CONSTANT_InvokeDynamic_info(uint16_t bootstrapMethodAttrIndex, uint16_t nameAndTypeIndex)
{
	tag= cpInfoTags::CONSTANT_InvokeDynamic;
	bootstrap_method_attr_index= bootstrapMethodAttrIndex;
	name_and_type_index= nameAndTypeIndex;
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


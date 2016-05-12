#include"cp_info.hpp"
#include "Leitura.hpp"

using namespace Leitura;

CONSTANT_Class_info::CONSTANT_Class_info(uint16_t nameIndex)
{
	tag= CONSTANT_Class;
	name_index= nameIndex;
}

CONSTANT_Fieldref_info::CONSTANT_Fieldref_info(uint_16 classIndex, uint16_t nameAndTypeIndex)
{
	tag= CONSTANT_Fieldref;
	this->class_index= classIndex;
	this->name_and_type_index= nameAndTypeIndex;
}
CONSTANT_Methodref_info::CONSTANT_Methodref_info(uint_16 classIndex, uint16_t nameAndTypeIndex)
{
	tag= CONSTANT_Methodref;
	this->class_index= classIndex;
	this->name_and_type_index= nameAndTypeIndex;
}
CONSTANT_InterfaceMethodref_info::CONSTANT_InterfaceMethodref_info(uint_16 classIndex, uint16_t nameAndTypeIndex)
{
	tag= CONSTANT_InterfaceMethodref;
	this->class_index= classIndex;
	this->name_and_type_index= nameAndTypeIndex;
}

CONSTANT_String_info::CONSTANT_String_info(uint16_t stringIndex)
{
	tag= CONSTANT_String;
	this->string_index= stringIndex;
}
CONSTANT_Integer_info::CONSTANT_Integer_info(uint32_t bytes)
{
	tag= CONSTANT_Integer;
	this->bytes= bytes;
}
CONSTANT_Float_info::CONSTANT_Float_info(uint32_t bytes)
{
	tag= CONSTANT_Float;
	this->bytes= bytes;
}
CONSTANT_NameAndType_info::CONSTANT_NameAndType_info(uint16_t nameIndex, uint16_t descriptorIndex)
{
	tag= CONSTANT_NameAndType;
	descriptor_index= descriptorIndex;
}
CONSTANT_MethodHandle_info::CONSTANT_MethodHandle_info(uint8_t referenceKind, uint16_t referenceIndex)
{
	tag= CONSTANT_MethodHandle;
	reference_kind= referenceKind;
	reference_index= referenceIndex;
}
CONSTANT_MethodType_info::CONSTANT_MethodType_info(uint16_t descriptorIndex)
{
	tag= CONSTANT_MethodType;
	descriptor_index= descriptorIndex;
}
CONSTANT_InvokeDynamic_info::CONSTANT_InvokeDynamic_info(uint16_t bootstrapMethodAttrIndex, uint16_t nameAndTypeIndex)
{
	tag= CONSTANT_InvokeDynamic;
	bootstrap_method_attr_index= bootstrapMethodAttrIndex;
	name_and_type_index= nameAndTypeIndex;
}

cp_info* cp_info::LerCpInfo(FILE *arq)
{
	uint8_t tag;
	LerAtributo(&tag, 1, arq);
	switch(tag)
	{
		case (CONSTANT_Class):
		{
			uint16_t nameIndex;
			LerAtributo(&nameIndex, 2, arq);
			return new CONSTANT_Class_info(nameIndex);
		}
		case (CONSTANT_Fieldref):
		{
			uint16_t classIndex, nameAndTypeIndex;
			LerAtributo(&classIndex, 2, arq);
			LerAtributo(&nameAndTypeIndex, 2, arq);
			return new CONSTANT_Fieldref_info(classIndex, nameAndTypeIndex);
		}
		case (CONSTANT_Methodref):
		{
			uint16_t classIndex, nameAndTypeIndex;
			LerAtributo(&classIndex, 2, arq);
			LerAtributo(&nameAndTypeIndex, 2, arq);
			return new CONSTANT_Methodref_info(classIndex, nameAndTypeIndex);
		}
		case (CONSTANT_InterfaceMethodref):
		{
			uint16_t classIndex, nameAndTypeIndex;
			LerAtributo(&classIndex, 2, arq);
			LerAtributo(&nameAndTypeIndex, 2, arq);
			return new CONSTANT_InterfaceMethodref_info(classIndex, nameAndTypeIndex);
		}
		case (CONSTANT_String):
		{
			uint16_t stringIndex;
			LerAtributo(&stringIndex, 2, arq);
			return new CONSTANT_String_info(stringIndex);
		}
		case (CONSTANT_Integer):
		{
			uint32_t bytes;
			LerAtributo(&bytes, 4, arq);
			return new CONSTANT_Integer_info(bytes);
		}
		case (CONSTANT_Float):
		{
			uint32_t bytes;
			LerAtributo(&bytes, 4, arq);
			return new CONSTANT_Float_info(bytes);
		}
		case (CONSTANT_Long):
		{
			uint32_t highBytes, lowBytes;
			LerAtributo(&highBytes, 4, arq);
			LerAtributo(&lowBytes, 4, arq);
			return new CONSTANT_Long_info(highBytes, lowBytes);
		}
		case (CONSTANT_Double):
		{
			uint32_t highBytes, lowBytes;
			LerAtributo(&highBytes, 4, arq);
			LerAtributo(&lowBytes, 4, arq);
			return new CONSTANT_Double_info(highBytes, lowBytes);
		}
		case (CONSTANT_NameAndType):
		{
			uint16_t nameIndex, descriptorIndex;
			LerAtributo(&nameIndex, 2, arq);
			LerAtributo(&descriptorIndex, 2, arq);
			return new CONSTANT_NameAndType_info(nameIndex, descriptorIndex);
		}
		case (CONSTANT_Utf8):
		{
			uint16_t comprimento;
			LerAtributo(&comprimento, 2, arq);
			void *bytes= new uint8_t[comprimento];
			LerAtributo(bytes, comprimento, arq);
			return new CONSTANT_Utf8_info(comprimento, bytes);
		}
		case (CONSTANT_MethodHandle):
		{
			uint8_t referenceKind;
			uint16_t referenceIndex;
			LerAtributo(&referenceKind, 1, arq);
			LerAtributo(&referenceIndex, 2, arq);
			return new CONSTANT_MethodHandle_info(referenceKind, referenceIndex);
		}
		case (CONSTANT_MethodType):
		{
			uint16_t descriptorIndex;
			LerAtributo(&descriptorIndex, 2, arq);
			return new CONSTANT_MethodType_info(descriptorIndex);
		}
		case (CONSTANT_InvokeDynamic):
		{
			uint16_t bootstrapMethodAttrIndex, nameAndTypeIndex;
			LerAtributo(&bootstrapMethodAttrIndex, 2, arq);
			LerAtributo(&nameAndTypeIndex, 2, arq);
			return new CONSTANT_InvokeDynamic_info(bootstrapMethodAttrIndex, nameAndTypeIndex);
		}
		default:
		{
			throw new Erro("Método LerCpInfo leu um tag inválido!\n");
		}
	}
}


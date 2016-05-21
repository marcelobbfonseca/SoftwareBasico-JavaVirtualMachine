#include"cp_info.hpp"
#include "Leitura.hpp"
#include"Endian.hpp"
#include<string.h>
#include<iostream>

#define DEBUG
#ifdef DEBUG
#include<stdio.h>
#endif

CONSTANT_Class_info::CONSTANT_Class_info(uint16_t nameIndex)
{
	tag= CONSTANT_Class;
	name_index= nameIndex;
}

CONSTANT_Fieldref_info::CONSTANT_Fieldref_info(uint16_t classIndex, uint16_t nameAndTypeIndex)
{
	tag= CONSTANT_Fieldref;
	this->class_index= classIndex;
	this->name_and_type_index= nameAndTypeIndex;
}
CONSTANT_Methodref_info::CONSTANT_Methodref_info(uint16_t classIndex, uint16_t nameAndTypeIndex)
{
	tag= CONSTANT_Methodref;
	this->class_index= classIndex;
	this->name_and_type_index= nameAndTypeIndex;
}
CONSTANT_InterfaceMethodref_info::CONSTANT_InterfaceMethodref_info(uint16_t classIndex, uint16_t nameAndTypeIndex)
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
CONSTANT_Long_info::CONSTANT_Long_info(uint32_t highBytes, uint32_t lowBytes)
{
#ifdef DEBUG
printf("Long lido!");
#endif
	tag= CONSTANT_Long;
	high_bytes= highBytes;
	low_bytes= lowBytes;
}
CONSTANT_Double_info::CONSTANT_Double_info(uint32_t highBytes, uint32_t lowBytes)
{
#ifdef DEBUG
printf("Double lido!");
#endif
	tag= CONSTANT_Double;
	high_bytes= highBytes;
	low_bytes= lowBytes;
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
CONSTANT_Utf8_info::CONSTANT_Utf8_info(uint16_t comprimento, uint8_t *arrayBytes)
{
	lenght= comprimento;
	bytes= arrayBytes;
}
CONSTANT_Utf8_info::~CONSTANT_Utf8_info()
{
	delete bytes;
}

NaoUsavel::NaoUsavel(void)
{
	tag= TagNaoUsavel;
}

cp_info* cp_info::LerCpInfo(FILE *arq)
{
	using namespace Leitura;

	uint8_t tag;
	LerAtributo(&tag, 1, arq);
	switch(tag)
	{
		case (CONSTANT_Class):
		{
			uint16_t nameIndex;
			LerAtributo(&nameIndex, 2, arq, EH_NUMERO);
			return new CONSTANT_Class_info(nameIndex);
		}
		case (CONSTANT_Fieldref):
		{
			uint16_t classIndex, nameAndTypeIndex;
			LerAtributo(&classIndex, 2, arq, EH_NUMERO);
			LerAtributo(&nameAndTypeIndex, 2, arq, EH_NUMERO);
			return new CONSTANT_Fieldref_info(classIndex, nameAndTypeIndex);
		}
		case (CONSTANT_Methodref):
		{
			uint16_t classIndex, nameAndTypeIndex;
			LerAtributo(&classIndex, 2, arq, EH_NUMERO);
			LerAtributo(&nameAndTypeIndex, 2, arq, EH_NUMERO);
			return new CONSTANT_Methodref_info(classIndex, nameAndTypeIndex);
		}
		case (CONSTANT_InterfaceMethodref):
		{
			uint16_t classIndex, nameAndTypeIndex;
			LerAtributo(&classIndex, 2, arq, EH_NUMERO);
			LerAtributo(&nameAndTypeIndex, 2, arq, EH_NUMERO);
			return new CONSTANT_InterfaceMethodref_info(classIndex, nameAndTypeIndex);
		}
		case (CONSTANT_String):
		{
			uint16_t stringIndex;
			LerAtributo(&stringIndex, 2, arq, EH_NUMERO);
			return new CONSTANT_String_info(stringIndex);
		}
		case (CONSTANT_Integer):
		{
			uint32_t bytes;
			LerAtributo(&bytes, 4, arq, EH_NUMERO);
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
			LerAtributo(&highBytes, 4, arq, EH_NUMERO);
			LerAtributo(&lowBytes, 4, arq, EH_NUMERO);
			throw new CONSTANT_Long_info(highBytes, lowBytes);
		}
		case (CONSTANT_Double):
		{
			uint32_t highBytes, lowBytes;
			LerAtributo(&highBytes, 4, arq);
			LerAtributo(&lowBytes, 4, arq);
			throw new CONSTANT_Double_info(highBytes, lowBytes);
		}
		case (CONSTANT_NameAndType):
		{
			uint16_t nameIndex, descriptorIndex;
			LerAtributo(&nameIndex, 2, arq, EH_NUMERO);
			LerAtributo(&descriptorIndex, 2, arq, EH_NUMERO);
			return new CONSTANT_NameAndType_info(nameIndex, descriptorIndex);
		}
		case (CONSTANT_Utf8):
		{
			uint16_t comprimento;
			LerAtributo(&comprimento, 2, arq, EH_NUMERO);
			uint8_t *bytes= new uint8_t[comprimento];
			LerAtributo(bytes, comprimento, arq);
			return new CONSTANT_Utf8_info(comprimento, bytes);
		}
		case (CONSTANT_MethodHandle):
		{
			uint8_t referenceKind;
			uint16_t referenceIndex;
			LerAtributo(&referenceKind, 1, arq);
			LerAtributo(&referenceIndex, 2, arq, EH_NUMERO);
			return new CONSTANT_MethodHandle_info(referenceKind, referenceIndex);
		}
		case (CONSTANT_MethodType):
		{
			uint16_t descriptorIndex;
			LerAtributo(&descriptorIndex, 2, arq, EH_NUMERO);
			return new CONSTANT_MethodType_info(descriptorIndex);
		}
		case (CONSTANT_InvokeDynamic):
		{
			uint16_t bootstrapMethodAttrIndex, nameAndTypeIndex;
			LerAtributo(&bootstrapMethodAttrIndex, 2, arq, EH_NUMERO);
			LerAtributo(&nameAndTypeIndex, 2, arq, EH_NUMERO);
			return new CONSTANT_InvokeDynamic_info(bootstrapMethodAttrIndex, nameAndTypeIndex);
		}
		default:
		{
			char erro[150]= "Método LerCpInfo leu um tag inválido!\n\t\tTag lido: ";
			sprintf(erro, "Método LerCpInfo leu um tag inválido!\n\t\tTag lido: %hu\n", tag);
			throw new Erro(erro);
		}
	}
}

void CONSTANT_Class_info::ExibirInformacoes(void)
{
	cout << "Class\n\t\tname_index = " << name_index << endl;
}

void CONSTANT_Fieldref_info::ExibirInformacoes(void)
{
	cout << "Fieldref" << endl;
	cout <<"\t\tclass_index = " << class_index << endl;
	cout <<"\t\tname_and_type_index = " << name_and_type_index << endl;
}

void CONSTANT_Methodref_info::ExibirInformacoes(void)
{
	cout << "Methodref" << endl;
	cout <<"\t\tclass_index = " << class_index << endl;
	cout <<"\t\tname_and_type_index = " << name_and_type_index << endl;
}

void CONSTANT_InterfaceMethodref_info::ExibirInformacoes(void)
{
	cout << "InterfaceMethodref" << endl;
	cout <<"\t\tclass_index = " << class_index << endl;
	cout <<"\t\tname_and_type_index = " << name_and_type_index << endl;
}

void CONSTANT_String_info::ExibirInformacoes(void)
{
	cout << "String" << endl;
	cout << "\t\tstring_index = " << string_index << endl;
}

void CONSTANT_Integer_info::ExibirInformacoes(void)
{
	cout << "Integer" << endl;
	cout << "\t\tbytes = " << bytes << endl;
}

void CONSTANT_Float_info::ExibirInformacoes(void)
{
	cout << "Float" <<endl;
	cout << "\t\tbytes = 0x";
	uint8_t *ptr= (uint8_t *) &bytes ;
	for(int cont =0;  cont < 4 ; cont++)
	{
		cout<< hex << ptr[cont] << dec;
	}

	if(EhLittleEndian())
	{
		uint32_t numeroInvertido= InverterEndianess<uint32_t>(bytes);
		float *fl= (float *) &numeroInvertido;
		cout << "\t\t//"<< (*fl) << endl;
	}
	else
	{
		float *aux = (float *) &bytes;
		cout << "\t\t// " << (*aux) << endl;
	}
}

void CONSTANT_Long_info:: ExibirInformacoes(void)
{
	cout << "Long" << endl;
	cout << "\t\thigh_bytes = 0x";
	uint32_t invertido = InverterEndianess<uint32_t>(high_bytes);
	cout << hex << invertido << dec << endl;
	cout << "\t\tlow_bytes = 0x";
	uint32_t invertido2= InverterEndianess<uint32_t>(low_bytes);
	cout << hex << invertido2 << dec << endl;
	cout << "\t\tNumero representado: 0x" << hex << high_bytes <<low_bytes << dec << endl;
}

void CONSTANT_Double_info:: ExibirInformacoes(void)
{
	cout << "Double" << endl;
	cout << "\t\thigh_bytes = 0x";
	uint32_t invertido = InverterEndianess<uint32_t>(high_bytes);
	cout << hex << invertido << dec << endl;
	cout << "\t\tlow_bytes = 0x";
	uint32_t invertido2= InverterEndianess<uint32_t>(low_bytes);
	cout << hex << invertido2 << dec << endl;
	cout << "\t\tNumero representado: 0x" << hex << high_bytes <<low_bytes << dec << endl;
}

void CONSTANT_NameAndType_info::ExibirInformacoes(void)
{
	cout << "NameAndType" << endl;
	cout <<"\t\tname_index = " << name_index << endl;
	cout <<"\t\tdescriptor_index = " << descriptor_index << endl;
}

void CONSTANT_Utf8_info::ExibirInformacoes(void)
{
	cout << "UTF8" << endl;
	cout << "\t\tlenght = " << lenght << endl;
	cout << "\t\tbytes = ";
//	int widthAnterior = cout.width(2);
//	char fillAnterior = cout.fill('0');
	for(int cont = 0; cont < lenght; cont++)
	{
		cout << hex << bytes[cont] << dec;
	}
//	cout.width(widthAnterior);
//	cout.fill(fillAnterior);
	cout<<endl;
}

void CONSTANT_MethodHandle_info::ExibirInformacoes(void)
{
	cout << "MethodHandle" << endl;
	cout << "\t\treference_kind = " << reference_kind;
	switch(reference_kind)
	{
		case (REF_getField):
		{
			cout << "\t\t//getField" << endl;
			break;
		}
		case (REF_getStatic):
		{
			cout << "\t\t//getStatic" << endl;
			break;
		}
		case (REF_putField):
		{
			cout << "\t\t//putField" << endl;
			break;
		}
		case (REF_putStatic):
		{
			cout << "\t\t//putStatic" << endl;
			break;
		}
		case (REF_invokeVirtual):
		{
			cout << "\t\t//invokeVirtual" << endl;
			break;
		}
		case (REF_invokeStatic):
		{
			cout << "\t\t//invokeStatic" << endl;
			break;
		}
		case (REF_invokeSpecial):
		{
			cout << "\t\t//invokeSpecial" << endl;
			break;
		}
		case (REF_newInvokeSpecial):
		{
			cout << "\t\t//newInvokeSpecial" << endl;
			break;
		}
		case (REF_invokeInterface):
		{
			cout << "\t\t//invokeInterface" << endl;
			break;
		}
		default:
		{
			cout << "[ERRO] reference_kind inválido. \treference_kind = " << reference_kind << endl;
			break;
		}
	}
	cout << "\t\treference_index = " << reference_index;
}

void CONSTANT_MethodType_info::ExibirInformacoes(void)
{
	cout << "MethodType" << endl;
	cout <<"\t\tdescriptor_index = " << descriptor_index << endl;
}

void CONSTANT_InvokeDynamic_info::ExibirInformacoes(void)
{
	cout << "InvokeDynamic" << endl;
	cout <<"\t\tbootstrap_method_attr_index = " << bootstrap_method_attr_index << endl;
	cout <<"\t\tname_and_type_index = " << name_and_type_index << endl;
}

void NaoUsavel::ExibirInformacoes(void)
{
	cout << "\t//Nao usavel" << endl;
}

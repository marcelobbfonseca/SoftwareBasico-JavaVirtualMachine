#include<stdint.h>
#include "attribute_info.hpp"
#include"Leitura.hpp"
//#include<iostream>

namespace Atributos
{
	using namespace Leitura;
	ConstantValue_attribute::ConstantValue_attribute(FILE *arq, uint16_t attributeNameIndex)
	{
		this->attribute_name_index = attributeNameIndex;
		LerAtributo(&attribute_length, 4, arq);
		LerAtributo(&constantvalue_index, 2, arq);
	}
	Excecao::Excecao(FILE *arq)
	{
		LerAtributo(&start_pc, 2, arq);
		LerAtributo(&end_pc, 2, arq);
		LerAtributo(&handler_pc, 2, arq);
		LerAtributo(&catch_type, 2, arq);
	}
	Code_attribute::Code_attribute(FILE *arq, uint16_t attributeNameIndex)
	{
		this->attribute_name_index = attributeNameIndex;
		LerAtributo(&attribute_length, 4, arq);
		LerAtributo(&max_stack, 2, arq);
		LerAtributo(&max_locals, 2, arq);
		LerAtributo(&code_length, 4, arq);
		code = new uint8_t[code_length]; 
		LerAtributo(code, code_length, arq, IGNORAR_ENDIAN);
		LerAtributo(&exception_table_length, 2, arq);
		for(int cont=0 ; cont < exception_table_length; cont++)
		{
			Excecao *aux = new Excecao(arq);
			exception_table.push_back(*aux);
		}
		LerAtributo(&attributes_count, 2, arq);
		for(int cont=0; cont < attributes_count; cont++)
		{
			attribute_info *aux= LerAtributeInfo(arq);
			attributes.push_back(aux);
		}
	}

	Exceptions_attribute::Exceptions_attribute(FILE *arq, uint16_t attributeNameIndex)
	{
		this->attribute_name_index= attributeNameIndex;
		LerAtributo(&attribute_length, 4, arq);
		LerAtributo(&number_of_exceptions, 2, arq);
		for(int cont = 0; cont < number_of_exceptions; cont++)
		{
			uint16_t temp;
			LerAtributo(&temp, 2, arq);
			exception_index_table.push_back(temp);
		}
	}

	InfoDaClasse::InfoDaClasse(FILE *arq)
	{
		LerAtributo(&inner_class_info_index, 2, arq);
		LerAtributo(&outer_class_info_index, 2, arq);
		LerAtributo(&inner_name_index, 2, arq);
		LerAtributo(&inner_class_access_flags, 2, arq);
	}

	InnerClasses_attribute::InnerClasses_attribute(FILE *arq, uint16_t attributeNameIndex)
	{
		this->attribute_name_index= attributeNameIndex;
		LerAtributo(&attribute_length, 4, arq);
		LerAtributo(&number_of_classes, 2, arq);
		for(int cont=0; cont < number_of_classes; cont++)
		{
			InfoDaClasse *temp= new InfoDaClasse(arq);
			classes.push_back(*temp);
		}
	}

	EnclosingMethod_attribute::EnclosingMethod_attribute(FILE *arq, uint16_t attributeNameIndex)
	{
		this->attribute_name_index= attributeNameIndex;
		LerAtributo(&attribute_length, 4, arq);
		LerAtributo(&class_index, 2, arq);
		LerAtributo(&method_index, 2, arq);
	}

	Synthetic_attribute::Synthetic_attribute(FILE *arq, uint16_t attributeNameIndex)
	{
		this->attribute_name_index= attributeNameIndex;
		LerAtributo(&attribute_length, 4, arq);
	}

	Signature_attribute::Signature_attribute(FILE *arq, uint16_t attributeNameIndex)
	{
		this->attribute_name_index= attributeNameIndex;
		LerAtributo(&attribute_length, 4, arq);
		LerAtributo(&signature_index, 2, arq);
	}

	SourceFile_attribute::SourceFile_attribute(FILE *arq, uint16_t attributeNameIndex)
	{
		this->attribute_name_index= attributeNameIndex;
		LerAtributo(&attribute_length, 4, arq);
		LerAtributo(&sourcefile_index, 2, arq);
	}

	SourceDebugExtension_attribute::SourceDebugExtension_attribute(FILE *arq, uint16_t attributeNameIndex)
	{
		this->attribute_name_index= attributeNameIndex;
		LerAtributo(&attribute_length, 4, arq);
		debug_extension= new uint8_t[attribute_length];
		LerAtributo(debug_extension, attribute_length, arq, IGNORAR_ENDIAN);
	}

	Elemento_LineNumber::Elemento_LineNumber(FILE *arq)
	{
		LerAtributo(&start_pc, 2, arq);
		LerAtributo(&line_number, 2, arq);
	}

	LineNumberTable_attribute::LineNumberTable_attribute(FILE *arq, uint16_t attributeNameIndex)
	{
		this->attribute_name_index= attributeNameIndex;
		LerAtributo(&attribute_length, 4, arq);
		LerAtributo(&line_number_table_length, 2, arq);
		for(int cont=0; cont < line_number_table_length; cont++)
		{
			Elemento_LineNumber *temp= new Elemento_LineNumber(arq);
			elements_number_table.push_back(*temp);
		}
	}

	Elemento_local_variable::Elemento_local_variable(FILE *arq)
	{
		LerAtributo(&start_pc, 2, arq);
		LerAtributo(&length, 2, arq);
		LerAtributo(&name_index, 2, arq);
		LerAtributo(&descriptor_index, 2, arq);
		LerAtributo(&index, 2, arq);
	}

	LocalVariableTable_attribute::LocalVariableTable_attribute(FILE *arq, uint16_t attributeNameIndex)
	{
		this->attribute_name_index= attributeNameIndex;
		LerAtributo(&attribute_length, 4, arq);
		LerAtributo(&local_variable_table_length, 2, arq);
		for(int cont =0; cont < local_variable_table_length; cont++)
		{
			Elemento_local_variable *temp= new Elemento_local_variable(arq);
			local_variable_table.push_back(*temp);
		}
	}

	Elemento_LocalVariableType::Elemento_LocalVariableType(FILE *arq)
	{
		LerAtributo(&start_pc, 2, arq);
		LerAtributo(&length, 2, arq);
		LerAtributo(&name_index, 2, arq);
		LerAtributo(&signature_index, 2, arq);
		LerAtributo(&index, 2, arq);
	}

	LocalVariableTypeTable_attribute::LocalVariableTypeTable_attribute(FILE *arq, uint16_t attributeNameIndex)
	{
		this->attribute_name_index= attributeNameIndex;
		LerAtributo(&attribute_length, 4, arq);
		LerAtributo(&local_variable_type_table_length, 2, arq);
		for(int cont=0; cont< local_variable_type_table_length; cont++)
		{
			Elemento_LocalVariableType *temp= new Elemento_LocalVariableType(arq);
			local_variable_type_table.push_back(*temp);
		}
	}

	Deprecated_attribute::Deprecated_attribute(FILE *arq, uint16_t attributeNameIndex)
	{
		this->attribute_name_index= attributeNameIndex;
		LerAtributo(&attribute_length, 4, arq);
	}

}

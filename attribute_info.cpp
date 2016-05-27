#include<stdint.h>
#include "attribute_info.hpp"
#include"Leitura.hpp"
//#include<iostream>
/*
attribute_info* attribute_info::LerAtributeInfo(FILE *arq)
{
	LerAtributo(&attribute_name_index, 2, arq);
	
}
*/
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

	Elemento_Metodo_Bootstrap::Elemento_Metodo_Bootstrap(FILE *arq)
	{
		LerAtributo(&bootstrap_method_ref, 2, arq);
		LerAtributo(&num_bootstrap_arguments, 2, arq);
		for(int cont=0; cont < num_bootstrap_arguments; cont++)
		{
			int16_t temp;
			LerAtributo(&temp, 2, arq);
			bootstrap_arguments.push_back(temp);
		}
	}

	BootstrapMethods_attribute::BootstrapMethods_attribute(FILE *arq, uint16_t attributeNameIndex)
	{
		this->attribute_name_index= attributeNameIndex;
		LerAtributo(&attribute_length, 4, arq);
		LerAtributo(&num_bootstrap_methods, 2, arq);
		for(int cont =0; cont < num_bootstrap_methods; cont++)
		{
			Elemento_Metodo_Bootstrap *aux= new Elemento_Metodo_Bootstrap(arq);
			bootstrap_methods.push_back(*aux);
		}
	}
	
	RuntimeVisibleAnnotations_attribute::RuntimeVisibleAnnotations_attribute(FILE *arq, uint16_t attributeNameIndex)
	{
		this->attribute_name_index= attributeNameIndex;
		LerAtributo(&attribute_length, 4, arq);
		info= new uint8_t[attribute_length];
		LerAtributo(info, attribute_length, arq);
	}
	
	RuntimeInvisibleAnnotations_attribute::RuntimeInvisibleAnnotations_attribute(FILE *arq, uint16_t attributeNameIndex)
	{
		this->attribute_name_index= attributeNameIndex;
		LerAtributo(&attribute_length, 4, arq);
		info= new uint8_t[attribute_length];
		LerAtributo(info, attribute_length, arq);
	}
	
	RuntimeVisibleParameterAnnotations_attribute::RuntimeVisibleParameterAnnotations_attribute(FILE *arq, uint16_t attributeNameIndex)
	{
		this->attribute_name_index= attributeNameIndex;
		LerAtributo(&attribute_length, 4, arq);
		info= new uint8_t[attribute_length];
		LerAtributo(info, attribute_length, arq);
	}
	
	RuntimeInvisibleParameterAnnotations_attribute::RuntimeInvisibleParameterAnnotations_attribute(FILE *arq, uint16_t attributeNameIndex)
	{
		this->attribute_name_index= attributeNameIndex;
		LerAtributo(&attribute_length, 4, arq);
		info= new uint8_t[attribute_length];
		LerAtributo(info, attribute_length, arq);
	}
	
	AnnotationDefault_attribute::AnnotationDefault_attribute(FILE *arq, uint16_t attributeNameIndex)
	{
		this->attribute_name_index= attributeNameIndex;
		LerAtributo(&attribute_length, 4, arq);
		info= new uint8_t[attribute_length];
		LerAtributo(info, attribute_length, arq);
	}

	verification_type_info::verification_type_info(FILE *arq)
	{
		LerAtributo(&tag, 1, arq);
		if(tag==ITEM_Object || tag ==ITEM_Uninitialized)
		{
			LerAtributo(&cpoolOuOffset, 2, arq);
		}
	}

	stack_map_frame::stack_map_frame(FILE *arq)
	{
		LerAtributo(&frame_type, 1, arq);
		if(frame_type >= 247)
		{
			LerAtributo(&offset_delta, 2, arq);
		}
		if( ( 64 <= frame_type && frame_type <= 127 ) || frame_type == 247)
		{
			verification_type_info *temp= new verification_type_info(arq);
			this->stack.push_back(*temp);
		}
		if(252 <= frame_type && frame_type <= 254)
		{
			for(int cont=0 ; cont < frame_type-251 ; cont++)
			{
				verification_type_info *temp= new verification_type_info(arq);
				this->locals.push_back(*temp);
			}
		}
		if(frame_type == 255)
		{
			LerAtributo(&number_of_locals, 2, arq);
			for(int cont =0; cont < number_of_locals; cont++)
			{
				verification_type_info *temp= new verification_type_info(arq);
				this->locals.push_back(*temp);
			}
			LerAtributo(&number_of_stack_items, 2, arq);
			for(int cont =0; cont < number_of_stack_items; cont++)
			{
				verification_type_info *temp= new verification_type_info(arq);
				this->stack.push_back(*temp);
			}
		}
	}

	StackMapTable_attribute::StackMapTable_attribute(FILE *arq, uint16_t attributeNameIndex)
	{
		this->attribute_name_index= attributeNameIndex;
		LerAtributo(&attribute_length, 4, arq);
		LerAtributo(&number_of_entries, 2, arq);
		for(int cont=0; cont < number_of_entries; cont++)
		{
			stack_map_frame *temp= new stack_map_frame(arq);
			entries.push_back(*temp);
		}
	}
	
	
}

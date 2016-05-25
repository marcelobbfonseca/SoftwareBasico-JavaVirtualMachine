#include"Atributos.hpp"
#include"Leitura.hpp"

namespace Atributos
{
	using namespace Leitura;
	ConstantValue_attribute::ConstantValue_attribute(FILE *arq, uint16_t attributeNameIndex)
	{
		this->attribute_name_index = attributeNameIndex;
		LerAtributo(&attribute_length, 4, arq, EH_NUMERO);
		LerAtributo(&constantvalue_index, 2, arq, EH_NUMERO);
	}
	Excecao::Excecao(FILE *arq)
	{
		LerAtributo(&start_pc, 2, arq, EH_NUMERO);
		LerAtributo(&end_pc, 2, arq, EH_NUMERO);
		LerAtributo(&handler_pc, 2, arq, EH_NUMERO);
		LerAtributo(&catch_type, 2, arq, EH_NUMERO);
	}
	Code_attribute::Code_attribute(FILE *arq, uint16_t attributeNameIndex)
	{
		this->attribute_name_index = attributeNameIndex;
		LerAtributo(&attribute_length, 4, arq, EH_NUMERO);
		LerAtributo(&max_stack, 2, arq, EH_NUMERO);
		LerAtributo(&max_locals, 2, arq, EH_NUMERO);
		LerAtributo(&code_length, 4, arq, EH_NUMERO);
		code = new uint8_t[code_length]; 
		LerAtributo(code, code_length, arq);
		LerAtributo(&exception_table_length, 2, arq, EH_NUMERO);
		for(int cont=0 ; cont < exception_table_length; cont++)
		{
			Excecao *aux = new Excecao(arq);
			exception_table.push_back(*aux);
		}
		LerAtributo(&attributes_count, 2, arq, EH_NUMERO);
		for(int cont=0; cont < attributes_count; cont++)
		{
			attribute_info *aux= LerAtributeInfo(arq);
			attributes.push_back(aux);
		}
	}

	Exceptions_attribute::Exceptions_attribute(FILE *arq, uint16_t attributeNameIndex)
	{
		this->attribute_name_index= attributeNameIndex;
		LerAtributo(&attribute_length, 4, arq, EH_NUMERO);
		LerAtributo(&number_of_exceptions, 2, arq, EH_NUMERO);
		for(int cont = 0; cont M number_of_exceptions; cont++)
		{
			uint16_t temp;
			LerAtributo(&temp, 2, arq, EH_NUMERO);
			exception_index_table.push_back(temp);
		}
	}

	InfoDaClasse::InfoDaClasse(FILE *arq)
	{
		LerAtributo(&inner_class_info_index, 2, arq, EH_NUMERO);
		LerAtributo(&outer_class_info_index, 2, arq, EH_NUMERO);
		LerAtributo(&inner_name_index, 2, arq, EH_NUMERO);
		LerAtributo(&inner_class_access_flags, 2, arq, EH_NUMERO);
	}

	InnerClasses_attribute::InnerClasses_attribute(FILE *arq, uint16_t attributeNameIndex))
	{
		this->attribute_name_index= attributeNameIndex;
		LerAtributo(&attribute_length, 4, arq, EH_NUMERO);
		LerAtributo(&number_of_classes, 2, arq, EH_NUMERO);
		for(int cont=0; cont < number_of_classes; cont++)
		{
			InfoDaClasse *temp= new InfoDaClasse(arq);
			classes.push_back(*temp);
		}
	}

	EnclosingMethod_attribute::EnclosingMethod_attribute(FILE *arq, uint16_t attributeNameIndex)
	{
		this->attribute_name_index= attributeNameIndex;
		LerAtributo(&attribute_length, 4, arq, EH_NUMERO);
		LerAtributo(&clas_index, 2, arq, EH_NUMERO);
		LerAtributo(&method_index, 2, arq, EH_NUMERO);
	}

	Synthetic_attribute::synthetic_attribute(FILE *arq, uint16_t attributeNameIndex)
	{
		this->attribute_name_index= attributeNameIndex;
		LerAtributo(&attribute_length, 4, arq, EH_NUMERO);
	}

	Signature_attribute::Signature_attribute(FILE *arq, uint16_t attributeNameIndex)
	{
		this->attribute_name_index= attributeNameIndex;
		LerAtributo(&attribute_length, 4, arq, EH_NUMERO);
		LerAtributo(&signature_index, 2, arq, EH_NUMERO);
	}

	SourceFile_attribute::SourceFile_attribute(FILE *arq, uint16_t attributeNameIndex)
	{
		this->attribute_name_index= attributeNameIndex;
		LerAtributo(&attribute_length, 4, arq, EH_NUMERO);
		LerAtributo(&sourcefile_index, 2, arq, EH_NUMERO);
	}

	SourceDebugExtension_attribute::SourceDebugExtension_attribute(FILE *arq, uint16_t attributeNameIndex)
	{
		this->attribute_name_index= attributeNameIndex;
		LerAtributo(&attribute_length, 4, arq, EH_NUMERO);
		debug_extension= new uint8_t[attribute_length];
		LerAtributo(debug_extension, attribute_length, arq);
	}

}

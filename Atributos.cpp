#include"Atributos.hpp"
#include"Leitura.hpp"

namespace Atributos
{
	using namespace Leitura;
	ConstantValue_attribute::ConstantValue_attribute(FILE *arq)
	{
		LerAtributo(&attribute_name_index, 2, arq, EH_NUMERO);
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
	Code_attribute::Code_attribute(FILE *arq)
	{
		LerAtributo(&attribute_name_index, 2, arq, EH_NUMERO);
		LerAtributo(&attribute_length, 2, arq, EH_NUMERO);
		LerAtributo(&max_stack, 2, arq, EH_NUMERO);
		LerAtributo(&max_locals, 2, arq, EH_NUMERO);
		LerAtributo(&code_length, 4, arq, EH_NUMERO);
		code = new [code_length]uint8_t; 
		LerAtributo(code, code_length, arq);
		LerAtributo(&exception_table_length, 2 arq, EH_NUMERO);
		for(int cont=0 ; cont < exception_table_length; cont++)
		{
			Excecao *aux = new Excecao(arq)
			exception_table.push_back(*aux);
		}
		LerAtributo(&attributes_count, 2, arq, EH_NUMERO);
		for(int cont=0; cont < attributes_count; cont++)
		{
			attribute_info *aux= new attribute_info(arq);
			attributes.push_back(*aux);
		}
	}
}

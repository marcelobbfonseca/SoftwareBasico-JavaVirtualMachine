#include<stdint.h>
#include<stdio.h>
#include<vector>

namespace Atributos
{
	class ConstantValue_attribute
	{
		private:
			uint16_t attribute_name_index;
			uint32_t attribute_length;
			uint16_t constantvalue_index;
		public:
			ConstantValue_attribute(FILE *arq);
			void ExibirInformações(void);
	}

	class Excecao
	{
		private:
			uint16_t start_pc;
			uint16_t end_pc;
			uint16_t handler_pc;
			uint16_t catch_type;
		public:
			Excecao(FILE *arq);
			void ExibirInformações(void);
	}

	class Code_attribute
	{
		private:
			uint16_t attribute_name_index;
			uint32_t attribute_length;
			uint16_t max_stack;
			uint16_t max_locals;
			uint32_t code_length;
			uint8_t *code;
			uint16_t exception_table_length;
			vector<Excecao> exception_table;
			uint16_t attributes_count;
			vector<attribute_info> attributes;
		public:
			Code_attribute(FILE *arq);
			~Code_attribute(void);
			void ExibirInformações(void);
	}

	class StackMapTable_attribute
	{
		public:
			uint16_t attribute_name_index;
			uint32_t attribute_length;
			uint16_t number_of_entries;
			vector<stack_map_frame> entries;
	}
}

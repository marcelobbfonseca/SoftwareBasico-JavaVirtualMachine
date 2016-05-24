#include<stdint.h>
#include<stdio.h>

namespace Atributos
{
	class ConstantValue_attribute
	{
		private:
			uint16_t attribute_name_index;
			uint32_t attribute_length;
			uint16_t constantvalue_index;
		public:
			ConstantValue(FILE *arq);
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
			uint8_t code[code_length];
			uint16_t exception_table_length;
			{
				uint16_t start_pc;
				uint16_t end_pc;
				uint16_t handler_pc;
				uint16_t catch_type;
			} exception_table[exception_table_length];
			uint16_t attributes_count;
			attribute_info attributes[attributes_count];
		public:
			Code_attribute(FILE *arq);
			void ExibirInformações(void);
	}

	class StackMapTable_attribute
	{
		public:
			u2 attribute_name_index;
			u4 attribute_length;
			u2 number_of_entries;
			stack_map_frame entries[number_of_entries];
	}
}

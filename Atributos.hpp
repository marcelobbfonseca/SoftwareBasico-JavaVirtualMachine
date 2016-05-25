#include<stdint.h>
#include<stdio.h>
#include<vector>
#include"attribute_info.hpp"

namespace Atributos
{
	using namespace std;

	class ConstantValue_attribute: public attribute_info
	{
		private:
//			uint16_t attribute_name_index;
//			uint32_t attribute_length;
			uint16_t constantvalue_index;
		public:
			ConstantValue_attribute(FILE *arq, uint16_t attributeNameIndex);
			void ExibirInformacoes(void);
	};

	class Excecao
	{
		private:
			uint16_t start_pc;
			uint16_t end_pc;
			uint16_t handler_pc;
			uint16_t catch_type;
		public:
			Excecao(FILE *arq);
			void ExibirInformacoes(void);
	};

	class Code_attribute: public attribute_info
	{
		private:
			uint16_t max_stack;
			uint16_t max_locals;
			uint32_t code_length;
			uint8_t *code;
			uint16_t exception_table_length;
			vector<Excecao> exception_table;
			uint16_t attributes_count;
			vector<attribute_info *> attributes;
		public:
			Code_attribute(FILE *arq, uint16_t attributeNameIndex);
			~Code_attribute(void);
			void ExibirInformacoes(void);
	};

	class StackMapTable_attribute: public attribute_info
	{
		public:
			uint16_t number_of_entries;
//			vector<stack_map_frame> entries;
	};

	class Exceptions_attribute : public attribute_info
	{
		private:
			uint16_t number_of_exceptions;
			vector<uint16_t> exception_index_table;
		
		public:
			exceptions_attribute (FILE *arq, uint16_t attributeNameIndex);
			~exceptions_attribute ();
			void ExibirInformacoes(void);
	};

	class InfoDaClasse
	{
		private:
			uint16_t inner_class_info_index;
			uint16_t outer_class_info_index;
			uint16_t inner_name_index;
			uint16_t inner_class_access_flags;
		public:
			InfoDaClasse(FILE *arq);
			void ExibirInformacoes(void);
	}

	class InnerClasses_attribute: public attribute_info
	{
		private:
			uint16_t number_of_classes;
			vector<InfoDaClasse> classes;
		public:
			innerClasses_attribute(FILE *arq, uint16_t attributeNameIndex);
			void ExibirInformacoes(void);
	}

	class EnclosingMethod_attribute:public attribute_info
	{
		private:
			uint16_t class_index;
			uint16_t method_index;
		public:
			EnclosingMethod_attribute(FILE *arq, uint16_t attributeNameIndex);
			void ExibirInformacoes();
	}

	class Synthetic_attribute: public attribute_info
	{
		private:
		public:
			Synthetic_attribute(FILE *arq, uint16_t attributeNameIndex);
			void ExibirInformacoes(void);
	}

	class Signature_attribute:public attribute_info
	{
		private:
			uint16_t signature_index;
		public:
			Signature_attribute(FILE *arq, uint16_t attributeNameIndex);
			void ExibirInformacoes(void);
	}

	class SourceFile_attribute: public attribute_info
	{
		private:
			uint16_t sourcefile_index;
		public:
			SourceFile_attribute(FILE *arq, uint16_t attributeNameIndex);
			ExibirInformacoes();
	}

	class SourceDebugExtension_attribute: public attribute_info
	{
		private:
			uint8_t *debug_extension;
		public:
			SourceDebugExtension_attribute(FILE *arq, uint16_t attributeNameIndex);
			void ExibirInformacoes(void);
	}


}

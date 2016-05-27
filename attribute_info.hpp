#include<stdint.h>
#include<stdio.h>
#include<vector>
#include"cp_info.hpp"

#ifndef ATTRIBUTE_INFO_HPP
#define ATTRIBUTE_INFO_HPP

class attribute_info
{
	protected:
		uint16_t attribute_name_index;
		uint32_t attribute_length;
//	uint8_t *info;

	public:
	static attribute_info* LerAtributeInfo(FILE *arq, std::vector<cp_info*> const &constant_pool);
	virtual void ExibirInformacoes(void)=0;
};

//namespace Atributos
//{
	using namespace std;

	enum Tags_verification_type_info
	{
		ITEM_Top =0,
		ITEM_Integer = 1,
		ITEM_Float = 2,
		ITEM_Double = 3,
		ITEM_Long =4,
		ITEM_Null = 5,
		ITEM_UninitializedThis = 6,
		ITEM_Object = 7,
		ITEM_Uninitialized = 8
	};

	class ConstantValue_attribute: public attribute_info
	{
		private:
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
			Code_attribute(FILE *arq, uint16_t attributeNameIndex, std::vector<cp_info*> const &constant_pool);
			~Code_attribute(void);
			void ExibirInformacoes(void);
	};

	class Exceptions_attribute : public attribute_info
	{
		private:
			uint16_t number_of_exceptions;
			vector<uint16_t> exception_index_table;
	
		public:
			Exceptions_attribute (FILE *arq, uint16_t attributeNameIndex);
			~Exceptions_attribute ();
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
	};

	class InnerClasses_attribute: public attribute_info
	{
		private:
			uint16_t number_of_classes;
			vector<InfoDaClasse> classes;
		public:
			InnerClasses_attribute(FILE *arq, uint16_t attributeNameIndex);
			void ExibirInformacoes(void);
	};

	class EnclosingMethod_attribute:public attribute_info
	{
		private:
			uint16_t class_index;
			uint16_t method_index;
		public:
			EnclosingMethod_attribute(FILE *arq, uint16_t attributeNameIndex);
			void ExibirInformacoes();
	};

	class Synthetic_attribute: public attribute_info
	{
		private:
		public:
			Synthetic_attribute(FILE *arq, uint16_t attributeNameIndex);
			void ExibirInformacoes(void);
	};

	class Signature_attribute:public attribute_info
	{
		private:
			uint16_t signature_index;
		public:
			Signature_attribute(FILE *arq, uint16_t attributeNameIndex);
			void ExibirInformacoes(void);
	};

	class SourceFile_attribute: public attribute_info
	{
		private:
			uint16_t sourcefile_index;
		public:
			SourceFile_attribute(FILE *arq, uint16_t attributeNameIndex);
			void ExibirInformacoes(void);
	};

	class SourceDebugExtension_attribute: public attribute_info
	{
		private:
			uint8_t *debug_extension;
		public:
			SourceDebugExtension_attribute(FILE *arq, uint16_t attributeNameIndex);
			void ExibirInformacoes(void);
	};

	class Elemento_LineNumber
	{
		private:
			uint16_t start_pc;
			uint16_t line_number;
		public:
			Elemento_LineNumber(FILE *arq);
			void ExibirInformacoes(void);
	};

	class LineNumberTable_attribute: public attribute_info
	{
		private:
			uint16_t line_number_table_length;
			vector<Elemento_LineNumber> elements_number_table;
		public:
			LineNumberTable_attribute(FILE *arq, uint16_t attributeNameIndex);
			void ExibirInformacoes(void);
	};

	class Elemento_local_variable
	{
		private:
			uint16_t start_pc;
			uint16_t length;
			uint16_t name_index;
			uint16_t descriptor_index;
			uint16_t index;
		public:
			Elemento_local_variable(FILE *arq);
			void ExibirInformacoes(void);
	};

	class LocalVariableTable_attribute : public attribute_info
	{
		private:
			uint16_t local_variable_table_length;
			vector<Elemento_local_variable> local_variable_table;
		public:
			LocalVariableTable_attribute(FILE *arq, uint16_t attributeNameIndex);
			void ExibirInformacoes(void);
	};

	class Elemento_LocalVariableType
	{
		private:
			uint16_t start_pc;
			uint16_t length;
			uint16_t name_index;
			uint16_t signature_index;
			uint16_t index;
		public:
			Elemento_LocalVariableType(FILE *arq);
	};

	class LocalVariableTypeTable_attribute : public attribute_info
	{
		private:
			uint16_t local_variable_type_table_length;
			vector<Elemento_LocalVariableType>local_variable_type_table;
		public:
			LocalVariableTypeTable_attribute(FILE *arq, uint16_t attributeNameIndex);
			void ExibirInformacoes(void);
	};


	class Deprecated_attribute : public attribute_info
	{
		private:
		public:
			Deprecated_attribute(FILE *arq, uint16_t attributeNameIndex);
			void ExibirInformacoes(void);
	};
	
	class Elemento_Metodo_Bootstrap
	{
		private:
			uint16_t bootstrap_method_ref;
			uint16_t num_bootstrap_arguments;
			vector<uint16_t> bootstrap_arguments;
		public:
			Elemento_Metodo_Bootstrap(FILE *arq);
			void ExibirInformacoes(void);
	};
	
	class BootstrapMethods_attribute: public attribute_info
	{
		private:
			uint16_t num_bootstrap_methods;
			vector<Elemento_Metodo_Bootstrap>bootstrap_methods;
		public:
			BootstrapMethods_attribute(FILE *arq, uint16_t attributeNameIndex);
			void ExibirInformacoes(void);
	};
	
	class RuntimeVisibleAnnotations_attribute: public attribute_info//Foda-se essa classe. Muito imcompreensível.Fazendo um attribute_info genérico.
	{
		private:
			void *info;
		public:
			RuntimeVisibleAnnotations_attribute(FILE *arq, uint16_t attributeNameIndex);
			void ExibirInformacoes(void);
	};
	
	class RuntimeInvisibleAnnotations_attribute: public attribute_info//Foda-se essa classe. Muito imcompreensível.Fazendo um attribute_info genérico.
	{
		private:
			void *info;
		public:
			RuntimeInvisibleAnnotations_attribute(FILE *arq, uint16_t attributeNameIndex);
			~RuntimeInvisibleAnnotations_attribute();
			void ExibirInformacoes(void);
	};
	
	class RuntimeVisibleParameterAnnotations_attribute: public attribute_info//Foda-se essa classe. Muito imcompreensível. Fazendo um attribute_info genérico.
	{
		private:
			void *info;
		public:
			RuntimeVisibleParameterAnnotations_attribute(FILE *arq, uint16_t attributeNameIndex);
			void ExibirInformacoes(void);
	};
	
	class RuntimeInvisibleParameterAnnotations_attribute: public attribute_info//Foda-se essa classe. Muito imcompreensível.Fazendo um attribute_info genérico.
	{
		private:
			void *info;
		public:
			RuntimeInvisibleParameterAnnotations_attribute(FILE *arq, uint16_t attributeNameIndex);
			void ExibirInformacoes(void);
	};
	
	class AnnotationDefault_attribute: public attribute_info//Foda-se essa classe. Muito imcompreensível.Fazendo um attribute_info genérico.
	{
		private:
			void *info;
		public:
			AnnotationDefault_attribute(FILE *arq, uint16_t attributeNameIndex);
			void ExibirInformacoes(void);
	};

	class verification_type_info
	{
		private:
			uint8_t tag;
			uint16_t cpoolOuOffset;
		public:
			verification_type_info(FILE *arq);
			void ExibirInformacoes(void);
	};

	class stack_map_frame
	{
		private:
			int8_t frame_type;
			uint16_t offset_delta;
			uint16_t number_of_locals;
			vector<verification_type_info> locals;
			uint16_t number_of_stack_items;
			vector<verification_type_info> stack;
		public:
			stack_map_frame(FILE *arq);
			void ExibirInformacoes(void);
	};

	class StackMapTable_attribute : public attribute_info
	{
		private:
			uint16_t number_of_entries;
			vector<stack_map_frame> entries;
		public:
			StackMapTable_attribute(FILE *arq, uint16_t attributeNameIndex);
			void ExibirInformacoes(void);
	};
//}
#endif

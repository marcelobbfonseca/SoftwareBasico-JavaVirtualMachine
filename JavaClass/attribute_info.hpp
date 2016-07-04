#ifndef ATTRIBUTE_INFO_HPP
#define ATTRIBUTE_INFO_HPP

#include<stdint.h>
#include<stdio.h>
#include<vector>
#include<string>
#include"cp_info.hpp"
#include"Buffer.hpp"

#ifndef CP_INFO
class cp_info;
#endif
#ifndef JAVA_CLASS
class JavaClass;
#endif

#define ATTRIBUTE_INFO
class attribute_info
{
	protected:
		uint16_t attribute_name_index;
		uint32_t attribute_length;

	public:
		static attribute_info* LerAtributeInfo(FILE *arq, std::vector<cp_info*> const &constant_pool);
		static attribute_info* LerAtributeInfo(Buffer &buff, std::vector<cp_info*> const &constant_pool);
		virtual ~attribute_info(){}
		virtual void ExibirInformacoes(std::string tabs, JavaClass *javaClass)=0;
		uint16_t getAttributeNameIndex();
};

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
		ConstantValue_attribute(Buffer &buff, uint16_t attributeNameIndex);
		void ExibirInformacoes(std::string tabs, JavaClass *javaClass);
};

class Excecao
{
	private:
		uint16_t start_pc;
		uint16_t end_pc;
		uint16_t handler_pc;
		uint16_t catch_type;
	public:
//		Excecao(FILE *arq);
		Excecao(Buffer &buffer);
		void ExibirInformacoes(std::string tabs, JavaClass *javaClass);
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
		string ObterMinemonicoOpcode(uint8_t bytecode);
		void ExibirInfoOpCode(unsigned int *cont);
	public:
		Code_attribute(FILE *arq, uint16_t attributeNameIndex, std::vector<cp_info*> const &constant_pool);
		Code_attribute(Buffer &buff, uint16_t attributeNameIndex, std::vector<cp_info*> const &constant_pool);
		~Code_attribute(void);
		void ExibirInformacoes(std::string tabs, JavaClass *javaClass);

		Code_attribute& operator=(Code_attribute );
		Code_attribute(Code_attribute&);
		uint16_t getMaxLocals(void);
		uint8_t *getCode(void);
		uint32_t getCodeLength();
};

class Exceptions_attribute : public attribute_info
{
	private:
		uint16_t number_of_exceptions;
		vector<uint16_t> exception_index_table;

	public:
		Exceptions_attribute (FILE *arq, uint16_t attributeNameIndex);
		Exceptions_attribute (Buffer &buff, uint16_t attributeNameIndex);
		void ExibirInformacoes(std::string tabs, JavaClass *javaClass);
};

class InfoDaClasse
{
	private:
		uint16_t inner_class_info_index;
		uint16_t outer_class_info_index;
		uint16_t inner_name_index;
		uint16_t inner_class_access_flags;
	public:
		InfoDaClasse(Buffer &buffer);
		void ExibirInformacoes(std::string tabs, JavaClass *javaClass);
};

class InnerClasses_attribute: public attribute_info
{
	private:
		uint16_t number_of_classes;
		vector<InfoDaClasse> classes;
	public:
		InnerClasses_attribute(FILE *arq, uint16_t attributeNameIndex);
		InnerClasses_attribute(Buffer &buff, uint16_t attributeNameIndex);
		void ExibirInformacoes(std::string tabs, JavaClass *javaClass);
};

class EnclosingMethod_attribute:public attribute_info
{
	private:
		uint16_t class_index;
		uint16_t method_index;
	public:
		EnclosingMethod_attribute(FILE *arq, uint16_t attributeNameIndex);
		EnclosingMethod_attribute(Buffer &buff, uint16_t attributeNameIndex);
		void ExibirInformacoes(std::string tabs, JavaClass *javaClass);
};

class Synthetic_attribute: public attribute_info
{
	private:
	public:
		Synthetic_attribute(FILE *arq, uint16_t attributeNameIndex);
		Synthetic_attribute(Buffer &buff, uint16_t attributeNameIndex);
		void ExibirInformacoes(std::string tabs, JavaClass *javaClass);
};

class Signature_attribute:public attribute_info
{
	private:
		uint16_t signature_index;
	public:
		Signature_attribute(FILE *arq, uint16_t attributeNameIndex);
		Signature_attribute(Buffer &buff, uint16_t attributeNameIndex);
		void ExibirInformacoes(std::string tabs, JavaClass *javaClass);
};

class SourceFile_attribute: public attribute_info
{
	private:
		uint16_t sourcefile_index;
	public:
		SourceFile_attribute(FILE *arq, uint16_t attributeNameIndex);
		SourceFile_attribute(Buffer &buff, uint16_t attributeNameIndex);
		void ExibirInformacoes(std::string tabs, JavaClass *javaClass);
		//para implementar
		uint16_t GetSouceFileIndex(void);
};
//nao utilizar
class SourceDebugExtension_attribute: public attribute_info
{
	private:
		uint8_t *debug_extension;
	public:
		SourceDebugExtension_attribute(FILE *arq, uint16_t attributeNameIndex);
		SourceDebugExtension_attribute(Buffer &buff, uint16_t attributeNameIndex);
		~SourceDebugExtension_attribute();
		void ExibirInformacoes(std::string tabs, JavaClass *javaClass);
};

class Elemento_LineNumber
{
	private:
		uint16_t start_pc;
		uint16_t line_number;
	public:
		Elemento_LineNumber(Buffer &buffer);
		void ExibirInformacoes(std::string tabs, JavaClass *javaClass);
};

class LineNumberTable_attribute: public attribute_info
{
	private:
		uint16_t line_number_table_length;
		vector<Elemento_LineNumber> elements_number_table;
	public:
		LineNumberTable_attribute(FILE *arq, uint16_t attributeNameIndex);
		LineNumberTable_attribute(Buffer &buff, uint16_t attributeNameIndex);
		void ExibirInformacoes(std::string tabs, JavaClass *javaClass);
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
		Elemento_local_variable(Buffer &buffer);
		void ExibirInformacoes(std::string tabs, JavaClass *javaClass);
};

class LocalVariableTable_attribute : public attribute_info
{
	private:
		uint16_t local_variable_table_length;
		vector<Elemento_local_variable> local_variable_table;
	public:
		LocalVariableTable_attribute(FILE *arq, uint16_t attributeNameIndex);
		LocalVariableTable_attribute(Buffer &buff, uint16_t attributeNameIndex);
		void ExibirInformacoes(std::string tabs, JavaClass *javaClass);
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
		Elemento_LocalVariableType(Buffer &buffer);
		void ExibirInformacoes(std::string tabs, JavaClass *javaClass);
};

class LocalVariableTypeTable_attribute : public attribute_info
{
	private:
		uint16_t local_variable_type_table_length;
		vector<Elemento_LocalVariableType>local_variable_type_table;
	public:
		LocalVariableTypeTable_attribute(FILE *arq, uint16_t attributeNameIndex);
		LocalVariableTypeTable_attribute(Buffer &buff, uint16_t attributeNameIndex);
		void ExibirInformacoes(std::string tabs, JavaClass *javaClass);
};

class Deprecated_attribute : public attribute_info
{
	private:
	public:
		Deprecated_attribute(FILE *arq, uint16_t attributeNameIndex);
		Deprecated_attribute(Buffer &buff, uint16_t attributeNameIndex);
		void ExibirInformacoes(std::string tabs, JavaClass *javaClass);
};
//nao utilizar
class Elemento_Metodo_Bootstrap
{
	private:
		uint16_t bootstrap_method_ref;
		uint16_t num_bootstrap_arguments;
		vector<uint16_t> bootstrap_arguments;
	public:
		Elemento_Metodo_Bootstrap(Buffer &buff);
		void ExibirInformacoes(std::string tabs, JavaClass *javaClass);
};
//nao utilizar
class BootstrapMethods_attribute: public attribute_info
{
	private:
		uint16_t num_bootstrap_methods;
		vector<Elemento_Metodo_Bootstrap>bootstrap_methods;
	public:
		BootstrapMethods_attribute(FILE *arq, uint16_t attributeNameIndex);
		BootstrapMethods_attribute(Buffer &buff, uint16_t attributeNameIndex);
		void ExibirInformacoes(std::string tabs, JavaClass *javaClass);
};
//nao utilizar
class RuntimeVisibleAnnotations_attribute: public attribute_info//Foda-se essa classe. Muito imcompreensível.Fazendo um attribute_info genérico.
{
	private:
		uint8_t *info;
	public:
		RuntimeVisibleAnnotations_attribute(FILE *arq, uint16_t attributeNameIndex);
		RuntimeVisibleAnnotations_attribute(Buffer &buff, uint16_t attributeNameIndex);
		~RuntimeVisibleAnnotations_attribute();
		void ExibirInformacoes(std::string tabs, JavaClass *javaClass);
};
//nao utilizar
class RuntimeInvisibleAnnotations_attribute: public attribute_info//Foda-se essa classe. Muito imcompreensível.Fazendo um attribute_info genérico.
{
	private:
		uint8_t *info;
	public:
		RuntimeInvisibleAnnotations_attribute(FILE *arq, uint16_t attributeNameIndex);
		RuntimeInvisibleAnnotations_attribute(Buffer &buff, uint16_t attributeNameIndex);
		~RuntimeInvisibleAnnotations_attribute();
		void ExibirInformacoes(std::string tabs, JavaClass *javaClass);
};
//nao utilizar
class RuntimeVisibleParameterAnnotations_attribute: public attribute_info//Foda-se essa classe. Muito imcompreensível. Fazendo um attribute_info genérico.
{
	private:
		uint8_t *info;
	public:
		RuntimeVisibleParameterAnnotations_attribute(FILE *arq, uint16_t ttributeNameIndex);
		RuntimeVisibleParameterAnnotations_attribute(Buffer &buff, uint16_t ttributeNameIndex);
		~RuntimeVisibleParameterAnnotations_attribute();
		void ExibirInformacoes(std::string tabs, JavaClass *javaClass);
};
//nao utilizar
class RuntimeInvisibleParameterAnnotations_attribute: public attribute_info//Foda-se essa classe. Muito imcompreensível.Fazendo um attribute_info genérico.
{
	private:
		uint8_t *info;
	public:
		RuntimeInvisibleParameterAnnotations_attribute(FILE *arq, uint16_t ttributeNameIndex);
		RuntimeInvisibleParameterAnnotations_attribute(Buffer &buff, uint16_t ttributeNameIndex);
		~RuntimeInvisibleParameterAnnotations_attribute();
		void ExibirInformacoes(std::string tabs, JavaClass *javaClass);
};
//nao utilizar
class AnnotationDefault_attribute: public attribute_info//Foda-se essa classe. Muito incompreensível.Fazendo um attribute_info genérico.
{
	private:
		uint8_t *info;
	public:
		AnnotationDefault_attribute(FILE *arq, uint16_t attributeNameIndex);
		AnnotationDefault_attribute(Buffer &buff, uint16_t attributeNameIndex);
		~AnnotationDefault_attribute();
		void ExibirInformacoes(std::string tabs, JavaClass *javaClass);
};

class verification_type_info
{
	private:
		uint8_t tag;
		uint16_t cpoolOuOffset;
	public:
//		verification_type_info(FILE *arq);
		verification_type_info(Buffer &buffer);
		void ExibirInformacoes(std::string tabs, JavaClass *javaClass);
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
//		stack_map_frame(FILE *arq);
		stack_map_frame(Buffer &buffer);
		void ExibirInformacoes(std::string tabs, JavaClass *javaClass);
};

class StackMapTable_attribute : public attribute_info
{
	private:
		uint16_t number_of_entries;
		vector<stack_map_frame> entries;
	public:
		StackMapTable_attribute(FILE *arq, uint16_t attributeNameIndex);
		StackMapTable_attribute(Buffer &buff, uint16_t attributeNameIndex);
		void ExibirInformacoes(std::string tabs, JavaClass *javaClass);
};

//A especificação da JVM diz que não deve dar erro ler um atributo desconhecido, basta ignorá-lo. Essa classe apenas armazena o atributo desconecido na forma de um attribute info genérico.
class AtributoDesconhecido : public attribute_info
{
	private:
		uint8_t *info;
	public:
		AtributoDesconhecido(FILE *arq, uint16_t ttributeNameIndex);
		AtributoDesconhecido(Buffer &buff, uint16_t ttributeNameIndex);
		~AtributoDesconhecido();
		void ExibirInformacoes(std::string tabs, JavaClass *javaClass);
};
#endif

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
		void ExibirInfoOpCode(unsigned int *cont, JavaClass *javaClass);
		void ExibirCpIndex(unsigned int* cont, JavaClass *javaClass);
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

class Synthetic_attribute: public attribute_info
{
	private:
	public:
		Synthetic_attribute(FILE *arq, uint16_t attributeNameIndex);
		Synthetic_attribute(Buffer &buff, uint16_t attributeNameIndex);
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

class Deprecated_attribute : public attribute_info
{
	private:
	public:
		Deprecated_attribute(FILE *arq, uint16_t attributeNameIndex);
		Deprecated_attribute(Buffer &buff, uint16_t attributeNameIndex);
		void ExibirInformacoes(std::string tabs, JavaClass *javaClass);
};
//nao utilizar
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

#include "attribute_info.hpp"
#include"Leitura.hpp"
#include"Opcode.hpp"
#include<iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
using namespace Leitura;


/*
Então pessoal, Como tem muito C++ no método abaixo vou explicar:

	O objetivo desse método é simples: Ler o attribute_name_index do attribute_info, identificar que tipo de attribute_info é e chamar o construtor correto.

	Como lemos o attribute_name_index antes de criar o objeto, armazenamos o valor lido em uma variável temporára e seu valor será enviado ao construtor da classe correta.

	Após a leitura, precisamos verificar qual subclasse de attribute_info é indicada entreda no constant_pool na posição informado pelo attribute_name_index.
	OBS: Por isso esse método precisa ter acesso ao constant_pool
	OBS2: A especificação da JVM garante que essa nessa posição do constant_pool haverá um CONSTANT_Utf8_info(por isso faço o cast sem verificar)

	Aí fazemos o seguinte:
		-acessamos o constant_pool na posição lida;
		-fazemos um cast da posição lida de ponteiro de cp_info para ponteiro de CONSTANT_Utf8_info
		-acessamos o CONSTANT_Utf8_info indicado pelo ponteiro(olha o '*' pouco depois do if)
		-Usando a sobrecarga do operador == existente no CONSTANT_Utf8_info, verificamos se lá contem a 'string' testada.
		-chamados o construtor adequado passado o arquivo a ser lido e o attributeNameIndex.
*/
attribute_info* attribute_info::LerAtributeInfo(FILE *arq, std::vector<cp_info*> const &constant_pool)
{

	uint16_t attributeNameIndex;
	LerAtributo(&attributeNameIndex, 2, arq);
	if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex -1] ) )== "ConstantValue")
	{
		return new ConstantValue_attribute(arq, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex -1] ) )== "Code")
	{
		return new Code_attribute(arq, attributeNameIndex, constant_pool);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex -1] ) )== "StackMapTable")
	{
		return new StackMapTable_attribute(arq, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex -1] ) )== "Exceptions")
	{
		return new Exceptions_attribute(arq, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex -1] ) )== "InnerClasses")
	{
		return new InnerClasses_attribute(arq, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex -1] ) )== "EnclosingMethod")
	{
		return new EnclosingMethod_attribute(arq, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex -1] ) )== "Synthetic")
	{
		return new Synthetic_attribute(arq, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex -1] ) )== "Signature")
	{
		return new Signature_attribute(arq, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex -1] ) )== "SourceFile")
	{
		return new SourceFile_attribute(arq, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex -1] ) )== "SourceDebugExtension")
	{
		return new SourceDebugExtension_attribute(arq, attributeNameIndex);
	}

	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex -1] ) )== "LineNumberTable")
	{
		return new LineNumberTable_attribute(arq, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex -1] ) )== "LocalVariableTable")
	{
		return new LocalVariableTable_attribute(arq, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex -1] ) )== "LocalVariableTypeTable")
	{
		return new LocalVariableTypeTable_attribute(arq, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex -1] ) )== "Deprecated")
	{
		return new Deprecated_attribute(arq, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex -1] ) )== "RuntimeVisibleAnnotations")
	{
		return new RuntimeVisibleAnnotations_attribute(arq, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex -1] ) )== "RuntimeInvisibleAnnotations")
	{
		return new RuntimeInvisibleAnnotations_attribute(arq, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex -1] ) )== "RuntimeVisibleParameterAnnotations")
	{
		return new RuntimeVisibleParameterAnnotations_attribute(arq, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex -1] ) )== "RuntimeInvisibleParameterAnnotations")
	{
		return new RuntimeInvisibleParameterAnnotations_attribute(arq, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex -1] ) )== "AnnotationDefault")
	{
		return new AnnotationDefault_attribute(arq, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex -1] ) )== "BootstrapMethods")
	{
		return new BootstrapMethods_attribute(arq, attributeNameIndex);
	}
	else
	{
		printf("atributoLixo %d",attributeNameIndex);
		return new AtributoDesconhecido(arq, attributeNameIndex);
	}

}

attribute_info* attribute_info::LerAtributeInfo(Buffer &buffer, std::vector<cp_info*> const &constant_pool)
{


	uint16_t attributeNameIndex;
	buffer.Ler(&attributeNameIndex, 2);
	if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex -1] ) )== "ConstantValue")
	{
		return new ConstantValue_attribute(buffer, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex-1] ) )== "Code")
	{
		return new Code_attribute(buffer, attributeNameIndex, constant_pool);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex-1] ) )== "StackMapTable")
	{
		return new StackMapTable_attribute(buffer, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex-1] ) )== "Exceptions")
	{
		return new Exceptions_attribute(buffer, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex-1] ) )== "InnerClasses")
	{
		return new InnerClasses_attribute(buffer, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex-1] ) )== "EnclosingMethod")
	{
		return new EnclosingMethod_attribute(buffer, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex-1] ) )== "Synthetic")
	{
		return new Synthetic_attribute(buffer, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex-1] ) )== "Signature")
	{
		return new Signature_attribute(buffer, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex-1] ) )== "SourceFile")
	{
		return new SourceFile_attribute(buffer, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex-1] ) )== "SourceDebugExtension")
	{
		return new SourceDebugExtension_attribute(buffer, attributeNameIndex);
	}

	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex-1] ) )== "LineNumberTable")
	{
		return new LineNumberTable_attribute(buffer, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex-1] ) )== "LocalVariableTable")
	{
		return new LocalVariableTable_attribute(buffer, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex-1] ) )== "LocalVariableTypeTable")
	{
		return new LocalVariableTypeTable_attribute(buffer, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex-1] ) )== "Deprecated")
	{
		return new Deprecated_attribute(buffer, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex-1] ) )== "RuntimeVisibleAnnotations")
	{
		return new RuntimeVisibleAnnotations_attribute(buffer, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex-1] ) )== "RuntimeInvisibleAnnotations")
	{
		return new RuntimeInvisibleAnnotations_attribute(buffer, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex-1] ) )== "RuntimeVisibleParameterAnnotations")
	{
		return new RuntimeVisibleParameterAnnotations_attribute(buffer, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex-1] ) )== "RuntimeInvisibleParameterAnnotations")
	{
		return new RuntimeInvisibleParameterAnnotations_attribute(buffer, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex-1] ) )== "AnnotationDefault")
	{
		return new AnnotationDefault_attribute(buffer, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex-1] ) )== "BootstrapMethods")
	{
		return new BootstrapMethods_attribute(buffer, attributeNameIndex);
	}
	else
	{
		return new AtributoDesconhecido(buffer, attributeNameIndex);
	}
}


ConstantValue_attribute::ConstantValue_attribute(FILE *arq, uint16_t attributeNameIndex)
{
	this->attribute_name_index = attributeNameIndex;
	LerAtributo(&attribute_length, 4, arq);
	Buffer *buffer = new Buffer(arq, attribute_length);
	buffer->Ler(&constantvalue_index, 2);
	delete buffer;
}

ConstantValue_attribute::ConstantValue_attribute(Buffer &buff, uint16_t attributeNameIndex)
{
	this->attribute_name_index = attributeNameIndex;
	buff.Ler(&attribute_length, 4);
	Buffer *buffer = new Buffer(buff, attribute_length);
	buffer->Ler(&constantvalue_index, 2);
	delete buffer;
}

Excecao::Excecao(Buffer &buffer)
{
	buffer.Ler(&start_pc, 2);
	buffer.Ler(&end_pc, 2);
	buffer.Ler(&handler_pc, 2);
	buffer.Ler(&catch_type, 2);
}

Code_attribute::Code_attribute(FILE *arq, uint16_t attributeNameIndex, std::vector<cp_info*> const &constant_pool)
{
	this->attribute_name_index = attributeNameIndex;
	LerAtributo(&attribute_length, 4, arq);
	Buffer *buffer= new Buffer(arq, attribute_length);
	buffer->Ler(&max_stack, 2);
	buffer->Ler(&max_locals, 2);
	buffer->Ler(&code_length, 4);
	code = new uint8_t[code_length];
	buffer->Ler(code, code_length, IGNORAR_ENDIAN);
	buffer->Ler(&exception_table_length, 2);
	for(int cont=0 ; cont < exception_table_length; cont++)
	{
		Excecao *aux = new Excecao(*buffer);
		exception_table.push_back(*aux);
	}
	buffer->Ler(&attributes_count, 2);
	for(int cont=0; cont < attributes_count; cont++)
	{
		attribute_info *aux= LerAtributeInfo(*buffer, constant_pool);
		attributes.push_back(aux);
	}
	delete buffer;
}

Code_attribute::Code_attribute(Buffer &buff, uint16_t attributeNameIndex, std::vector<cp_info*> const &constant_pool)
{
	this->attribute_name_index = attributeNameIndex;
	buff.Ler(&attribute_length, 4);
	Buffer *buffer = new Buffer(buff, attribute_length);
	buffer->Ler(&max_stack, 2);
	buffer->Ler(&max_locals, 2);
	buffer->Ler(&code_length, 4);
	code = new uint8_t[code_length];
	buffer->Ler(code, code_length, IGNORAR_ENDIAN);
	buffer->Ler(&exception_table_length, 2);
	for(int cont=0 ; cont < exception_table_length; cont++)
	{
		Excecao *aux = new Excecao(*buffer);
		exception_table.push_back(*aux);
	}
	buffer->Ler(&attributes_count, 2);
	for(int cont=0; cont < attributes_count; cont++)
	{
		attribute_info *aux= LerAtributeInfo(*buffer, constant_pool);
		attributes.push_back(aux);
	}
	delete buffer;
}


Code_attribute::~Code_attribute()
{
	delete []code;
}

Exceptions_attribute::Exceptions_attribute(FILE *arq, uint16_t attributeNameIndex)
{
	this->attribute_name_index= attributeNameIndex;
	LerAtributo(&attribute_length, 4, arq);
	Buffer *buffer = new Buffer(arq, attribute_length);
	buffer->Ler(&number_of_exceptions, 2);
	for(int cont = 0; cont < number_of_exceptions; cont++)
	{
		uint16_t temp;
		buffer->Ler(&temp, 2);
		exception_index_table.push_back(temp);
	}
	delete buffer;
}

Exceptions_attribute::Exceptions_attribute(Buffer &buff, uint16_t attributeNameIndex)
{
	this->attribute_name_index= attributeNameIndex;
	buff.Ler(&attribute_length, 4);
	Buffer *buffer = new Buffer(buff, attribute_length);
	buffer->Ler(&number_of_exceptions, 2);
	for(int cont = 0; cont < number_of_exceptions; cont++)
	{
		uint16_t temp;
		buffer->Ler(&temp, 2);
		exception_index_table.push_back(temp);
	}
	delete buffer;
}

InfoDaClasse::InfoDaClasse(Buffer &buffer)
{
	buffer.Ler(&inner_class_info_index, 2);
	buffer.Ler(&outer_class_info_index, 2);
	buffer.Ler(&inner_name_index, 2);
	buffer.Ler(&inner_class_access_flags, 2);
}

InnerClasses_attribute::InnerClasses_attribute(FILE *arq, uint16_t attributeNameIndex)
{
	this->attribute_name_index= attributeNameIndex;
	LerAtributo(&attribute_length, 4, arq);
	Buffer *buffer= new Buffer(arq, attribute_length);
	buffer->Ler(&number_of_classes, 2, arq);
	for(int cont=0; cont < number_of_classes; cont++)
	{
		InfoDaClasse *temp= new InfoDaClasse(*buffer);
		classes.push_back(*temp);
	}
	delete buffer;
}

InnerClasses_attribute::InnerClasses_attribute(Buffer &buff, uint16_t attributeNameIndex)
{
	this->attribute_name_index= attributeNameIndex;
	buff.Ler(&attribute_length, 4);
	Buffer *buffer= new Buffer(buff, attribute_length);
	buffer->Ler(&number_of_classes, 2);
	for(int cont=0; cont < number_of_classes; cont++)
	{
		InfoDaClasse *temp= new InfoDaClasse(*buffer);
		classes.push_back(*temp);
	}
	delete buffer;
}

EnclosingMethod_attribute::EnclosingMethod_attribute(FILE *arq, uint16_t attributeNameIndex)
{
	this->attribute_name_index= attributeNameIndex;
	LerAtributo(&attribute_length, 4, arq);
	Buffer *buffer= new Buffer(arq, attribute_length);
	buffer->Ler(&class_index, 2);
	buffer->Ler(&method_index, 2);
	delete buffer;
}

EnclosingMethod_attribute::EnclosingMethod_attribute(Buffer &buff, uint16_t attributeNameIndex)
{
	this->attribute_name_index= attributeNameIndex;
	buff.Ler(&attribute_length, 4);
	Buffer *buffer= new Buffer(buff, attribute_length);
	buffer->Ler(&class_index, 2);
	buffer->Ler(&method_index, 2);
	delete buffer;
}

Synthetic_attribute::Synthetic_attribute(FILE *arq, uint16_t attributeNameIndex)
{
	this->attribute_name_index= attributeNameIndex;
	LerAtributo(&attribute_length, 4, arq);
}

Synthetic_attribute::Synthetic_attribute(Buffer &buff, uint16_t attributeNameIndex)
{
	this->attribute_name_index= attributeNameIndex;
	buff.Ler(&attribute_length, 4);
}

Signature_attribute::Signature_attribute(FILE *arq, uint16_t attributeNameIndex)
{
	this->attribute_name_index= attributeNameIndex;
	LerAtributo(&attribute_length, 4, arq);
	LerAtributo(&signature_index, 2, arq);
}

Signature_attribute::Signature_attribute(Buffer &buff, uint16_t attributeNameIndex)
{
	this->attribute_name_index= attributeNameIndex;
	buff.Ler(&attribute_length, 4);
	buff.Ler(&signature_index, 2);
}

SourceFile_attribute::SourceFile_attribute(FILE *arq, uint16_t attributeNameIndex)
{
	this->attribute_name_index= attributeNameIndex;
	LerAtributo(&attribute_length, 4, arq);
	LerAtributo(&sourcefile_index, 2, arq);
}

SourceFile_attribute::SourceFile_attribute(Buffer &buff, uint16_t attributeNameIndex)
{
	this->attribute_name_index= attributeNameIndex;
	buff.Ler(&attribute_length, 4);
	buff.Ler(&sourcefile_index, 2);
}

SourceDebugExtension_attribute::SourceDebugExtension_attribute(FILE *arq, uint16_t attributeNameIndex)
{
	this->attribute_name_index= attributeNameIndex;
	LerAtributo(&attribute_length, 4, arq);
	debug_extension= new uint8_t[attribute_length];
	LerAtributo(debug_extension, attribute_length, arq, IGNORAR_ENDIAN);
}

SourceDebugExtension_attribute::SourceDebugExtension_attribute(Buffer &buff, uint16_t attributeNameIndex)
{
	this->attribute_name_index= attributeNameIndex;
	buff.Ler(&attribute_length, 4);
	debug_extension= new uint8_t[attribute_length];
	buff.Ler(debug_extension, attribute_length, IGNORAR_ENDIAN);
}

SourceDebugExtension_attribute::~SourceDebugExtension_attribute()
{
	delete []debug_extension;
}

Elemento_LineNumber::Elemento_LineNumber(Buffer &buffer)
{
	buffer.Ler(&start_pc, 2);
	buffer.Ler(&line_number, 2);
}

LineNumberTable_attribute::LineNumberTable_attribute(FILE *arq, uint16_t attributeNameIndex)
{
	this->attribute_name_index= attributeNameIndex;
	LerAtributo(&attribute_length, 4, arq);
	Buffer *buffer= new Buffer(arq, attribute_length);
	buffer->Ler(&line_number_table_length, 2);
	for(int cont=0; cont < line_number_table_length; cont++)
	{
		Elemento_LineNumber *temp= new Elemento_LineNumber(*buffer);
		elements_number_table.push_back(*temp);
	}
	delete buffer;
}

LineNumberTable_attribute::LineNumberTable_attribute(Buffer &buff, uint16_t attributeNameIndex)
{
	this->attribute_name_index= attributeNameIndex;
	buff.Ler(&attribute_length, 4);
	Buffer *buffer= new Buffer(buff, attribute_length);
	buffer->Ler(&line_number_table_length, 2);
	for(int cont=0; cont < line_number_table_length; cont++)
	{
		Elemento_LineNumber *temp= new Elemento_LineNumber(*buffer);
		elements_number_table.push_back(*temp);
	}
	delete buffer;
}

Elemento_local_variable::Elemento_local_variable(Buffer &buffer)
{
	buffer.Ler(&start_pc, 2);
	buffer.Ler(&length, 2);
	buffer.Ler(&name_index, 2);
	buffer.Ler(&descriptor_index, 2);
	buffer.Ler(&index, 2);
}

LocalVariableTable_attribute::LocalVariableTable_attribute(FILE *arq, uint16_t attributeNameIndex)
{
	this->attribute_name_index= attributeNameIndex;
	LerAtributo(&attribute_length, 4, arq);
	Buffer *buffer = new Buffer(arq, attribute_length);
	buffer->Ler(&local_variable_table_length, 2);
	for(int cont =0; cont < local_variable_table_length; cont++)
	{
		Elemento_local_variable *temp= new Elemento_local_variable(*buffer);
		local_variable_table.push_back(*temp);
	}
	delete buffer;
}

LocalVariableTable_attribute::LocalVariableTable_attribute(Buffer &buff, uint16_t attributeNameIndex)
{
	this->attribute_name_index= attributeNameIndex;
	buff.Ler(&attribute_length, 4);
	Buffer *buffer = new Buffer(buff, attribute_length);
	buffer->Ler(&local_variable_table_length, 2);
	for(int cont =0; cont < local_variable_table_length; cont++)
	{
		Elemento_local_variable *temp= new Elemento_local_variable(*buffer);
		local_variable_table.push_back(*temp);
	}
	delete buffer;
}

Elemento_LocalVariableType::Elemento_LocalVariableType(Buffer &buffer)
{
	buffer.Ler(&start_pc, 2);
	buffer.Ler(&length, 2);
	buffer.Ler(&name_index, 2);
	buffer.Ler(&signature_index, 2);
	buffer.Ler(&index, 2);
}

LocalVariableTypeTable_attribute::LocalVariableTypeTable_attribute(FILE *arq, uint16_t attributeNameIndex)
{
	this->attribute_name_index= attributeNameIndex;
	LerAtributo(&attribute_length, 4, arq);
	Buffer *buffer = new Buffer (arq, attribute_length);
	buffer->Ler(&local_variable_type_table_length, 2);
	for(int cont=0; cont< local_variable_type_table_length; cont++)
	{
		Elemento_LocalVariableType *temp= new Elemento_LocalVariableType(*buffer);
		local_variable_type_table.push_back(*temp);
	}
	delete buffer;
}

LocalVariableTypeTable_attribute::LocalVariableTypeTable_attribute(Buffer &buff, uint16_t attributeNameIndex)
{
	this->attribute_name_index= attributeNameIndex;
	buff.Ler(&attribute_length, 4);
	Buffer *buffer = new Buffer (buff, attribute_length);
	buffer->Ler(&local_variable_type_table_length, 2);
	for(int cont=0; cont< local_variable_type_table_length; cont++)
	{
		Elemento_LocalVariableType *temp= new Elemento_LocalVariableType(*buffer);
		local_variable_type_table.push_back(*temp);
	}
	delete buffer;
}

Deprecated_attribute::Deprecated_attribute(FILE *arq, uint16_t attributeNameIndex)
{
	this->attribute_name_index= attributeNameIndex;
	LerAtributo(&attribute_length, 4, arq);
}

Deprecated_attribute::Deprecated_attribute(Buffer &buff, uint16_t attributeNameIndex)
{
	this->attribute_name_index= attributeNameIndex;
	buff.Ler(&attribute_length, 4);
}

Elemento_Metodo_Bootstrap::Elemento_Metodo_Bootstrap(Buffer &buffer)
{
	buffer.Ler(&bootstrap_method_ref, 2);
	buffer.Ler(&num_bootstrap_arguments, 2);
	for(int cont=0; cont < num_bootstrap_arguments; cont++)
	{
		int16_t temp;
		buffer.Ler(&temp, 2);
		bootstrap_arguments.push_back(temp);
	}
}

BootstrapMethods_attribute::BootstrapMethods_attribute(FILE *arq, uint16_t attributeNameIndex)
{
	this->attribute_name_index= attributeNameIndex;
	LerAtributo(&attribute_length, 4, arq);
	Buffer *buffer= new Buffer(arq, attribute_length);
	buffer->Ler(&num_bootstrap_methods, 2);
	for(int cont =0; cont < num_bootstrap_methods; cont++)
	{
		Elemento_Metodo_Bootstrap *aux= new Elemento_Metodo_Bootstrap(*buffer);
		bootstrap_methods.push_back(*aux);
	}
	delete buffer;
}

BootstrapMethods_attribute::BootstrapMethods_attribute(Buffer &buff, uint16_t attributeNameIndex)
{
	this->attribute_name_index= attributeNameIndex;
	buff.Ler(&attribute_length, 4);
	Buffer *buffer= new Buffer(buff, attribute_length);
	buffer->Ler(&num_bootstrap_methods, 2);
	for(int cont =0; cont < num_bootstrap_methods; cont++)
	{
		Elemento_Metodo_Bootstrap *aux= new Elemento_Metodo_Bootstrap(*buffer);
		bootstrap_methods.push_back(*aux);
	}
	delete buffer;
}

RuntimeVisibleAnnotations_attribute::RuntimeVisibleAnnotations_attribute(FILE *arq, uint16_t attributeNameIndex)
{
	this->attribute_name_index= attributeNameIndex;
	LerAtributo(&attribute_length, 4, arq);
	info= new uint8_t[attribute_length];
	LerAtributo(info, attribute_length, arq);
}

RuntimeVisibleAnnotations_attribute::RuntimeVisibleAnnotations_attribute(Buffer &buff, uint16_t attributeNameIndex)
{
	this->attribute_name_index= attributeNameIndex;
	buff.Ler(&attribute_length, 4);
	info= new uint8_t[attribute_length];
	buff.Ler(info, attribute_length);
}

RuntimeVisibleAnnotations_attribute::~RuntimeVisibleAnnotations_attribute()
{
	delete []info;
}

RuntimeInvisibleAnnotations_attribute::RuntimeInvisibleAnnotations_attribute(FILE *arq, uint16_t attributeNameIndex)
{
	this->attribute_name_index= attributeNameIndex;
	LerAtributo(&attribute_length, 4, arq);
	info= new uint8_t[attribute_length];
	LerAtributo(info, attribute_length, arq);
}

RuntimeInvisibleAnnotations_attribute::RuntimeInvisibleAnnotations_attribute(Buffer &buff, uint16_t attributeNameIndex)
{
	this->attribute_name_index= attributeNameIndex;
	buff.Ler(&attribute_length, 4);
	info= new uint8_t[attribute_length];
	buff.Ler(info, attribute_length);
}

RuntimeInvisibleAnnotations_attribute::~RuntimeInvisibleAnnotations_attribute()
{
	delete []info;
}

RuntimeVisibleParameterAnnotations_attribute::RuntimeVisibleParameterAnnotations_attribute(FILE *arq, uint16_t attributeNameIndex)
{
	this->attribute_name_index= attributeNameIndex;
	LerAtributo(&attribute_length, 4, arq);
	info= new uint8_t[attribute_length];
	LerAtributo(info, attribute_length, arq);
}

RuntimeVisibleParameterAnnotations_attribute::RuntimeVisibleParameterAnnotations_attribute(Buffer &buff, uint16_t attributeNameIndex)
{
	this->attribute_name_index= attributeNameIndex;
	buff.Ler(&attribute_length, 4);
	info= new uint8_t[attribute_length];
	buff.Ler(info, attribute_length);
}

RuntimeVisibleParameterAnnotations_attribute::~RuntimeVisibleParameterAnnotations_attribute()
{
	delete []info;
}

RuntimeInvisibleParameterAnnotations_attribute::RuntimeInvisibleParameterAnnotations_attribute(FILE *arq, uint16_t attributeNameIndex)
{
	this->attribute_name_index= attributeNameIndex;
	LerAtributo(&attribute_length, 4, arq);
	info= new uint8_t[attribute_length];
	LerAtributo(info, attribute_length, arq);
}

RuntimeInvisibleParameterAnnotations_attribute::RuntimeInvisibleParameterAnnotations_attribute(Buffer &buff, uint16_t attributeNameIndex)
{
	this->attribute_name_index= attributeNameIndex;
	buff.Ler(&attribute_length, 4);
	info= new uint8_t[attribute_length];
	buff.Ler(info, attribute_length);
}

RuntimeInvisibleParameterAnnotations_attribute::~RuntimeInvisibleParameterAnnotations_attribute()
{
	delete []info;
}

AnnotationDefault_attribute::AnnotationDefault_attribute(FILE *arq, uint16_t attributeNameIndex)
{
	this->attribute_name_index= attributeNameIndex;
	LerAtributo(&attribute_length, 4, arq);
	info= new uint8_t[attribute_length];
	LerAtributo(info, attribute_length, arq);
}

AnnotationDefault_attribute::AnnotationDefault_attribute(Buffer &buff, uint16_t attributeNameIndex)
{
	this->attribute_name_index= attributeNameIndex;
	buff.Ler(&attribute_length, 4);
	info= new uint8_t[attribute_length];
	buff.Ler(info, attribute_length);
}

AnnotationDefault_attribute::~AnnotationDefault_attribute()
{
	delete []info;
}

verification_type_info::verification_type_info(Buffer &buffer)
{
	buffer.Ler(&tag, 1);
	if(tag==ITEM_Object || tag ==ITEM_Uninitialized)
	{
		buffer.Ler(&cpoolOuOffset, 2);
	}
}

stack_map_frame::stack_map_frame(Buffer &buffer)
{
	buffer.Ler(&frame_type, 1);
	if(frame_type >= 247)
	{
		buffer.Ler(&offset_delta, 2);
	}
	if( ( 64 <= frame_type && frame_type <= 127 ) || frame_type == 247)
	{
		verification_type_info *temp= new verification_type_info(buffer);
		this->stack.push_back(*temp);
	}
	if(252 <= frame_type && frame_type <= 254)
	{
		for(int cont=0 ; cont < frame_type-251 ; cont++)
		{
			verification_type_info *temp= new verification_type_info(buffer);
			this->locals.push_back(*temp);
		}
	}
	if(frame_type == 255)
	{
		buffer.Ler(&number_of_locals, 2);
		for(int cont =0; cont < number_of_locals; cont++)
		{
			verification_type_info *temp= new verification_type_info(buffer);
			this->locals.push_back(*temp);
		}
		buffer.Ler(&number_of_stack_items, 2);
		for(int cont =0; cont < number_of_stack_items; cont++)
		{
			verification_type_info *temp= new verification_type_info(buffer);
			this->stack.push_back(*temp);
		}
	}
}

StackMapTable_attribute::StackMapTable_attribute(FILE *arq, uint16_t attributeNameIndex)
{
	this->attribute_name_index= attributeNameIndex;
	LerAtributo(&attribute_length, 4, arq);

	Buffer *buffer= new Buffer(arq, attribute_length);
	buffer->Ler(&number_of_entries, 2);
	for(int cont=0; cont < number_of_entries; cont++)
	{
		stack_map_frame *temp= new stack_map_frame(*buffer);
		entries.push_back(*temp);
	}
	delete buffer;
}

StackMapTable_attribute::StackMapTable_attribute(Buffer &buff, uint16_t attributeNameIndex)
{
	this->attribute_name_index= attributeNameIndex;
	buff.Ler(&attribute_length, 4);

	Buffer *buffer= new Buffer(buff, attribute_length);
	buffer->Ler(&number_of_entries, 2);
	for(int cont=0; cont < number_of_entries; cont++)
	{
		stack_map_frame *temp= new stack_map_frame(*buffer);
		entries.push_back(*temp);
	}
	delete buffer;
}

AtributoDesconhecido::AtributoDesconhecido(FILE *arq, uint16_t attributeNameIndex)
{
	this->attribute_name_index= attributeNameIndex;
	LerAtributo(&attribute_length, 4, arq);
	info= new uint8_t[attribute_length];
	LerAtributo(info, attribute_length, arq);
}

AtributoDesconhecido::AtributoDesconhecido(Buffer &buff, uint16_t attributeNameIndex)
{
	this->attribute_name_index= attributeNameIndex;
	buff.Ler(&attribute_length, 4);
	info= new uint8_t[attribute_length];
	buff.Ler(info, attribute_length);
}

AtributoDesconhecido::~AtributoDesconhecido()
{
	delete []info;
}

void ConstantValue_attribute::ExibirInformacoes(string tabs)
{
	cout << tabs << "attribute_info do tipo ConstantValue." <<endl;
	cout << tabs << "\tattribute_name_index = " << attribute_name_index << endl;
	cout << tabs << "\tattribute_length = " << attribute_length << endl;
	cout << tabs << "\tconstantvalue_index = " << constantvalue_index << endl;
}

void Excecao::ExibirInformacoes(string tabs)
{
	cout << tabs << "elemento do exception_table" <<endl;
	cout << tabs << "\tstart_pc = " << start_pc << endl;
	cout << tabs << "\tend_pc = " << end_pc << endl;
	cout << tabs << "\thandler_pc = " << handler_pc << endl;
	cout << tabs << "\tcatch_type = " << catch_type << endl;
}

void Code_attribute::ExibirInformacoes(string tabs)
{
	cout << tabs << "attribute_info do tipo Code." <<endl;
	cout << tabs << "\tattribute_name_index = " << attribute_name_index << endl;
	cout << tabs << "\tattribute_length = " << attribute_length << endl;
	cout << tabs << "\tmax_stack = " << max_stack << endl;
	cout << tabs << "\tmax_locals = " << max_locals << endl;
	cout << tabs << "\tcode_length = " << code_length << endl;
//	int aux=0;
	for(unsigned int cont=0; cont < code_length; cont++)
	{
		cout << tabs << "\t\t" << hex << cont << dec << "\t" << OpCode::GetReferencia()->GetMinemonico(code[cont]);
		ExibirInfoOpCode(&cont);
		cout << endl;
	}
	cout << tabs << "\tattributes_count = " << attributes_count << endl;
	cout << "-   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -" << endl;
	for(unsigned int cont =0; cont < attributes_count; cont++)
	{
		cout << tabs << "\tAttribute[" << cont << "]:" << endl;;
		attributes[cont]->ExibirInformacoes( ( (tabs + "\t") +"\t" ) );
		if(cont != attributes.size()-1)
		{
			cout << "-   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -" << endl;
		}
	}
}

void Exceptions_attribute::ExibirInformacoes(string tabs)
{
	cout << tabs << "attribute_info do tipo Exceptions." <<endl;
	cout << tabs << "\tnumber_of_exceptions = " << number_of_exceptions << endl;
	for(int cont=0 ; cont < number_of_exceptions ; cont++)
	{
		cout << tabs << "\texception_index_table[" << cont << "]:\t" << exception_index_table[cont] << endl;
	}
}

void InfoDaClasse::ExibirInformacoes(string tabs)
{
	cout << tabs << "inner_class_info_index = " << inner_class_info_index << endl;
	cout << tabs << "outer_class_info_index = " << outer_class_info_index << endl;
	cout << tabs << "inner_name_index = " << inner_name_index << endl;
	cout << tabs << "inner_class_access_flags = " << inner_class_access_flags << endl;
	if(inner_class_access_flags & 0x0001)
	{
		cout << tabs << "\tACC_PUBLIC" << endl;
	}
	if(inner_class_access_flags & 0x0002)
	{
		cout << tabs << "\tACC_PRIVATE" << endl;
	}
	if(inner_class_access_flags & 0x0004)
	{
		cout << tabs << "\tACC_PROTECTED" << endl;
	}
	if(inner_class_access_flags & 0x0008)
	{
		cout << tabs << "\tACC_STATIC" << endl;
	}
	if(inner_class_access_flags & 0x0010)
	{
		cout << tabs << "\tACC_FINAL" << endl;
	}
	if(inner_class_access_flags & 0x0200)
	{
		cout << tabs << "\tACC_INTERFACE" << endl;
	}
	if(inner_class_access_flags & 0x0400)
	{
		cout << tabs << "\tACC_ABSTRACT" << endl;
	}
	if(inner_class_access_flags & 0x1000)
	{
		cout << tabs << "\tACC_SYNTHETIC" << endl;
	}
	if(inner_class_access_flags & 0x2000)
	{
		cout << tabs << "\tACC_ANNOTATION" << endl;
	}
	if(inner_class_access_flags & 0x4000)
	{
		cout << tabs << "\tACC_ENUM" << endl;
	}
}

void InnerClasses_attribute::ExibirInformacoes(string tabs)
{
	cout << tabs << "attribute_info do tipo InnerClasses." <<endl;
	cout << tabs << "\tnumber_of_classes = " << number_of_classes << endl;
	for(unsigned int cont =0 ; cont < number_of_classes ; cont++)
	{
		cout << tabs << "\tclasses[" << cont << "]:" << endl;
		classes[cont].ExibirInformacoes( (tabs + "\t") +"\t");
	}
}

void EnclosingMethod_attribute::ExibirInformacoes(string tabs)
{
	cout << tabs << "attribute_info do tipo EnclosingMethod." <<endl;
	cout << tabs << "\tclass_index = " << class_index << endl;
	cout << tabs << "\tmethod_index = " << method_index << endl;
}

void Synthetic_attribute::ExibirInformacoes(string tabs)
{
	cout << tabs << "attribute_info do tipo Synthetic." << endl << endl;
}

void Signature_attribute::ExibirInformacoes(string tabs)
{
	cout << tabs << "attribute_info do tipo Signature." <<endl;
	cout << tabs << "\tsignature_index = " << signature_index << endl;
}

void SourceFile_attribute::ExibirInformacoes(string tabs)
{
	cout << tabs << "attribute_info do tipo SourceFile." <<endl;
	cout << tabs << "\tsourcefile_index = " << sourcefile_index << endl;
}

void SourceDebugExtension_attribute::ExibirInformacoes(string tabs)
{
	cout << tabs << "attribute_info do tipo SourceDebugExtension." <<endl;
	for(unsigned int cont =0; cont < attribute_length; cont++)
	{
		cout << tabs << "\tdebug_extension[ " << cont << "] = " << debug_extension[cont] << endl;
	}
}

void Elemento_LineNumber::ExibirInformacoes(string tabs)
{
	cout << tabs << "start_pc = " << start_pc << endl;
	cout << tabs << "line_number = " << start_pc << endl;
}

void LineNumberTable_attribute::ExibirInformacoes(string tabs)
{
	cout << tabs << "attribute_info do tipo LineNumberTable." <<endl;
	cout << tabs << "\tline_number_table_length = " << line_number_table_length <<endl;
	for(int cont=0; cont < line_number_table_length ; cont++)
	{
		cout << tabs << "\telements_number_table[" << cont << "]:" << endl;
		elements_number_table[cont].ExibirInformacoes( (tabs + "\t") +"\t");
	}
}

void Elemento_local_variable::ExibirInformacoes(string tabs)
{
	cout << tabs << "start_pc = " << start_pc <<endl;
	cout << tabs << "length = " << length <<endl;
	cout << tabs << "name_index = " << name_index <<endl;
	cout << tabs << "descriptor_index = " << descriptor_index <<endl;
	cout << tabs << "index = " << index <<endl;
}

void LocalVariableTable_attribute::ExibirInformacoes(string tabs)
{
	cout << tabs << "attribute_info do tipo LocalVariableTable." <<endl;
	cout << tabs << "\tlocal_variable_table_length = " << local_variable_table_length <<endl;
	for(int cont=0; cont < local_variable_table_length ; cont++)
	{
		cout << tabs << "\tlocal_variable_table[ " << cont << "]:" << endl;
		local_variable_table[cont].ExibirInformacoes( (tabs + "\t") +"\t");
	}
}

void Elemento_LocalVariableType::ExibirInformacoes(string tabs)
{
	cout << tabs << "start_pc = " << start_pc <<endl;
	cout << tabs << "length = " << length <<endl;
	cout << tabs << "name_index = " << name_index <<endl;
	cout << tabs << "signature_index = " << signature_index <<endl;
	cout << tabs << "index = " << index <<endl;
}

void LocalVariableTypeTable_attribute::ExibirInformacoes(string tabs)
{
	cout << tabs << "attribute_info do tipo LocalVariableTypeTable." <<endl;
	cout << tabs << "\tlocal_variable_type_table_length = " << local_variable_type_table_length <<endl;
	for(int cont=0; cont < local_variable_type_table_length ; cont++)
	{
		cout << tabs << "\tlocal_variable_type_table_length[ " << cont << "]:" << endl;
		local_variable_type_table[cont].ExibirInformacoes( (tabs + "\t") +"\t");
	}
}

void Deprecated_attribute::ExibirInformacoes(string tabs)
{
	cout << tabs << "attribute_info do tipo Deprecated." << endl << endl;
}

void Elemento_Metodo_Bootstrap::ExibirInformacoes(string tabs)
{
	cout << tabs << "bootstrap_method_ref = " << bootstrap_method_ref << endl;
	cout << tabs << "num_bootstrap_arguments = " << num_bootstrap_arguments << endl;
	for(int cont=0; cont < num_bootstrap_arguments ; cont++)
	{
		cout << tabs << "bootstrap_arguments[" << cont << "] = " << bootstrap_arguments[cont] << endl;
	}
}

void BootstrapMethods_attribute::ExibirInformacoes(string tabs)
{
	cout << tabs << "attribute_info do tipo BootstrapMethods." <<endl;
	cout << tabs << "\tnum_bootstrap_methods = " << num_bootstrap_methods <<endl;
	for(int cont=0; cont < num_bootstrap_methods ; cont++)
	{
		cout << tabs << "\tbootstrap_methods[ " << cont << "]:" << endl;
		bootstrap_methods[cont].ExibirInformacoes( (tabs + "\t") +"\t");
	}
}

void RuntimeVisibleAnnotations_attribute::ExibirInformacoes(string tabs)
{
	cout << tabs << "attribute_info do tipo RuntimeVisibleAnnotations." <<endl;
	cout << tabs << "\ttamanho em bytes: " << attribute_length << endl;
	cout << tabs << "\tinfo= 0x" << hex;
	for(unsigned int cont = 0; cont < attribute_length; cont++)
	{
		cout << info[cont];
	}
	cout << dec <<endl;
}

void RuntimeInvisibleAnnotations_attribute::ExibirInformacoes(string tabs)
{
	cout << tabs << "attribute_info do tipo RuntimeInvisibleAnnotations." <<endl;
	cout << tabs << "\ttamanho em bytes: " << attribute_length << endl;
	cout << tabs << "\tinfo= 0x" << hex;
	for(unsigned int cont = 0; cont < attribute_length; cont++)
	{
		cout << info[cont];
	}
	cout << dec <<endl;
}

void RuntimeVisibleParameterAnnotations_attribute::ExibirInformacoes(string tabs)
{
	cout << tabs << "attribute_info do tipo RuntimeVisibleParameterAnnotations." <<endl;
	cout << tabs << "\ttamanho em bytes: " << attribute_length << endl;
	cout << tabs << "\tinfo= 0x" << hex;
	for(unsigned int cont = 0; cont < attribute_length; cont++)
	{
		cout << info[cont];
	}
	cout << dec <<endl;
}

void RuntimeInvisibleParameterAnnotations_attribute::ExibirInformacoes(string tabs)
{
	cout << tabs << "attribute_info do tipo RuntimeInvisibleParameterAnnotations." <<endl;
	cout << tabs << "\ttamanho em bytes: " << attribute_length << endl;
	cout << tabs << "\tinfo= 0x" << hex;
	for(unsigned int cont = 0; cont < attribute_length; cont++)
	{
		cout << info[cont];
	}
	cout << dec <<endl;
}

void AnnotationDefault_attribute::ExibirInformacoes(string tabs)
{
	cout << tabs << "attribute_info do tipo AnnotationDefault." <<endl;
	cout << tabs << "\ttamanho em bytes: " << attribute_length << endl;
	cout << tabs << "\tinfo= 0x" << hex;
	for(unsigned int cont = 0; cont < attribute_length; cont++)
	{
		cout << info[cont];
	}
	cout << dec <<endl;
}

void verification_type_info::ExibirInformacoes(string tabs)
{
	cout << tabs << "tag = " << tag << "\t\t";
	if(tag==ITEM_Object)
	{
		cout << "//ITEM_Object" << endl;
		cout << tabs << "cpool_index = " << cpoolOuOffset << endl;
	}
	if(tag == ITEM_Uninitialized)
	{
		cout << "//ITEM_Uninitialized" << endl;
		cout << tabs << "offset = " << cpoolOuOffset << endl;
	}
}

void stack_map_frame::ExibirInformacoes(string tabs)
{
	cout << tabs << "frame_type = " << frame_type << endl;
	cout << tabs << "offset_delta = " << offset_delta << endl;
	cout << tabs << "number_of_locals = " << number_of_locals << endl;
	for(int cont =0; cont < number_of_locals ; cont++)
	{
		cout << tabs << "locals[" << cont << "]:" << endl;
		locals[cont].ExibirInformacoes(tabs + "\t");
	}
}

void StackMapTable_attribute::ExibirInformacoes(string tabs)
{
	cout << tabs << "attribute_info do tipo StackMapTable." <<endl;
	cout << tabs << "\tnumber_of_entries = " << number_of_entries <<endl;
	for(int cont=0; cont < number_of_entries ; cont++)
	{
		cout << tabs << "\tentries[ " << cont << "]:" << endl;
		entries[cont].ExibirInformacoes( (tabs + "\t") +"\t");
	}
}

void AtributoDesconhecido::ExibirInformacoes(string tabs)
{
	cout << tabs << "attribute_info do tipo AtributoDesconhecido." <<endl;
	cout << tabs << "\tattribute_name_index = " << attribute_name_index << endl;
	cout << tabs << "\ttamanho em bytes: " << attribute_length << endl;
	cout << tabs << "\tinfo= 0x" << hex;
	for(unsigned int cont = 0; cont < attribute_length; cont++)
	{
		if(info[cont]< 16)
		{
			cout << 0;
		}
		cout << (int) info[cont];
	}
	cout << dec <<endl;
}


void Code_attribute::ExibirInfoOpCode(unsigned int *cont)
{
	switch(code[*cont])
	{
		case(JAVA_OPCODE_ALOAD):
		case(JAVA_OPCODE_ASTORE):
		case(JAVA_OPCODE_DLOAD):
		case(JAVA_OPCODE_DSTORE):
		case(JAVA_OPCODE_FLOAD):
		case(JAVA_OPCODE_FSTORE):
		case(JAVA_OPCODE_ILOAD):
		case(JAVA_OPCODE_ISTORE):
		case(JAVA_OPCODE_LDC):
		case(JAVA_OPCODE_LLOAD):
		case(JAVA_OPCODE_LSTORE):
		{
			cout << "\tindex = " << (unsigned int)code[++(*cont)];
			break;
		}
		case(JAVA_OPCODE_ANEWARRAY):
		case(JAVA_OPCODE_CHECKCAST):
		case(JAVA_OPCODE_GETFIELD):
		case(JAVA_OPCODE_GETSTATIC):
		case(JAVA_OPCODE_INSTANCEOF):
		case(JAVA_OPCODE_INVOKESPECIAL):
		case(JAVA_OPCODE_INVOKESTATIC):
		case(JAVA_OPCODE_INVOKEVIRTUAL):
		case(JAVA_OPCODE_LDC_W):
		case(JAVA_OPCODE_LDC2_W):
		case(JAVA_OPCODE_PUTSTATIC):
		case(JAVA_OPCODE_PUTFIELD):
		case(JAVA_OPCODE_NEW):
		{
			cout << "\tindexbyte1 = " << (unsigned int)code[++(*cont)];
			cout << "\tindexbyte2 = " << (unsigned int)code[++(*cont)];
			break;
		}
		case(JAVA_OPCODE_BIPUSH):
		{
			cout << "\tbyte = " << (int32_t)code[++(*cont)];
			break;
		}
		case(JAVA_OPCODE_GOTO):
		case(JAVA_OPCODE_IF_ACMPEQ):
		case(JAVA_OPCODE_IF_ACMPNE):
		case(JAVA_OPCODE_IF_ICMPEQ):
		case(JAVA_OPCODE_IF_ICMPNE):
		case(JAVA_OPCODE_IF_ICMPLT):
		case(JAVA_OPCODE_IF_ICMPGE):
		case(JAVA_OPCODE_IF_ICMPGT):
		case(JAVA_OPCODE_IF_ICMPLE):
		case(JAVA_OPCODE_IFEQ):
		case(JAVA_OPCODE_IFNE):
		case(JAVA_OPCODE_IFLT):
		case(JAVA_OPCODE_IFGE):
		case(JAVA_OPCODE_IFGT):
		case(JAVA_OPCODE_IFLE):
		case(JAVA_OPCODE_IFNONNULL):
		case(JAVA_OPCODE_IFNULL):
		case(JAVA_OPCODE_JSR):
		{
			cout << "\tbranchbyte1 = " << (unsigned int)code[++(*cont)];
			cout << "\tbranchbyte2 = " << (unsigned int)code[++(*cont)];
			break;
		}
		case(JAVA_OPCODE_GOTO_W):
		case(JAVA_OPCODE_JSR_W):
		{
			cout << "\tbranchbyte1 = " << (unsigned int)code[++(*cont)];
			cout << "\tbranchbyte2 = " << (unsigned int)code[++(*cont)];
			cout << "\tbranchbyte3 = " << (unsigned int)code[++(*cont)];
			cout << "\tbranchbyte4 = " << (unsigned int)code[++(*cont)];
			break;
		}
		case(JAVA_OPCODE_IINC):
		{
			cout << "\tindex = " << (unsigned int)code[++(*cont)];
			cout << "\tconst = " << (unsigned int)code[++(*cont)];
			break;
		}
		case(JAVA_OPCODE_INVOKEDYNAMIC):
		{
			cout << "\tindexbyte1 = " << (unsigned int)code[++(*cont)];
			cout << "\tindexbyte2 = " << (unsigned int)code[++(*cont)];
			(*cont)= (*cont)+2;
			break;
		}
		case(JAVA_OPCODE_INVOKEINTERFACE):
		{
			cout << "\tindexbyte1 = " << (unsigned int)code[++(*cont)];
			cout << "\tindexbyte2 = " << (unsigned int)code[++(*cont)];
			cout << "\tcount = " << (unsigned int)code[++(*cont)];
			(*cont)++;
			break;
		}

		case(JAVA_OPCODE_SIPUSH):
		{
			cout << "\t byte1 = " << (unsigned int)code[++(*cont)];
			cout << "\t byte2 = " << (unsigned int)code[++(*cont)];
			break;
		}
		case(JAVA_OPCODE_RET):
		{
			uint32_t *aux= (uint32_t*) ( &(code[ (*cont)+1 ] ) );
			cout << "\t index = " << *aux;
			cont+= 4;
			break;
		}
		case(JAVA_OPCODE_NEWARRAY):
		{
			/*Array Type atype
			T_BOOLEAN	4
			T_CHAR	   5
			T_FLOAT	  6
			T_DOUBLE	 7
			T_BYTE	   8
			T_SHORT	  9
			T_INT		10
			T_LONG	   11*/
			cout << "\t atype = " << (unsigned int)code[++(*cont)];
			break;
		}
		case(JAVA_OPCODE_MULTIANEWARRAY):
		{
			cout << "\t indexbyte1 = " << (unsigned int)code[++(*cont)];
			cout << "\t indexbyte2 = " << (unsigned int)code[++(*cont)];
			cout << "\t dimension = " << (unsigned int)code[++(*cont)];
			break;
		}
		case(JAVA_OPCODE_LOOKUPSWITCH):
		{
			(*cont)++;
			if((*cont) % 4 != 0)
			{
				unsigned int temp= *cont;
				(*cont) = temp + (4 - ( temp % 4));
			}
			cout << "\t defaultbyte1 = " << (unsigned int)code[*cont];
			cout << "\t defaultbyte2 = " << (unsigned int)code[++(*cont)];
			cout << "\t defaultbyte3 = " << (unsigned int)code[++(*cont)];
			cout << "\t defaultbyte4 = " << (unsigned int)code[++(*cont)];

			cout << "\t npair1 = " << (unsigned int)code[++(*cont)];
			cout << "\t npair2 = " << (unsigned int)code[++(*cont)];
			cout << "\t npair3 = " << (unsigned int)code[++(*cont)];
			cout << "\t npair4 = " << (unsigned int)code[++(*cont)];

			for(int i = 0; i < 4 ;i++){
				(*cont)++;
				uint32_t *npair=  (uint32_t*) ( &(code[*cont]) );
				(*cont) += 4;
				uint32_t *offset= (uint32_t*) ( &(code[*cont]) );
				cout << "\t npair " << i << ":" << *npair << "\t offset: " << offset;
				cont+= 4;

			}
			(*cont)--;//o ponteiro não deve parar no próximo bytecode, mas no último byte lido
			break;
		}
		case(JAVA_OPCODE_WIDE):
		{
			cout << " " << OpCode::GetReferencia()->GetMinemonico(code[++(*cont)]);
			switch(code[(*cont)])
			{
				case(JAVA_OPCODE_ILOAD):
				case(JAVA_OPCODE_FLOAD):
				case(JAVA_OPCODE_ALOAD):
				case(JAVA_OPCODE_LLOAD):
				case(JAVA_OPCODE_DLOAD):
				case(JAVA_OPCODE_ISTORE):
				case(JAVA_OPCODE_FSTORE):
				case(JAVA_OPCODE_ASTORE):
				case(JAVA_OPCODE_LSTORE):
				case(JAVA_OPCODE_DSTORE):
				case(JAVA_OPCODE_RET):
				{
					cout << "\tindexbyte1 = " << (unsigned int)code[++(*cont)];
					cout << "\tindexbyte2 = " << (unsigned int)code[++(*cont)];
				}
				case(JAVA_OPCODE_IINC):
				{
					cout << "\tindexbyte1 = " << (unsigned int)code[++(*cont)];
					cout << "\tindexbyte2 = " << (unsigned int)code[++(*cont)];

					cout << "\tconstbyte1 = " << (unsigned int)code[++(*cont)];
					cout << "\tconstbyte2 = " << (unsigned int)code[++(*cont)];
				}
			}
		}
		case(JAVA_OPCODE_TABLESWITCH):
		{
			(*cont)++;

			if(*cont % 4 != 0)
			{
				unsigned int temp= *cont;
				(*cont) = temp + (4 - ( temp % 4));
			}

			int32_t *defaultbytes =  (int32_t*) ( &(code[*cont]));
			cout << "\t defaultbyte = " << defaultbytes;

			int32_t *lowbytes =  (int32_t*) ( &(code[*cont]));
			cout << "\t lowbytes = " << lowbytes;

			int32_t *highbytes =  (int32_t*) ( &(code[*cont]));
			cout << "\t highbytes = " << highbytes;

			int32_t *high_minus_low_more_one_bytes =  (int32_t*) ( &(code[*cont]));
			cout << "\t jump_offsets = " << high_minus_low_more_one_bytes;

			(*cont)--;//o ponteiro não deve parar no próximo bytecode, mas no último byte lido
			break;
		}
	}
}

uint16_t attribute_info::getAttributeNameIndex()
{
	return attribute_name_index;
}

uint16_t SourceFile_attribute::GetSouceFileIndex(void)
{
	return sourcefile_index;
}

uint16_t Code_attribute::getMaxLocals(void)
{
    return max_locals;
}

uint8_t Code_attribute::getCode(void)
{
    return *code;
}

uint32_t Code_attribute::getCodeLength(void)
{
    return code_length;
}

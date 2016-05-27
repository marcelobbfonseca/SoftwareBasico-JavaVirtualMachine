#include<stdint.h>
#include "attribute_info.hpp"
#include"Leitura.hpp"
#include"Opcodes.hpp"
//#include<iostream>

//using namespace Atributos;
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
	if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex] ) )== "ConstantValue")
	{
		return new ConstantValue_attribute(arq, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex] ) )== "Code")
	{
		return new Code_attribute(arq, attributeNameIndex, constant_pool);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex] ) )== "StackMapTable")
	{
		return new StackMapTable_attribute(arq, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex] ) )== "Exceptions")
	{
		return new Exceptions_attribute(arq, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex] ) )== "InnerClasses")
	{
		return new InnerClasses_attribute(arq, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex] ) )== "EnclosingMethod")
	{
		return new EnclosingMethod_attribute(arq, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex] ) )== "Synthetic")
	{
		return new Synthetic_attribute(arq, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex] ) )== "Signature")
	{
		return new Signature_attribute(arq, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex] ) )== "SourceFile")
	{
		return new SourceFile_attribute(arq, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex] ) )== "SourceDebugExtension")
	{
		return new SourceDebugExtension_attribute(arq, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex] ) )== "LineNumberTable")
	{
		return new LineNumberTable_attribute(arq, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex] ) )== "LocalVariableTable")
	{
		return new LocalVariableTable_attribute(arq, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex] ) )== "LocalVariableTypeTable")
	{
		return new LocalVariableTypeTable_attribute(arq, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex] ) )== "Deprecated")
	{
		return new Deprecated_attribute(arq, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex] ) )== "RuntimeVisibleAnnotations")
	{
		return new RuntimeVisibleAnnotations_attribute(arq, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex] ) )== "RuntimeInvisibleAnnotations")
	{
		return new RuntimeInvisibleAnnotations_attribute(arq, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex] ) )== "RuntimeVisibleParameterAnnotations")
	{
		return new RuntimeVisibleParameterAnnotations_attribute(arq, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex] ) )== "RuntimeInvisibleParameterAnnotations")
	{
		return new RuntimeInvisibleParameterAnnotations_attribute(arq, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex] ) )== "AnnotationDefault")
	{
		return new AnnotationDefault_attribute(arq, attributeNameIndex);
	}
	else if( *( ( CONSTANT_Utf8_info *) ( constant_pool[attributeNameIndex] ) )== "BootstrapMethods")
	{
		return new BootstrapMethods_attribute(arq, attributeNameIndex);
	}
	else
	{
		char msgErro[200];
		sprintf(msgErro, "LerAtributeInfo leu um atributo desconhecido.\n\tattribute_name_index= %d\n", attributeNameIndex);
		throw new Erro(msgErro);
	}
}

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

Code_attribute::Code_attribute(FILE *arq, uint16_t attributeNameIndex, std::vector<cp_info*> const &constant_pool)
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
		attribute_info *aux= LerAtributeInfo(arq, constant_pool);
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

void ConstantValue_attribute::void ExibirInformacoes(string tabs)
{
	cout << tabs << "attribute_info do tipo ConstantValue_attribute." <<endl;
	cout << tabs << "\tattribute_name_index = " << attribute_name_index << endl;
	cout << tabs << "\tattribute_length = " << attribute_length << endl;
	cout << tabs << "\tconstantvalue_index = " << constantvalue_index << endl;
}

void Excecao::void ExibirInformacoes(string tabs)
{
	cout << tabs << "elemento do exception_table" <<endl;
	cout << tabs << "\tstart_pc = " << start_pc << endl;
	cout << tabs << "\tend_pc = " << end_pc << endl;
	cout << tabs << "\thandler_pc = " << handler_pc << endl;
	cout << tabs << "\tcatch_type = " << catch_type << endl;
}

void Code_attribute::void ExibirInformacoes(string tabs)
{
	cout << tabs << "attribute_info do tipo Code_attribute." <<endl;
	cout << tabs << "\tattribute_name_index = " << attribute_name_index << endl;
	cout << tabs << "\tattribute_length = " << attribute_length << endl;
	cout << tabs << "\tmax_stack = " << max_stack << endl;
	cout << tabs << "\tmax_locals = " << max_locals << endl;
	cout << tabs << "\tcode_length = " << code_length << endl;
	for(int cont=0; cont < code_length; cont++)
	{
		cout << tabs << "\t\t" << hex << code[cont] << dec << "\t" << ObterMinemonicoOpcode(code[cont]) << endl;
	}
	cout << tabs << "\tattributes_count = " << attributes_count << endl;
	cout << "-   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -" << endl;
	for(int cont =0; cont < attributes_count; cont++)
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
	cout << tabs << "attribute_info do tipo Exceptions_attribute." <<endl;
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
	cout << tabs << "attribute_info do tipo InnerClasses_attribute." <<endl;
	cout << tabs << "number_of_classes = " << number_of_classes << endl;
	for(int cont =0 < cont < number_of_classes ; cont++)
	{
		cout << tabs << "classes[" << cont << "]:" << endl;
		classes[cont].ExibirInformacoes(tabs + "\t");
	}
}



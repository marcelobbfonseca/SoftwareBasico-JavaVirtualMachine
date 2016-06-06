#include<stdint.h>
#include<stdio.h>
#include<string>

#ifndef CP_INFO_HPP
#define CP_INFO_HPP

	//! Enumeração que indica os "tipos" de cpinfo
	/*! Enumeração que indica os valores que a tag do cpinfo pode assumir */
	//!\todo Verificar se vale a pena isolar enumerações em namespaces
enum cpInfoTags
{
	CONSTANT_Class=7,
	CONSTANT_Fieldref=9,
	CONSTANT_Methodref=10,
	CONSTANT_InterfaceMethodref=11,
	CONSTANT_String=8,
	CONSTANT_Integer=3,
	CONSTANT_Float=4,
	CONSTANT_Long=5,
	CONSTANT_Double=6,
	CONSTANT_NameAndType=12,
	CONSTANT_Utf8=1,
	CONSTANT_MethodHandle=15,
	CONSTANT_MethodType=16,
	CONSTANT_InvokeDynamic=18,
	TagNaoUsavel= 50
};

	//!\todo Verificar se vale a pena isolar enumerações em namespaces
enum referenceKinds
{
	REF_getField = 1,			//getfield C.f:T
	REF_getStatic = 2,			//getstatic C.f:T
	REF_putField = 3,			//putfield C.f:T
	REF_putStatic = 4,			//putstatic C.f:T
	REF_invokeVirtual = 5,		//invokevirtual C.m:(A*)T
	REF_invokeStatic = 6,		//invokestatic C.m:(A*)T
	REF_invokeSpecial = 7,		//invokespecial C.m:(A*)T
	REF_newInvokeSpecial = 8,	//new C; dup; invokespecial C.<init>:(A*)void
	REF_invokeInterface = 9		//invokeinterface C.m:(A*)T
};

//!  Contém informações que serão usadas posteriormente
/*!
  Contém informações simbólicas de classes, interfaces, arrays e instâncias
*/
class cp_info
{
	public:
   //! Método estático responsável pela criação de cpinfos
	/*!
	Método responsável pela leitura da tag, criação do cpinfo correspondente e preenchimento do mesmo.
	  \param arq Arquivo cujo cp é o próximo elemento a ser lido.
	  \return Retorna um filho de cpinfo devidamente preenchido
	*/
		static cp_info* LerCpInfo(FILE *arq);
		virtual void ExibirInformacoes(void) = 0;
		virtual ~cp_info(void){}
	private:
	protected:
	//! Tag que indica de qual filho deve ser usado
	/*!
		Deve armazenar um cpInfoTags válido.
	*/
		uint8_t tag;
};

//! Classe usada para representar uma classe ou interface Java
/*!
	Seu tag possui o valor CONSTANT_Class(7)
*/
class CONSTANT_Class_info:public cp_info
{
	public:
		CONSTANT_Class_info(uint16_t nameIndex);
		void ExibirInformacoes(void);
	private:
//!inteiro sem sinal de 2 bytes
/*!
O valor de nameIndex tem que ser um valor válido no vetor de constant_pool.
E deve referenciar um CONSTANT_Utf8_info, que representa uma classe binária ou interface com nome codificado na forma interna.
*/
		uint16_t name_index;
};

//! Classe utilizada para representar um campo de uma classe ou interface
class CONSTANT_Fieldref_info:public cp_info
{
	public:
		CONSTANT_Fieldref_info(uint16_t classIndex, uint16_t nameAndTypeIndex);
		void ExibirInformacoes(void);
	private:
		uint16_t class_index;
		uint16_t name_and_type_index;
};

//! Classe utilizada para representar um método de uma classe
class CONSTANT_Methodref_info:public cp_info
{
	public:
		CONSTANT_Methodref_info(uint16_t classIndex, uint16_t nameAndTypeIndex);
		void ExibirInformacoes(void);
	private:
		uint16_t class_index;
		uint16_t name_and_type_index;
};

//! Classe utilizada para representar um método de uma interface
class CONSTANT_InterfaceMethodref_info:public cp_info
{
	public:
		CONSTANT_InterfaceMethodref_info(uint16_t classIndex, uint16_t nameAndTypeIndex);
		void ExibirInformacoes(void);
	private:
		uint16_t class_index;
		uint16_t name_and_type_index;
};

//!Classe utilizada para armazenar referências para strings
class CONSTANT_String_info:public cp_info
{
	public:
		CONSTANT_String_info(uint16_t stringIndex);
		void ExibirInformacoes(void);
	private:
//!inteiro sem sinal de 2 bytes
/*!
O valor de string tem que ser um valor válido no vetor de constant_pool.
E deve referenciar um CONSTANT_Utf8_info, que representa em pontos unicode com o qual a string deve ser inicializada.
*/
		uint16_t string_index;
};

//!Classe usada para armazenar inteiros constantes de 32 bits com sinal.
class CONSTANT_Integer_info: public cp_info
{
	public:
		CONSTANT_Integer_info(uint32_t bytes);
		void ExibirInformacoes(void);
	private:
	//!Armazena um inteiro de 32 bits.
	/*!
		Em processadores low-Endian os bytes da memória ficam invertidos.
	*/
		uint32_t bytes;
};

//! Classe usada para armazenar números de ponto flutuante de 32 bits
class CONSTANT_Float_info: public cp_info
{
	public:
		CONSTANT_Float_info(uint32_t bytes);
		void ExibirInformacoes(void);
	private:
	//!Armazena um número em ponto flutuante de 32 bits.
	/*!
		Em processadores low-Endian os bytes da memória ficam invertidos. Estou utilizando um int para armazenar para garantir que são 32 bits. Para manipular deve-se fazer o cast do ponteiro
	*/
		uint32_t bytes;
};

//!Classe utilizada para representar um inteiro de 64 bits com sinnal
/*!
	Em processadores low-Endian os bytes da memória ficam invertidos. Estou utilizando um int para armazenar para garantir que são 32 bits. Para manipular deve-se fazer o cast do ponteiro
*/
class CONSTANT_Long_info:public cp_info
{
	public:
		CONSTANT_Long_info(uint32_t highBytes, uint32_t lowBytes);
		void ExibirInformacoes(void);

#ifdef IMPLEMENTADO_IMPRESSAO_NUMEROS_BASE_10

		//!Retorna em uma string o número na base 10
		/*!
			\todo:Implementar. Quando estiver implementado usá-lo no ExibirInformacoes(void)
		*/
		std::string ObterNumeroBase10();
#endif
	private:
//!Contém os 32 bytes de mais alta ordem do número inteiro de 64 bits
		uint32_t high_bytes;
//!Contém os 32 bytes de ordem mais baixa do inteiro de 64 bits
		uint32_t low_bytes;
};

//! Representa um número de ponto flutuante de 64 bits
/*!
	Em processadores low-Endian os bytes da memória ficam invertidos. Estou utilizando um int para armazenar para garantir que são 32 bits. Para manipular deve-se fazer o cast do ponteiro
*/
class CONSTANT_Double_info:public cp_info
{
	public:
		CONSTANT_Double_info(uint32_t highBytes, uint32_t lowBytes);
		void ExibirInformacoes(void);
#ifdef IMPLEMENTADO_IMPRESSAO_NUMEROS_BASE_10
		//!Retorna em uma string o número na base 10
		/*!
			\todo:Implementar. Quando estiver implementado usá-lo no ExibirInformacoes(void)
		*/
		std::string ObterNumeroBase10();
#endif
	private:
//!Contém os 32 bytes de mais alta ordem do número em ponto flutuante de 64 bits
		uint32_t high_bytes;
//!Contém os 32 bytes de ordem mais baixa do número em ponto flutuante de 64 bits
		uint32_t low_bytes;
};

/*!
	Classe utilizada para representar um campo ou método sem indicar a qual classe ou interface este pertence
*/
class CONSTANT_NameAndType_info: public cp_info
{
	public:
		CONSTANT_NameAndType_info(uint16_t nameIndex, uint16_t descriptorIndex);
		void ExibirInformacoes(void);
	private:
/*!
O valor de name_index tem que ser uma entrada válida na tabela constant_pool, que deve referenciar um CONSTANT_Utf8_info que representa tanto o nome do método especial <init> ou um nome não qualificado que denota um campo ou método.
*/
		uint16_t name_index;
/*
O valor de descriptor_index tem que ser uma entrada válida na tabela constant_pool que referencia um CONSTANT_Utf8_info que representa um descrito válido de campo ou método
The value of the descriptor_index item must be a valid index into the
constant_pool table. The constant_pool entry at that index must be a
CONSTANT_Utf8_info (§4.4.7) structure representing a valid field descriptor
(§4.3.2) or method descriptor 
*/
		uint16_t descriptor_index;
};

//! Classe utilizada para representar strings constantes.
/*!
	\todo: verificar a viabilidade de usar o Internation omponents for Unicode(ICU) para mostrar UTF-8
*/
class CONSTANT_Utf8_info: public cp_info
{
	public:
		CONSTANT_Utf8_info(uint16_t comprimento, uint8_t *arrayBytes);
		~CONSTANT_Utf8_info();
		void ExibirInformacoes(void);
		bool operator==(std::string teste);
		bool operator==(char const *teste);
	private:
/*!
O valo de lenght informa o número de bytes no vetor de bytes(e não o comprimento da string resultante). As strings contidas nessa estrutura NÃO terminam com '\0'(NULL)
*/
		uint16_t lenght;
/*!
O vetor de bytes contém os bytes da string. Nenhum byte pode ter o valor zero ou estar no intervalo 0xf0 ~-xff
*/
		uint8_t* bytes;
};

//! Classe utilizada para representar um manipulador de método(chuto que é assim que traduz)
class CONSTANT_MethodHandle_info: public cp_info
{
	public:
		CONSTANT_MethodHandle_info(uint8_t referenceKind, uint16_t referenceIndex);
		void ExibirInformacoes(void);
	private:
/*!
O valor de reference_knid tem q estar entre 1 e 9. O valor denota o tipo de manipulador de método, o qual caracteriza o comportamento do bytecode.
*/
		uint8_t reference_kind;
/*!
O valor de reference_index tem que ser um valor da tabela constant_pool.
Se o valor do reference_kind for 1(REF_getField), 2(REF_getStatic), 3(REF_putField ou 4(REF_putStatic), então a entrada na constant_pool referencia um CONSTANT_Fieldref_info representando qual manipulador de métodos deve ser criado.
Se o valor de reference_kind for 5(REF_invokeVirtual), 6(REF_invokeStatic), 7(REF_invokeSpecial) ou 8(REF_newInvokeSpecial) então a entrada na constant_pool é um CONSTANT_Methodref_info representando um método da classe  ou construtor para o qual o manipulador de método é para ser criado.
Se o valor do reference_kind é 9(REF_invokeInterface) então a entrada na constant_pool tem que ser CONSTANT_InterfaceMethodref_info que representa um método de interface para o qual o manipulador precisa ser criado.
Se o valor de reference_kind for 5, 6, 7 ou 9 o nome do método representado pela CONSTANT_Methodref_info NÃO pode ser <init> ou <clinit>
Se o valor for 8(REF_newInvokeSpecial) o nome do método representado pelo CONSTANT_Methodref_info deve ser <init>
*/
		uint16_t reference_index;
};

//!Classe que armazena um descritor de métodos
/*!
	Um descritor de método contém informa o tipo de retorno e os argumentos de algum método.
*/
class CONSTANT_MethodType_info:public cp_info
{
	public:
		CONSTANT_MethodType_info(uint16_t descriptorIndex);
		void ExibirInformacoes(void);
	private:
/*!
O Valor de descriptor_index tem que ser uma entrada válida na tabela constant_pool, que deve ser um CONSTANT_Utf8_info representando o descritor do método.
*/
		uint16_t descriptor_index;
};

//!Classe que representa a estrutura utiizada pela instrução invokedynamic.
/*!
Classe que representa a estrutura utiizada pela instrução invokedynamic, que é usada por um método "bootstrap", a invocação dinâmica do método, o nome dinâmico de invocação, o argumento e o tipo de retorno e opcionalmente uma sequência de constantes chamadas argumentos estáticos do método bootstrap.
*/
class CONSTANT_InvokeDynamic_info:public cp_info
{
	public:
		CONSTANT_InvokeDynamic_info(uint16_t bootstrapMethodAttrIndex, uint16_t nameAndTypeIndex);
		void ExibirInformacoes(void);
	private:
/*!
O valor de bootstrap_method_attr_index tem que ser uma entrada válida no vetor de métodos "bootstrap" da tabela de métodos "bootstrap" da classe do arquivo atual.
*/
		uint16_t bootstrap_method_attr_index;
/*!
O valro de name_and_type_index tem que ser uma entrada válida na tabela constant_pool, que deve ser um CONSTANT_NameAndType_info que representa o nome de um método e o seu descritor.
*/
		uint16_t name_and_type_index;
};

class NaoUsavel:public cp_info
{
	public:
		NaoUsavel(void);
		void ExibirInformacoes(void);
};

#endif

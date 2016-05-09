#include<stdint.h>


	//! Enumeração que indica os "tipos" de cpinfo
	/*! Enumeração que indica os valores que a tag do cpinfo pode assumir */
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
	CONSTANT_InvokeDynamic=18
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
	  \todo O método não está completamente codificado
	*/
		static cp_info& LerCpInfo(FILE *arq);
	private:
	//! Construtor privado, na verdade essa classe é abstrata
	/*!
	Essa classe é privada, só que não contém nenhum método virtual para qualifiquar ela-la como tal. Para evitar instanciação, tornei seu construtor privado
	*/
		cp_info();
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
	private:
//!inteiro sem sinal de 2 bytes
/*!
O valor de nameIndex tem que ser um valor válido no vetor de constant_pool.
E deve referenciar um CONSTANT_Utf8_info, que representa uma classe binária ou interface com nome codificado na forma interna.
*/
		uint16_t nameIndex;
};

class CONSTANT_Fieldred_info:public cp_info
{
	public:
		CONSTANT_Fieldred_info(uint16_t classIndex, uint16_t nameAndTypeIndex);
	private:
		uint16_t class_index;
		uint16_t name_and_type_index;
};

class CONSTANT_Methodref_info:public cp_info
{
	public:
		CONSTANT_Methodref_info(uint16_t classIndex, uint16_t nameAndTypeIndex);
	private:
		uint16_t class_index;
		uint16_t name_and_type_index;
};

class CONSTANT_InterfaceMethodref_info:public cp_info
{
	public:
		CONSTANT_InterfaceMethodref_info(uint16_t classIndex, uint16_t nameAndTypeIndex);
	private:
		uint16_t class_index;
		uint16_t name_and_type_index;
};

#include<stdint.h>
#include<vector>
#include<string>
#include"cp_info.hpp"
#include"field_info.hpp"
#include"method_info.hpp"
#include"attribute_info.hpp"

using namespace std;

#ifndef JAVA_CLASS_HPP
#define JAVA_CLASS_HPP


//!  Classe que representa um .class
/*!
  Classe responsável por armazenar dados de um arquivo .class
*/
class JavaClass
{
	public:
	//! Lê um arquivo .class e inicializa a classe.
	/*!
	  Método responsável por ler um arquivo .class e inicializar essa classe.
	  \param nomeArquivo Nome do arquivo .class que será lido
	*/
		JavaClass(string nomeArquivo);
		~JavaClass(void);
		void ExibirInformacoes(void);
	private:
		//!Assinatura do tipo de arquivo
		/*!
		Contém o número mágico que identifica o tipo do arquivo. Deve conter o valor 0xCAFEBABE.
		*/
		uint32_t magic;
		uint16_t minor_version;
		uint16_t major_version;
		//!Indica o número de cpinfo-1
		/*!
		O valor dessa variável é igual ao número de entradas no vetor constant_pool mais um(1).
		Um índice é válido se é maior que zero e menor que constant_pool_count. Com exceção de constantes do tipo long e double
		*/
		uint16_t constant_pool_count;
		vector<cp_info*> constant_pool;
		//! Armazena flags sobre a classe
		/*!
		O valor é uma máscara usada para informar permissões de acesso para e propriedade dessa classe ou interface.
		A interpretação da informação contida nessa classe pode ser vista na tabela abaixo:
		Nome da flag  | Bit sinalizador | interpretação
		:-------------|:---------------:|:-----------------------------------------------------------------------------------
		ACC_PUBLIC    | 0x0001          | Declarada pública. Pode ser acessada de fora deste pacote
		ACC_FINAL     | 0x0010          | Declarada final. Não pode ser herdada.
		ACC_SUPER     | 0x0020          | Trata os métodos da superclasse de forma diferente quando chamados pela instrução invokespecial.
		ACC_INTERFACE | 0x0200          | Isto é uma interface! Não é uma classe.
		ACC_ABSTRACT  | 0x0400          | Declarada abstrata. Não pode ser instanciada.
		ACC_SYNTHETIC | 0x1000          | Declarada sintética. Não existe no código fonte.
		ACC_ANNOTATION| 0x2000          | Declarada como um tipo anotação.
		ACC_ENUM      | 0x4000          | Declarada como uma enumeração.
		Todos os bits não informados acima são reservados para uso futuro. Eles devem ser tornados zeros na durante a geração do .class e; se não tiverem devem ser ignorados silenciosamente 
		*/
		uint16_t access_flags;
		//! Indica qual é a classe descrita este arquivo
		/*!
		O valor tem que ser uma entrada válida no vetor de constant_pool que deve ser uma constan class info.
		*/
		uint16_t this_class;
		//*! Referencia a classe pai
		/*!
		Numa classe, o valor da classe pai tem que ser zero ou um valor válido no constant_pool. Se o valor da super classe for diferente de zero, ele deve refenciar um CONSTANT_Class_info que representa o "pai" direto dessa classe. Nem o pai direto ou indireto deve ter a flag ACC_FINAL acionada.
		*/
		uint16_t super_class;
		//!Informa o número de interfaces relevantes para essa classe.
		uint16_t interfaces_count;
		//! Vetor de interfaces indexado a partir de zero
		vector<uint16_t> interfaces;
		uint16_t fields_count;
		vector<field_info> fields;
		uint16_t methods_count;
		vector<method_info> methods;
		uint16_t attributes_count;
		vector<attribute_info> attributes;
};

#endif


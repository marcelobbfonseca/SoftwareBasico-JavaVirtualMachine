#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<vector>
#include<string>

using namespace std;

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

class cp_info
{
	uint8_t tag;
	uint8_t *info;
};

class JavaClass
{
	public:
		uint32_t magic;
		uint16_t minor_version;
		uint16_t major_version;
		uint16_t constant_pool_count;
		vector<cp_info> constant_pool;
		uint16_t access_flags;
		uint16_t this_class;
		uint16_t super_class;
		uint16_t interfaces_count;
		uint16_t fieds_count;
		vector<field_info> fields;
		uint16_t methods_count;
		vector<method_info> methods;
		uint16_t attributes_count;
		vector<attribute_info> attributes;
		JavaClass(){};
		///\Validacao abertura de arquivo 
		/** Se nao conseguir abrir o arquivo da erro */
		void LerArquivo(string nomeArquivo){
			FILE *arq= fopen(nomeArquivo.c_str(), "rb");
			if(arq == NULL)
			{
				printf("ai meu cu");
				exit(1);
			}
			LerAtributo(&magic, 4, arq);
			LerAtributo(&minor_version, 2, arq);
			LerAtributo(&major_version, 2, arq);
			LerAtributo(&constant_pool_count, 2, arq);
			///que poha eh essa
			/**saber como funciona esse constant_pool com monitor */
			LerAtributo(&access_flags, 2, arq);
			LerAtributo(&this_class, 2, arq);
			LerAtributo(&super_class, 2, arq);
			for(int cont =0; cont < constant_pool_count; cont++)
			{
				LerAtributo(&(constant_pool[cont].tag), 1, arq);
				LerCpInfo(cont);
			}
			
		}
	private:
		///\Validacao leitura Arquivo 
		/** Se nao conseguir ler o arquivo da erro */
		void LerAtributo(void *alvo, int size, FILE *arq)
		{
			if(!fread(alvo, size, 1, arq))
			{
				printf("Erro na leitura do arquivo");
				exit(EXIT_FAILURE);
			}
		}
		void LerCpInfo(int indiceVetor){
			switch(constant_pool[indiceVetor].tag)
			{
				case 
			}
		}
};

/*void SetMagic(char *nomeArq){

	FILE *fp
    fp = fopen(nomeArq,fp);
	uint32_t magic; 
    fread(magic, sizeof(uint32_t),1,fp);
	this.magic = magic; //manda pro construtor
}

JavaClass(uint32_t u4){
	le issa parada

*/

#include"JavaClass.hpp"
#include "Erro.hpp"
#include "Leitura.hpp"
#include"Endian.hpp"
#include<iostream>
//o define EH_NUMERO informa que os bytes lidos devem ser invertidos, pois devem são numeros que devem ser armazenados em little endian

using namespace std;

JavaClass::JavaClass(string nomeArquivo)
{

	FILE *arq= fopen(nomeArquivo.c_str(), "rb");
	if(arq == NULL)
	{
		throw(new Erro("Falha na abertura do arquivo!"));
	}
	Leitura::LerAtributo(&magic, 4, arq);
	Leitura::LerAtributo(&minor_version, 2, arq, EH_NUMERO);
	Leitura::LerAtributo(&major_version, 2, arq, EH_NUMERO);
	Leitura::LerAtributo(&constant_pool_count, 2, arq, EH_NUMERO);
	for(int cont=0; cont < constant_pool_count-1; cont++)
	{
		try
		{
			cp_info *cpInfo = cp_info::LerCpInfo(arq);
			constant_pool.push_back(*cpInfo);
		}
		catch(CONSTANT_Long_info *longInfo)
		{
			constant_pool.push_back(*longInfo);
			NaoUsavel *naoUsavel= new NaoUsavel();
			constant_pool.push_back(*naoUsavel);
			cont++;
		}
		catch(CONSTANT_Double_info *doubleInfo)
		{
			constant_pool.push_back(*doubleInfo);
			NaoUsavel *naoUsavel= new NaoUsavel();
			constant_pool.push_back(*naoUsavel);
			cont++;
		}
	}
	Leitura::LerAtributo(&access_flags, 2, arq);
	Leitura::LerAtributo(&this_class, 2, arq, EH_NUMERO);
	Leitura::LerAtributo(&super_class, 2, arq, EH_NUMERO);
	Leitura::LerAtributo(&interfaces_count, 2, arq, EH_NUMERO);
	
	uint16_t aux_interface;
	for(int cont=0; cont < interfaces_count; cont++)
	{
		Leitura::LerAtributo(&aux_interface, 2, arq, EH_NUMERO);
		interfaces.push_back(aux_interface);
	}
	
	Leitura::LerAtributo(&fields_count, 2, arq, EH_NUMERO);
	for(int cont=0; cont < fields_count; cont++)
	{
		field_info *fieldInfo = new field_info(arq);
		fields.push_back(*fieldInfo);
	}
	
	Leitura::LerAtributo(&methods_count, 2, arq, EH_NUMERO);
	for(int cont=0; cont < methods_count; cont++)
	{
		method_info *methodInfo = new method_info(arq);
		methods.push_back(*methodInfo);
	}
	
	Leitura::LerAtributo(&attributes_count, 2, arq, EH_NUMERO);
	for(int cont=0; cont < attributes_count; cont++)
	{
		attribute_info *attributesInfo = new attribute_info(arq);
		attributes.push_back(*attributesInfo);
	}
	fclose(arq);
}

void JavaClass::ExibirInformacoes(void)
{
//	uint8_t *aux;
//	aux= (uint8_t *) &magic;
    cout <<"Magic:\t\t\t0x"<< hex << InverterEndianess<uint32_t>(magic) <<  endl << dec;
//	cout.unsetf(ios::hex);
	cout << "Minor version:\t\t\t" << minor_version << endl;
	cout << "Major version:\t\t\t" << major_version << endl;
	cout << "Versão do .class: " << major_version << "." << minor_version << endl;
	cout << "constant_pool_count:\t" << constant_pool_count <<endl;
	cout << "Constant pool:" << endl;
	for(unsigned int cont= 0; cont < constant_pool.size() ; cont++)
	{
		cout << " \t#" << cont+1 << " = ";
		constant_pool[cont].ExibirInformacoes();
        cout<< endl;
	}

}

#include "JavaClass.hpp"
#include "Erro.hpp"
#include "Leitura.hpp"
#include "Endian.hpp"
#include <iostream>

//o define EH_NUMERO informa que os bytes lidos devem ser invertidos, pois devem são numeros que devem ser armazenados em little endian

using namespace std;

JavaClass::JavaClass(string nomeArquivo)
{

	FILE *arq= fopen(nomeArquivo.c_str(), "rb");
	if(arq == NULL)
	{
		throw(new Erro("Falha na abertura do arquivo!"));
	} 					//enderecos de atributos do java class
	Leitura::LerAtributo(&magic, 4, arq, IGNORAR_ENDIAN);
	Leitura::LerAtributo(&minor_version, 2, arq);
	Leitura::LerAtributo(&major_version, 2, arq);
	Leitura::LerAtributo(&constant_pool_count, 2, arq);

	for(int cont=0; cont < constant_pool_count-1; cont++)
	{
		try
		{
			cp_info *cpInfo = cp_info::LerCpInfo(arq);
string tabs = "\t";
cpInfo->ExibirInformacoes();
			constant_pool.push_back(cpInfo);
		}
		catch(CONSTANT_Long_info *longInfo)
		{
			constant_pool.push_back(longInfo);
			NaoUsavel *naoUsavel= new NaoUsavel();
			constant_pool.push_back(naoUsavel);
			cont++;
		}
		catch(CONSTANT_Double_info *doubleInfo)
		{
			constant_pool.push_back(doubleInfo);
			NaoUsavel *naoUsavel= new NaoUsavel();
			constant_pool.push_back(naoUsavel);
			cont++;
		}
	}

	Leitura::LerAtributo(&access_flags, 2, arq);
	Leitura::LerAtributo(&this_class, 2, arq);
	Leitura::LerAtributo(&super_class, 2, arq);
	Leitura::LerAtributo(&interfaces_count, 2, arq);
	
	uint16_t aux_interface;
	for(int cont=0; cont < interfaces_count; cont++)
	{
		Leitura::LerAtributo(&aux_interface, 2, arq);
		interfaces.push_back(aux_interface);
	}
	
	Leitura::LerAtributo(&fields_count, 2, arq);
//cout<< "Começando a ler os " << fields_count <<" fields." << endl;
	for(int cont=0; cont < fields_count; cont++)
	{
		field_info *fieldInfo = new field_info(arq, constant_pool);
		fields.push_back(*fieldInfo);
//cout<< "Lido field" << endl;
	}
	
	Leitura::LerAtributo(&methods_count, 2, arq);
cout<< "Começando a ler os " << methods_count <<" methods." << endl;
	for(int cont=0; cont < methods_count; cont++)
	{
		method_info *methodInfo = new method_info(arq, constant_pool);
string tabs = "\t";
methodInfo->ExibirInformacoes(tabs);
		methods.push_back(*methodInfo);
cout<< "Lido method" << endl;
	}
	
	Leitura::LerAtributo(&attributes_count, 2, arq);
cout << "Attributes count = " << attributes_count << endl;
	for(int cont=0; cont < attributes_count; cont++)
	{
		attribute_info *attributesInfo = attribute_info::LerAtributeInfo(arq, constant_pool);
		attributes.push_back(attributesInfo);
	}
	fclose(arq);
}

JavaClass::~JavaClass(void)
{
	for(unsigned int cont  = 0 ; cont < constant_pool.size(); cont++)
	{
		delete constant_pool[cont];
	}
}

//pega as informacoes do javaclass arquivo 
void JavaClass::ExibirInformacoes(void)
{
	string tabs = "\t";

	cout << "-----------------------------------------------------------------" << endl;
	cout << "Bem vindo ao trabalho de SB do grupo MAFRJODEMA. Boa sorte tentando pronunciar isso =D" << endl;
	cout << "-----------------------------------------------------------------" << endl;
	cout <<"Magic:\t\t\t0x"<< hex << InverterEndianess<uint32_t>(magic) <<  endl << dec;
	cout << "-----------------------------------------------------------------" << endl;
	cout << "Minor version:\t\t\t" << minor_version << endl;
	cout << "Major version:\t\t\t" << major_version << endl;
	cout << "Versão do .class: \t\t" << major_version << "." << minor_version << endl;
	cout << "-----------------------------------------------------------------" << endl;
	cout << "constant_pool_count:\t\t" << constant_pool_count <<endl;
	cout << "Constant pool:\t" << endl;
	cout << "-- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;

	for(unsigned int cont= 0; cont < constant_pool.size() ; cont++)
	{
		cout  << tabs << "#" << cont+1 << " = ";
		(*(constant_pool[cont])).ExibirInformacoes();
		if(cont != constant_pool.size()-1)
		{
			cout << "-- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
		}
	}
	cout << "-----------------------------------------------------------------" << endl;
//passar essa parte pro access_flag.cpp!
	cout<< "access_flags:\t\t\t" << hex << access_flags << dec << endl;
	if(access_flags & 0x0001)
	{
		cout << "\t\tACC_PUBLIC" << endl;
	}
	if(access_flags & 0x0010)
	{
		cout << "\t\tACC_FINAL" << endl;
	}
	if(access_flags & 0x0020)
	{
		cout << "\t\tACC_SUPER" << endl;
	}
	if(access_flags & 0x0200)
	{
		cout << "\t\tACC_INTERFACE" << endl;
	}
	if(access_flags & 0x0400)
	{
		cout << "\t\tACC_ABSTRACT" << endl;
	}
	if(access_flags & 0x1000)
	{
		cout << "\t\tACC_SYNTHETIC" << endl;
	}
	if(access_flags & 0x2000)
	{
		cout << "\t\tACC_ANNOTATION" << endl;
	}
	if(access_flags & 0x4000)
	{
		cout << "\t\tACC_ENUM" << endl;
	}
	cout << "-----------------------------------------------------------------" << endl;
	cout << "This class =\t\t" << this_class << endl;
	cout << "Super class =\t\t" << super_class << endl;
	cout << "-----------------------------------------------------------------" << endl;
	cout << "Interfaces count =\t" << interfaces_count << endl;
	if(interfaces_count > 0)
	{
		cout << "Interfaces:" << endl;
		for(unsigned int cont= 0; cont < interfaces.size() ; cont++)
		{
			cout << "\t\t#" << cont << "\t" << interfaces[cont] << endl;
		}
	}
	cout << "-----------------------------------------------------------------" << endl;
	cout << "Fields count =\t\t" << fields_count << endl;
	if(fields_count > 0)
	{
		cout << "Fields:" << endl;
		cout << "-- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
		for(unsigned int cont= 0; cont < fields.size() ; cont++)
		{
			cout << "\tField[" << cont << "]:" << endl;;
			fields[cont].ExibirInformacoes( ( (tabs + "\t") +"\t" ) );
			if(cont != fields.size()-1)
			{
				cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
			}
		}
	}
	cout << "-----------------------------------------------------------------" << endl;
	cout << "Methods count =\t\t" << methods_count << endl;
	if(methods_count > 0)
	{
		cout << "Methods:" << endl;
		cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
		for(int cont= 0; cont < methods_count ; cont++)
		{
			cout << "\tMethod[" << cont << "]:" << endl;;
			methods[cont].ExibirInformacoes( ( (tabs + "\t") +"\t" ) );
			if(cont != methods_count-1)
			{
				cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
			}
		}
	}
	cout << "-----------------------------------------------------------------" << endl;
	cout << "Attributes count =\t\t" << attributes_count << endl;
	if(attributes_count > 0)
	{
		cout << "Attributes:" << endl;
		cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
		for(unsigned int cont= 0; cont < attributes.size() ; cont++)
		{
			cout << "\t\t\tAttribute[" << cont << "]:" << endl;;
			attributes[cont]->ExibirInformacoes( ( (tabs + "\t") +"\t" ) );
			if(cont != attributes.size()-1)
			{
				cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
			}
		}
	}
	cout << "-----------------------------------------------------------------" << endl;
	cout << "Isso é tudo q tem no arquivo xD" << endl;
	cout << "-----------------------------------------------------------------" << endl;
}

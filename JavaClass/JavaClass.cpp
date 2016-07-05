#include "JavaClass.hpp"
#include "Erro.hpp"
#include "Leitura.hpp"
#include "Endian.hpp"
#include "UtilidadesParaString.hpp"
#include <iostream>
#include <stdio.h>
#include <string.h>

// Check ruindos
#if _WIN32 || _WIN64
	#if _WIN64
		#define ENVIRONMENT64
	#else
		#define ENVIRONMENT32
	#endif
#endif

// Check GCC
#if __GNUC__
	#if __x86_64__ || __ppc64__
		#define ENVIRONMENT64
	#else
		#define ENVIRONMENT32
	#endif
#endif

//o define EH_NUMERO informa que os bytes lidos devem ser invertidos, pois devem são numeros que devem ser armazenados em little endian

//#define DEBUG

using namespace std;

JavaClass::JavaClass(string nomeArquivo)
{

	FILE *arq= fopen(nomeArquivo.c_str(), "rb");
	if(arq == NULL)
	{
		throw(new Erro("Falha na abertura do arquivo!"));
	} 					//enderecos de atributos do java class
	Leitura::LerAtributo(&magic, 4, arq);
	if(magic != 0xcafebabe)
	{
		throw new Erro("Magic invalido", "JavaClass", "JavaClass");
	}
	Leitura::LerAtributo(&minor_version, 2, arq);
	Leitura::LerAtributo(&major_version, 2, arq);
	if(major_version <46)
	{
		char errMsg[100];
		sprintf(errMsg, "Versao .class invalido.\tVersao informada: %d.%d", major_version, minor_version);
		throw new Erro(errMsg, "JavaClass", "JavaClass");
	}
	Leitura::LerAtributo(&constant_pool_count, 2, arq);

	for(int cont=0; cont < constant_pool_count-1; cont++)
	{
		try
		{
			cp_info *cpInfo = cp_info::LerCpInfo(arq);
#ifdef DEBUG
string tabs = "\t";
//cpInfo->ExibirInformacoes(this);
#endif
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
#ifdef DEBUG
cout<< "Começando a ler os " << fields_count <<" fields." << endl;
#endif
	for(int cont=0; cont < fields_count; cont++)
	{
		field_info *fieldInfo = new field_info(arq, constant_pool);
		fields.push_back(*fieldInfo);
#ifdef DEBUG
cout<< "Lido field" << endl;
#endif
	}

	Leitura::LerAtributo(&methods_count, 2, arq);
#ifdef DEBUG
cout<< "Começando a ler os " << methods_count <<" methods." << endl;
#endif
	for(int cont=0; cont < methods_count; cont++)
	{
		method_info *methodInfo = new method_info(arq, constant_pool);
#ifdef DEBUG
string tabs = "\t";
//methodInfo->ExibirInformacoes(tabs, this);
#endif
		methods.push_back(*methodInfo);
#ifdef DEBUG
cout<< "Lido method" << endl;
#endif
	}

	Leitura::LerAtributo(&attributes_count, 2, arq);
#ifdef DEBUG
cout << "Attributes count = " << attributes_count << endl;
#endif
	for(int cont=0; cont < attributes_count; cont++)
	{
		attribute_info *attributesInfo = attribute_info::LerAtributeInfo(arq, constant_pool);
		attributes.push_back(attributesInfo);
	}
	fclose(arq);
	//verificação se o nome do arquivo é igual ao nome da classe
	string nomeArquivoSemCaminhoNemExtensao= StringUtilidades::RemoverCaminhoEExtensao(nomeArquivo, ".class");
	if(this->NomeDaClasse()!= nomeArquivoSemCaminhoNemExtensao)
	{
		char erro[200];
		sprintf(erro, "Nome da classe diferente do nome do arquivo!\tArquivo: %s\tclasse:%s", NomeDaClasse().c_str(), nomeArquivoSemCaminhoNemExtensao.c_str());
		throw new Erro(erro, "JavaClass", "JavaClass");
	}
	//inicialização dos fields estáticos para tempo de execução
	for(unsigned int cont =0; cont < fields.size(); cont++)
	{
		field_info field= fields[cont];
		if(field.FlagAtivada(FIELD_STATIC) && !field.FlagAtivada(FIELD_FINAL))//estática e não final
		{
			string nomeField= getUTF8(field.getNameIndex());
			string descritorDoField= getUTF8(field.getDescriptorIndex());
			char tipoField = descritorDoField[0];
			Valor valor;
			switch(tipoField)
			{
				case('B'):
				{
					valor.tipo= TipoDado::BYTE;
					valor.dado = 0;
					break;
				}
				case('C'):
				{
					valor.tipo= TipoDado::CHAR;
					valor.dado= 0;
					break;
				}
				case('D'):
				{
					valor.tipo= TipoDado::DOUBLE;
					double aux=0;
					memcpy(&(valor.dado), &aux, 8);
					break;//tratar daqui a pouco nesse mesmo método
				}
				case('F'):
				{
					valor.tipo= TipoDado::FLOAT;
					float aux =0;
					memcpy(&(valor.dado), &aux, 4);
					break;
				}
				case('I'):
				{
					valor.tipo= TipoDado::INT;
					valor.dado= 0;
					break;
				}
				case('J'):
				{
					valor.tipo= TipoDado::LONG;
					valor.dado= 0;
					break;//tratar daqui a pouco nesse mesmo método
				}
				case('S'):
				{
					valor.tipo= TipoDado::SHORT;
					valor.dado= 0;
					break;
				}
				case('Z'):
				{
					valor.tipo= TipoDado::BOOLEAN;
					valor.dado= 0;
					break;
				}
				default:
				{
					valor.tipo= TipoDado::REFERENCE;
					void *aux= NULL;
					memcpy(&(valor.dado), &aux, sizeof(void*));
				}
			}
			camposEstaticos[nomeField]= valor;
		}
	}
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
	cout <<"Magic:\t\t\t0x"<< hex << magic <<  endl << dec;
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
		(*(constant_pool[cont])).ExibirInformacoes(this);
		if(cont != constant_pool.size()-1)
		{
			cout << "-- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
		}
	}
	cout << "-----------------------------------------------------------------" << endl;
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
			cout << "\t\t#" << cont << "\t" << interfaces[cont] << getUTF8(interfaces[cont]) << endl;
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
			fields[cont].ExibirInformacoes( ( (tabs + "\t") +"\t" ), this );
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
			methods[cont].ExibirInformacoes( ( (tabs + "\t") +"\t" ), this );
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
			attributes[cont]->ExibirInformacoes( ( (tabs + "\t") +"\t" ), this );
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

string JavaClass::NomeDaClasse(void)
{
	string retorno= "";
	for(unsigned int cont =0 ; cont < attributes.size(); cont++)
	{
		if( ( *( (CONSTANT_Utf8_info *)constant_pool[attributes[cont]->getAttributeNameIndex()-1] ) )== "SourceFile" )
		{
			uint16_t indiceNomeArquivo= ((SourceFile_attribute *)attributes[cont])->GetSouceFileIndex();
			retorno = ( (CONSTANT_Utf8_info *)(constant_pool[indiceNomeArquivo-1]) )->GetString();
			retorno = StringUtilidades::RemoverNoFinal(retorno, ".java");
			return retorno;
		}
	}
	return retorno;
//	throw new Erro("Classe nao possui nome armazenado internamente.", "JavaClass", "NomeDaClasse");
}

const std::vector<field_info>& JavaClass::getFieldInfo(void)
{
	return fields;
}

uint16_t JavaClass::getFieldsCount(void)
{
	return fields_count;
}

bool JavaClass::FlagAtivada(JavaClassFlag flag)
{
	return (access_flags&flag) != 0;
}

const string JavaClass::getUTF8(uint16_t posicao)
{
	cp_info* constante = constant_pool[posicao-1];
#ifdef DEBUG
cout<< "JavaClass::getUTF8\tposicao-1= " << posicao-1 << "\ttag= " << (uint32_t)constante->GetTag() << endl;
#endif
	switch(constante->GetTag())
	{
		case(CONSTANT_Class):
		{
			CONSTANT_Class_info *classInfo = (CONSTANT_Class_info*)constante;
			return getUTF8(classInfo->GetNameIndex());
		}
		case(CONSTANT_Fieldref):
		{
			CONSTANT_Fieldref_info *fieldRefInfo= (CONSTANT_Fieldref_info*) constante;
			CONSTANT_NameAndType_info *nameAndTypeInfo = (CONSTANT_NameAndType_info *)constant_pool[fieldRefInfo->GetNameAndTypeIndex()-1];
			const string nomeClasse = getUTF8(fieldRefInfo->GetClassIndex());
			const string nomeField= getUTF8(nameAndTypeInfo->GetNameIndex());
			return nomeClasse + "." + nomeField;
		}
		case(CONSTANT_Methodref):
		{
			CONSTANT_Methodref_info *methodRefInfo= (CONSTANT_Methodref_info*) constante;
			CONSTANT_NameAndType_info *nameAndTypeInfo = (CONSTANT_NameAndType_info *)constant_pool[methodRefInfo->GetNameAndTypeIndex()-1];
			const string nomeClasse = getUTF8(methodRefInfo->GetClassIndex());
			const string nomeMethod= getUTF8(nameAndTypeInfo->GetNameIndex());
			return nomeClasse + "." + nomeMethod;
		}
		case(CONSTANT_InterfaceMethodref):
		{
			CONSTANT_InterfaceMethodref_info *interfaceMethodRefInfo= (CONSTANT_InterfaceMethodref_info*) constante;
			CONSTANT_NameAndType_info *nameAndTypeInfo = (CONSTANT_NameAndType_info *)constant_pool[interfaceMethodRefInfo->GetNameAndTypeIndex()-1];
			const string nomeClasse = getUTF8(interfaceMethodRefInfo->GetClassIndex());
			const string nomeInterfaceMethod= getUTF8(nameAndTypeInfo->GetNameIndex());
			return nomeClasse + "." + nomeInterfaceMethod;
		}
		case(CONSTANT_String):
		{
			CONSTANT_String_info *stringInfo = (CONSTANT_String_info*)constante;
			return getUTF8(stringInfo->GetStringIndex());
		}
		case(CONSTANT_Integer):
		{
			CONSTANT_Integer_info *intInfo = (CONSTANT_Integer_info *)constante;
			int32_t numero = intInfo->GetNumero();
			char stringNum[30];
			sprintf(stringNum, "%d", numero);
			string retorno= stringNum;
			return retorno;
		}
		case(CONSTANT_Float):
		{
			CONSTANT_Float_info *floatInfo = (CONSTANT_Float_info *)constante;
			float numero= floatInfo->GetNumero();
			char stringNum[30];
			sprintf(stringNum, "%f", numero);
			string retorno= stringNum;
			return retorno;
		}
		case(CONSTANT_Long):
		{
			CONSTANT_Long_info *longInfo = (CONSTANT_Long_info *)constante;
			int64_t numero = longInfo->GetNumero();
			char stringNum[30];
#ifdef ENVIRONMENT32
			sprintf(stringNum, "%lld", numero);
#else
			sprintf(stringNum, "%ld", numero);
#endif
			string retorno= stringNum;
			return retorno;
		}
		case(CONSTANT_Double):
		{
			CONSTANT_Double_info *doubleInfo = (CONSTANT_Double_info *)constante;
			double numero= doubleInfo->GetNumero();
			char stringNum[30];
			sprintf(stringNum, "%f", numero);
			string retorno= stringNum;
			return retorno;
		}
		case(CONSTANT_NameAndType):
		{
			CONSTANT_NameAndType_info *nameAndTypeInfo = (CONSTANT_NameAndType_info *)constante;
			string nome= getUTF8(nameAndTypeInfo->GetNameIndex());
			string descritor= getUTF8(nameAndTypeInfo->GetDescriptorIndex());
			return nome+descritor;
		}
		case(CONSTANT_Utf8):
		{
			CONSTANT_Utf8_info *utf8Info = (CONSTANT_Utf8_info*)constante;
			return utf8Info->GetString();
		}
	}
	char erro[200];
	sprintf(erro, "Arquivo .class possui uma tag %hhu invalida no pool de constantes.", constante->GetTag());
	throw new Erro(erro, "JavaClass", "getUTF8");
//	return "";
}

const vector<cp_info*>& JavaClass::getConstantPool(void)
{
	return constant_pool;
}

method_info const * const JavaClass::getMetodo(string nomeMetodo, string descritorMetodo)
{
	for(unsigned int cont =0; cont < methods.size(); cont++)
	{
		method_info &temp = methods[cont];
		if(getUTF8(temp.getNameIndex()) == nomeMetodo && getUTF8(temp.getDescriptorIndex()) == descritorMetodo)
		{
			return &(methods[cont]);
		}
	}
	return NULL;
}

bool JavaClass::FieldExiste(string nomeDoField)
{
	return camposEstaticos.count(nomeDoField) > 0;
}

void JavaClass::ColocarValorNoField(string nomeDoField, Valor valor)
{
	camposEstaticos[nomeDoField]= valor;
}

Valor JavaClass::getValorDoField(string nomeDoField)
{
	if(!FieldExiste(nomeDoField))
	{
		throw new Erro("Solicitado field que não existe", "JavaClass", "getValorDoField");
	}
	return camposEstaticos[nomeDoField];
}



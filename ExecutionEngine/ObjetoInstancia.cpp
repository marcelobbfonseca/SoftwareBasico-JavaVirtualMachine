#include "ObjetoInstancia.hpp"
#include <vector>
#include <string.h>

TipoObjeto ObjetoInstancia::ObterTipoObjeto(void)
{
	return INSTANCIA;
}

ObjetoInstancia::ObjetoInstancia(JavaClass *classe)
{
	this->javaClass= classe;
	const vector<field_info> fields= javaClass->getFieldInfo();
	if(javaClass->FlagAtivada(JAVA_CLASS_ABSTRACT))
	{
		throw new Erro("Tentaram instanciar uma classe abstrata!", "ObjetoInstancia", "ObjetoInstancia");
	}
	for(unsigned int cont =0; cont < fields.size(); cont++)
	{
		field_info field= fields[cont];
		if(!field.FlagAtivada(FIELD_STATIC|FIELD_FINAL))//não estática e não final
		{
			string nomeField= javaClass->getUTF8(field.getNameIndex());
			string descritorDoField= javaClass->getUTF8(field.getDescriptorIndex());
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
					valor.tipo= TipoDado::INTEIRO;
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
					valor.tipo= TipoDado::BOOLEANO;
					valor.dado= 0;
					break;
				}
				default:
				{
					valor.tipo= TipoDado::REFERENCIA;
					void *aux= NULL;
					memcpy(&(valor.dado), &aux, sizeof(void*));
				}
			}
			atributosDeInstancia[nomeField]= valor;
		}
	}
}

ObjetoInstancia::~ObjetoInstancia()
{
	
}

JavaClass *ObjetoInstancia::ObterJavaClass(void)
{
	return javaClass;
}

bool ObjetoInstancia::CampoExiste(string nomeDoCampo)
{
	return atributosDeInstancia.count(nomeDoCampo) > 0;
}

void ObjetoInstancia::ColocarValorNoCampo(string nomeDoCampo, Valor valor)
{
	atributosDeInstancia[nomeDoCampo]= valor;
}

Valor ObjetoInstancia::ObterValorDoCampo(string nomeDoCampo)
{
	if(!CampoExiste(nomeDoCampo))
	{
		throw new Erro("Solicitado field que não existe", "JavaClass", "getValorDoField");
	}
	return atributosDeInstancia[nomeDoCampo];
}



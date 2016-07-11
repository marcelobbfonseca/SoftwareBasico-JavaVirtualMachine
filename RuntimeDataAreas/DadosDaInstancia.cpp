#include"DadosDaInstancia.hpp"
#include"Erro.hpp"
#include<string.h>

DadosDaInstancia::DadosDaInstancia(JavaClass *javaClass)
{
	vector<field_info> fields = javaClass->getFieldInfo();

	if (javaClass->FlagAtivada(JAVA_CLASS_ABSTRACT))
	{
		throw new Erro("Tentou-se instanciar uma classe abstrata", "DadosDaInstancia", "DadosDaInstancia");
	}

	for (int i = 0; i < javaClass->getFieldsCount(); i++)
	{
		field_info field = fields[i];
		if (!field.FlagAtivada(FIELD_STATIC|FIELD_FINAL))// não estática e não final
		{
			string nomeField = javaClass->getUTF8(field.getNameIndex());
			string descritorField = javaClass->getUTF8(field.getDescriptorIndex());

			char tipoField = descritorField[0];
			Valor valor;

			switch (tipoField)
			{
				case 'B':
				{
					valor.tipo = TipoDado::BYTE;
					valor.dado = 0;
					break;
				}
				case 'C':
				{
					valor.tipo = TipoDado::CHAR;
					valor.dado = 0;
					break;
				}
				case 'D':
				{
					valor.tipo = TipoDado::DOUBLE;
					double aux=0;
					memcpy(&(valor.dado), &aux, 8);
					break;
				}
				case 'F':
				{
					valor.tipo = TipoDado::FLOAT;
					float aux =0;
					memcpy(&(valor.dado), &aux, 4);
					break;
				}
				case 'I':
				{
					valor.tipo = TipoDado::INTEIRO;
					valor.dado = 0;
					break;
				}
				case 'J':
				{
					valor.tipo = TipoDado::LONG;
					valor.dado = 0;
					break;
				}
				case 'S':
				{
					valor.tipo = TipoDado::SHORT;
					valor.dado = 0;
					break;
				}
				case 'Z':
				{
					valor.tipo = TipoDado::BOOLEANO;
					void *aux= NULL;
					memcpy(&(valor.dado), &aux, sizeof(void*));
					break;
				}
				default:
				{
					valor.tipo = TipoDado::REFERENCIA;
				}
			}

			fieldsInstancia[nomeField] = valor;
		}
	}
}

Valor DadosDaInstancia::getValorDoField(string nomeField){
	if (fieldsInstancia.count(nomeField) ==  0) {

		throw new Erro("Field não existente", "DadosDaInstancia", "getValorDoField");

	}

	return fieldsInstancia[nomeField];
}

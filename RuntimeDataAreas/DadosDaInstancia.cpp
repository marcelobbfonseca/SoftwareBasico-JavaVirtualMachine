#include"DadosDaInstancia.hpp"
#include<string.h>

DadosDaInstancia::DadosDaInstancia(JavaClass *javaClass)
{
	vector<field_info> fields = javaClass->getFieldInfo();
	uint16_t abstractFlag = 0x0400;

	if ((javaClass->getAccessFlags() & abstractFlag) != 0)
	{
		// Não pode instanciar se for classe abstrata
		cerr << "Erro de instanciamento" << endl;
		exit(1);
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
					valor.tipo = TipoDado::INT;
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
					valor.tipo = TipoDado::BOOLEAN;
					void *aux= NULL;
					memcpy(&(valor.dado), &aux, sizeof(void*));
					break;
				}
				default:
				{
					valor.tipo = TipoDado::REFERENCE;
				}
			}

			fieldsInstancia[nomeField] = valor;
		}
	}
}



Valor DadosDaInstancia::getValorDoField(string nomeField){
	if (fieldsInstancia.count(nomeField) ==  0) {
		cerr << "Field não existente" << endl;
		exit(1);
	}

	return fieldsInstancia[nomeField];
}

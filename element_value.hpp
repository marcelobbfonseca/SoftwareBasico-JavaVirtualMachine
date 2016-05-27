#include<stdio.h>

enum Elemento_value_tag
{
	BYTE = 'B',
	CHAR = 'C',
	DOUBLE = 'D',
	FLOAT = 'F',
	INT = 'I';
	LONG = 'J',
	SHORT = 'S',
	BOOLEAN = 'Z',
	STRING = 's',
	ENUM_CONSTANT = 'e',
	CLASS = 'c',
	ANNOTATION_TYPE = '@',
	ARRAY = '['
}

namespace Atributos
	class element_value
	{
		protected:
			uint8_t tag;
*/		public:
			static element_value* LerElementValue(FILE *arq);
			virtual void ExibirInformacoes(void)=0;
	}
	class ValorConstante
	{
		
	}
}

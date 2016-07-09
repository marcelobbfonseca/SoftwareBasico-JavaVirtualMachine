#include "ObjetoArray.hpp"

TipoObjeto ObjetoArray::ObterTipoObjeto(void)
{
	return ARRAY;
}

ObjetoArray::~ObjetoArray()
{
	
}

ObjetoArray::ObjetoArray(TipoDado tipo){

	this->tipo = tipo;

}

void ObjetoArray::InserirValor(Valor queSeraInserido)
{
	if(queSeraInserido.tipo == tipo)
	{
		elementos.push_back(queSeraInserido);
	}
	else
	{
		throw new Erro("Tentaram Incluir um valor de tipo errado num array", "ObjetoArray", "InserirValor");
	}
}

Valor ObjetoArray::RemoverValorDaPosicao(uint32_t posicao)
{
	if(elementos.size()>0 && posicao< elementos.size())
	{
		Valor retorno= elementos[posicao];
		elementos.erase(elementos.begin() + posicao);
		return retorno;
	}
	else
	{
		throw new Erro ("Tentaram remover uma posicao invalida do vetor", "ObjetoArray", "RemoverValorDaPosicao");
	}
}

Valor ObjetoArray::RemoverNoFinal(void)
{
	if(elementos.size()>0)
	{
		Valor retorno= elementos.back();
		elementos.pop_back();
		return retorno;
	}
	throw new Erro ("Tentaram remover uma posicao invalida do vetor", "ObjetoArray", "RemoverNoFinal");
}

Valor ObjetoArray::RemoverNoInicio(void)
{
	if(elementos.size()>0)
	{
		Valor retorno= elementos.front();
		elementos.erase(elementos.begin());
		return retorno;
	}
	throw new Erro ("Tentaram remover uma posicao invalida do vetor", "ObjetoArray", "RemoverNoInicio");
}

uint32_t ObjetoArray::ObterTamanho(void) const
{
	return elementos.size();
}

Valor ObjetoArray::ObterValor(uint32_t posicao) const
{
	if(elementos.size()>0 && posicao< elementos.size())
	{
		return elementos[posicao];
	}
	throw new Erro ("Tentaram acessar uma posicao invalida do vetor", "ObjetoArray", "ObterValor");
}

void ObjetoArray::AlterarElementoDaPosicao(uint32_t posicao, Valor valor)
{
	if(elementos.size()>0 && posicao< elementos.size())
	{
		elementos[posicao]= valor;
	}
	else
	{
		throw new Erro ("Tentaram acessar uma posicao invalida do vetor", "ObjetoArray", "AlterarElementoDaPosicao");
	}
}


void ObjetoArray::popularSubArray(TipoDado tipoDado, stack<int> count){

	int currCount = count.top();
	count.pop();

	TipoDado tipoArr = (count.size() > 1) ? TipoDado::REFERENCE : tipoDado;

	if (count.size() == 0) {
		for (int i = 0; i < currCount; i++) {

			Valor ValorSubArr;
			ValorSubArr.tipo = tipoDado;
			ValorSubArr.dado = 0;
			empilhaValor(ValorSubArr);

		}

	}
	else {
		for (int i = 0; i < currCount; i++) {
			ObjetoArray *subarray = new ObjetoArray(tipoArr);
			subarray->popularSubArray(tipoDado, count);

			Valor ValorSubArr;
			ValorSubArr.tipo = TipoDado::REFERENCE;
			ValorSubArr.dado = (uint64_t)subarray;
			this->empilhaValor(ValorSubArr);
		}
	}
}

void ObjetoArray::empilhaValor(Valor valor) {

	assert(valor.tipo == tipo);

	elementos.push_back(valor);

}



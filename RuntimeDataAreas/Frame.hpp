#ifndef FRAME_H
#define FRAME_H
#include <map>
#include<cassert>
#include <stack>
#include "Tipos.h"
#include "method_info.hpp"
#include "JavaClass.hpp"
#include "DadosDaInstancia.hpp"


class Frame{

	private:

		map<uint32_t,Valor> variaveisLocais;
		method_info *metodo;
		uint32_t pc;
		stack<Valor> pilhaOperandos;
		Objeto *objeto;
		//Ponteiro para o atributo Code referente ao método.
		Code_attribute *codeAttribute;
		//Atributo Exceptions referente ao método.
		Exceptions_attribute *exceptionsAttribute;

		// Obter um ponteiro para a pool de constantes referente ao frame atual.
		cp_info *cpInfo;

		void pegarAtributos();

	public:
		//Construtor
		Frame(Objeto *objeto, string nomeMetodo, string descritorMetodo);

		Valor getValorVariavelLocal(uint32_t indice);
		void mudarVariavelLocal(Valor valorDaVariavel, uint32_t indice);
		void empilharOperando(Valor operando);
		Valor desempilhaOperando();
		stack<Valor> retornaPilhaOperandos();
		void setaPilhaOperandos(stack<Valor> pilha);
		uint8_t *getCode();
		uint16_t tamanhoVetorVariaveis();
		uint32_t tamanhoCode();
		void incrementaPC(int32_t);
		int32_t getPC();
		Objeto *getObjeto();
};

#endif

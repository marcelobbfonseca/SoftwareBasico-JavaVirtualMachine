#ifndef FRAME_H
#define FRAME_H
#include <map>
#include <stack>
#include "Tipos.h"
#include "method_info.hpp"
#include "JavaClass.hpp"
#include "DadosDaInstancia.hpp"

class Objeto {
	public:
		DadosDaInstancia *instancia;
		JavaClass *classe;

};

class Frame{

	private:

		map<uint32_t,Valor> variaveisLocais;
		method_info *metodos;
		uint32_t PC;
		stack<Valor> pilhaOperandos;
		Objeto *objeto;
		//Ponteiro para o atributo Code referente ao método.
		Code_attribute *_codeAttribute;
		//Atributo Exceptions referente ao método.
		Exceptions_attribute *_exceptionsAttribute;

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
		uint8_t getCode();
		uint16_t tamanhoVetorVariaveis();
		uint32_t tamanhoCode() ;
		void incrementaPC();
		~Frame();
};

#endif

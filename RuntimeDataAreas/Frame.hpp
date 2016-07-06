#ifndef FRAME_H
#define FRAME_H
#include <map>
#include<cassert>
#include <stack>
#include "Tipos.h"
#include "method_info.hpp"
#include "JavaClass.hpp"
#include "DadosDaInstancia.hpp"
#include "ObjetoInstancia.hpp"
#include "RuntimeDataArea.hpp"

#ifndef RUNTIMEDATAAREA
class RuntimeDataArea;
#endif

#define FRAME
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

//		void pegarAtributos();
		void pegarAtributos(JavaClass *classe= NULL);
		method_info* BuscarMetodo(JavaClass*, string nome, string descritor, RuntimeDataArea *runtimeDataArea);

	public:
		//Construtor
		Frame(JavaClass *javaClass, string nomeMetodo, string descritor, RuntimeDataArea *runtimeDataArea);
		Frame(ObjetoInstancia *objeto, string nomeDoMetodo, string descritorMetodo, vector<Valor> argumentos, RuntimeDataArea *runtimeDataArea);
		Frame(ObjetoInstancia *objeto, JavaClass *javaClass, string nomeDoMetodo, string descritorMetodo, vector<Valor> argumentos, RuntimeDataArea *runtimeDataArea);
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

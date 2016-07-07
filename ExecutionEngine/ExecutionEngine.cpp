#include "ExecutionEngine.hpp"
#include "ObjetoArray.hpp"
#include "ObjetoString.hpp"
#include "ObjetoInstancia.hpp"
#include "Erro.hpp"
#include <string.h>
#include <inttypes.h>
#include <cmath>

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

#define DEBUG
#ifdef DEBUG
	#include"Opcode.hpp"
#endif

ExecutionEngine::ExecutionEngine(void)
{
	inicializaInstrucoes();
}

void ExecutionEngine::SetRuntimeDataArea(RuntimeDataArea *runtimeDataArea)
{
	this->runtimeDataArea= runtimeDataArea;
}

void ExecutionEngine::Play(string classComMain)
{


	uint8_t instrucao;
#ifdef DEBUG
	cout<< "ExecutionEngine::Play" << endl;
#endif
	if(runtimeDataArea == NULL)
	{
		throw new Erro("RuntimeDataArea nao instanciado!", "ExecutionEngine", "Play");
	}
	JavaClass *javaClass= runtimeDataArea->CarregarClasse(classComMain);
#ifdef DEBUG
	cout<< "ExecutionEngine::Play2" << endl;
#endif
	if(javaClass->getMetodo("main","([Ljava/lang/String;)V") == NULL)
	{
		throw new Erro("Classe informada não contém main");
	}
#ifdef DEBUG
	cout<< "ExecutionEngine::Play3" << endl;
#endif
	runtimeDataArea->empilharFrame(new Frame(javaClass, "main", "([Ljava/lang/String;)V", runtimeDataArea));
#ifdef DEBUG
	cout<< "ExecutionEngine::Play4" << endl;
#endif
	if(javaClass->getMetodo("<clinit>","()V") != NULL)
	{
#ifdef DEBUG
	cout<< "ExecutionEngine::Play5" << endl;
#endif
		runtimeDataArea->empilharFrame(new Frame(javaClass, "<clinit>","()V", runtimeDataArea));
	}
#ifdef DEBUG
	cout<< "ExecutionEngine::Play6" << endl;
#endif

	do
	{
#ifdef DEBUG
	cout<< "ExecutionEngine::Play7\tTamanho da pilha: " << runtimeDataArea->pilhaJVM.size() << endl;
#endif
		instrucao = *(runtimeDataArea->topoPilha()->getCode());
#ifdef DEBUG
	cout<< "ExecutionEngine::Play8\t" << OpCode::GetReferencia()->GetMinemonico(instrucao) << endl;

		(this->*vetorDePonteirosParaFuncao[instrucao])();
#endif

#ifdef DEBUG

	cout<< "ExecutionEngine::Play9" << endl;
#endif

	}
	while(runtimeDataArea->pilhaJVM.size() > 0);
#ifdef DEBUG
	cout<< "ExecutionEngine::Play10" << endl;
#endif
}

void ExecutionEngine::inicializaInstrucoes() {

	vetorDePonteirosParaFuncao[0x00] = &ExecutionEngine::i_nop;
	vetorDePonteirosParaFuncao[0x01] = &ExecutionEngine::i_aconst_null;
	vetorDePonteirosParaFuncao[0x02] = &ExecutionEngine::i_iconst_m1;
	vetorDePonteirosParaFuncao[0x03] = &ExecutionEngine::i_iconst_0;
	vetorDePonteirosParaFuncao[0x04] = &ExecutionEngine::i_iconst_1;
	vetorDePonteirosParaFuncao[0x05] = &ExecutionEngine::i_iconst_2;
	vetorDePonteirosParaFuncao[0x06] = &ExecutionEngine::i_iconst_3;
	vetorDePonteirosParaFuncao[0x07] = &ExecutionEngine::i_iconst_4;
	vetorDePonteirosParaFuncao[0x08] = &ExecutionEngine::i_iconst_5;
	vetorDePonteirosParaFuncao[0x09] = &ExecutionEngine::i_lconst_0;
	vetorDePonteirosParaFuncao[0x0a] = &ExecutionEngine::i_lconst_1;
	vetorDePonteirosParaFuncao[0x0b] = &ExecutionEngine::i_fconst_0;
	vetorDePonteirosParaFuncao[0x0c] = &ExecutionEngine::i_fconst_1;
	vetorDePonteirosParaFuncao[0x0d] = &ExecutionEngine::i_fconst_2;
	vetorDePonteirosParaFuncao[0x0e] = &ExecutionEngine::i_dconst_0;
	vetorDePonteirosParaFuncao[0x0f] = &ExecutionEngine::i_dconst_1;
	vetorDePonteirosParaFuncao[0x10] = &ExecutionEngine::i_bipush;
	vetorDePonteirosParaFuncao[0x11] = &ExecutionEngine::i_sipush;
	vetorDePonteirosParaFuncao[0x12] = &ExecutionEngine::i_ldc;
	vetorDePonteirosParaFuncao[0x13] = &ExecutionEngine::i_ldc_w;
	vetorDePonteirosParaFuncao[0x14] = &ExecutionEngine::i_ldc2_w;
	vetorDePonteirosParaFuncao[0x15] = &ExecutionEngine::i_iload;
	vetorDePonteirosParaFuncao[0x16] = &ExecutionEngine::i_lload;
	vetorDePonteirosParaFuncao[0x17] = &ExecutionEngine::i_fload;
	vetorDePonteirosParaFuncao[0x18] = &ExecutionEngine::i_dload;
	vetorDePonteirosParaFuncao[0x19] = &ExecutionEngine::i_aload;
	vetorDePonteirosParaFuncao[0x1a] = &ExecutionEngine::i_iload_0;
	vetorDePonteirosParaFuncao[0x1b] = &ExecutionEngine::i_iload_1;
	vetorDePonteirosParaFuncao[0x1c] = &ExecutionEngine::i_iload_2;
	vetorDePonteirosParaFuncao[0x1d] = &ExecutionEngine::i_iload_3;
	vetorDePonteirosParaFuncao[0x1e] = &ExecutionEngine::i_lload_0;
	vetorDePonteirosParaFuncao[0x1f] = &ExecutionEngine::i_lload_1;
	vetorDePonteirosParaFuncao[0x20] = &ExecutionEngine::i_lload_2;
	vetorDePonteirosParaFuncao[0x21] = &ExecutionEngine::i_lload_3;
	vetorDePonteirosParaFuncao[0x22] = &ExecutionEngine::i_fload_0;
	vetorDePonteirosParaFuncao[0x23] = &ExecutionEngine::i_fload_1;
	vetorDePonteirosParaFuncao[0x24] = &ExecutionEngine::i_fload_2;
	vetorDePonteirosParaFuncao[0x25] = &ExecutionEngine::i_fload_3;
	vetorDePonteirosParaFuncao[0x26] = &ExecutionEngine::i_dload_0;
	vetorDePonteirosParaFuncao[0x27] = &ExecutionEngine::i_dload_1;
	vetorDePonteirosParaFuncao[0x28] = &ExecutionEngine::i_dload_2;
	vetorDePonteirosParaFuncao[0x29] = &ExecutionEngine::i_dload_3;
	vetorDePonteirosParaFuncao[0x2a] = &ExecutionEngine::i_aload_0;
	vetorDePonteirosParaFuncao[0x2b] = &ExecutionEngine::i_aload_1;
	vetorDePonteirosParaFuncao[0x2c] = &ExecutionEngine::i_aload_2;
	vetorDePonteirosParaFuncao[0x2d] = &ExecutionEngine::i_aload_3;
	vetorDePonteirosParaFuncao[0x2e] = &ExecutionEngine::i_iaload;
	vetorDePonteirosParaFuncao[0x2f] = &ExecutionEngine::i_laload;
	vetorDePonteirosParaFuncao[0x30] = &ExecutionEngine::i_faload;
	vetorDePonteirosParaFuncao[0x31] = &ExecutionEngine::i_daload;
	vetorDePonteirosParaFuncao[0x32] = &ExecutionEngine::i_aaload;
	vetorDePonteirosParaFuncao[0x33] = &ExecutionEngine::i_baload;
	vetorDePonteirosParaFuncao[0x34] = &ExecutionEngine::i_caload;
	vetorDePonteirosParaFuncao[0x35] = &ExecutionEngine::i_saload;
	vetorDePonteirosParaFuncao[0x36] = &ExecutionEngine::i_istore;
	vetorDePonteirosParaFuncao[0x37] = &ExecutionEngine::i_lstore;
	vetorDePonteirosParaFuncao[0x38] = &ExecutionEngine::i_fstore;
	vetorDePonteirosParaFuncao[0x39] = &ExecutionEngine::i_dstore;
	vetorDePonteirosParaFuncao[0x3a] = &ExecutionEngine::i_astore;
	vetorDePonteirosParaFuncao[0x3b] = &ExecutionEngine::i_istore_0;
	vetorDePonteirosParaFuncao[0x3c] = &ExecutionEngine::i_istore_1;
	vetorDePonteirosParaFuncao[0x3d] = &ExecutionEngine::i_istore_2;
	vetorDePonteirosParaFuncao[0x3e] = &ExecutionEngine::i_istore_3;
	vetorDePonteirosParaFuncao[0x3f] = &ExecutionEngine::i_lstore_0;
	vetorDePonteirosParaFuncao[0x40] = &ExecutionEngine::i_lstore_1;
	vetorDePonteirosParaFuncao[0x41] = &ExecutionEngine::i_lstore_2;
	vetorDePonteirosParaFuncao[0x42] = &ExecutionEngine::i_lstore_3;
	vetorDePonteirosParaFuncao[0x43] = &ExecutionEngine::i_fstore_0;
	vetorDePonteirosParaFuncao[0x44] = &ExecutionEngine::i_fstore_1;
	vetorDePonteirosParaFuncao[0x45] = &ExecutionEngine::i_fstore_2;
	vetorDePonteirosParaFuncao[0x46] = &ExecutionEngine::i_fstore_3;
	vetorDePonteirosParaFuncao[0x47] = &ExecutionEngine::i_dstore_0;
	vetorDePonteirosParaFuncao[0x48] = &ExecutionEngine::i_dstore_1;
	vetorDePonteirosParaFuncao[0x49] = &ExecutionEngine::i_dstore_2;
	vetorDePonteirosParaFuncao[0x4a] = &ExecutionEngine::i_dstore_3;
	vetorDePonteirosParaFuncao[0x4b] = &ExecutionEngine::i_astore_0;
	vetorDePonteirosParaFuncao[0x4c] = &ExecutionEngine::i_astore_1;
	vetorDePonteirosParaFuncao[0x4d] = &ExecutionEngine::i_astore_2;
	vetorDePonteirosParaFuncao[0x4e] = &ExecutionEngine::i_astore_3;
	vetorDePonteirosParaFuncao[0x4f] = &ExecutionEngine::i_iastore;
	vetorDePonteirosParaFuncao[0x50] = &ExecutionEngine::i_lastore;
	vetorDePonteirosParaFuncao[0x51] = &ExecutionEngine::i_fastore;
	vetorDePonteirosParaFuncao[0x52] = &ExecutionEngine::i_dastore;
	vetorDePonteirosParaFuncao[0x53] = &ExecutionEngine::i_aastore;
	vetorDePonteirosParaFuncao[0x54] = &ExecutionEngine::i_bastore;
	vetorDePonteirosParaFuncao[0x55] = &ExecutionEngine::i_castore;
	vetorDePonteirosParaFuncao[0x56] = &ExecutionEngine::i_sastore;
	vetorDePonteirosParaFuncao[0x57] = &ExecutionEngine::i_pop;
	vetorDePonteirosParaFuncao[0x58] = &ExecutionEngine::i_pop2;
	vetorDePonteirosParaFuncao[0x59] = &ExecutionEngine::i_dup;
	vetorDePonteirosParaFuncao[0x5a] = &ExecutionEngine::i_dup2_x1;
	vetorDePonteirosParaFuncao[0x5b] = &ExecutionEngine::i_dup2_x2;
	vetorDePonteirosParaFuncao[0x5c] = &ExecutionEngine::i_dup2;
	vetorDePonteirosParaFuncao[0x5d] = &ExecutionEngine::i_dup2_x1;
	vetorDePonteirosParaFuncao[0x5e] = &ExecutionEngine::i_dup2_x2;
	vetorDePonteirosParaFuncao[0x5f] = &ExecutionEngine::i_swap;
	vetorDePonteirosParaFuncao[0x60] = &ExecutionEngine::i_iadd;
	vetorDePonteirosParaFuncao[0x61] = &ExecutionEngine::i_ladd;
	vetorDePonteirosParaFuncao[0x62] = &ExecutionEngine::i_fadd;
	vetorDePonteirosParaFuncao[0x63] = &ExecutionEngine::i_dadd;
	vetorDePonteirosParaFuncao[0x64] = &ExecutionEngine::i_isub;
	vetorDePonteirosParaFuncao[0x65] = &ExecutionEngine::i_lsub;
	vetorDePonteirosParaFuncao[0x66] = &ExecutionEngine::i_fsub;
	vetorDePonteirosParaFuncao[0x67] = &ExecutionEngine::i_dsub;
	vetorDePonteirosParaFuncao[0x68] = &ExecutionEngine::i_imul;
	vetorDePonteirosParaFuncao[0x69] = &ExecutionEngine::i_lmul;
	vetorDePonteirosParaFuncao[0x6a] = &ExecutionEngine::i_fmul;
	vetorDePonteirosParaFuncao[0x6b] = &ExecutionEngine::i_dmul;
	vetorDePonteirosParaFuncao[0x6c] = &ExecutionEngine::i_idiv;
	vetorDePonteirosParaFuncao[0x6d] = &ExecutionEngine::i_ldiv;
	vetorDePonteirosParaFuncao[0x6e] = &ExecutionEngine::i_fdiv;
	vetorDePonteirosParaFuncao[0x6f] = &ExecutionEngine::i_ddiv;
	vetorDePonteirosParaFuncao[0x70] = &ExecutionEngine::i_irem;
	vetorDePonteirosParaFuncao[0x71] = &ExecutionEngine::i_lrem;
	vetorDePonteirosParaFuncao[0x72] = &ExecutionEngine::i_frem;
	vetorDePonteirosParaFuncao[0x73] = &ExecutionEngine::i_drem;
	vetorDePonteirosParaFuncao[0x74] = &ExecutionEngine::i_ineg;
	vetorDePonteirosParaFuncao[0x75] = &ExecutionEngine::i_lneg;
	vetorDePonteirosParaFuncao[0x76] = &ExecutionEngine::i_fneg;
	vetorDePonteirosParaFuncao[0x77] = &ExecutionEngine::i_dneg;
	vetorDePonteirosParaFuncao[0x78] = &ExecutionEngine::i_ishl;
	vetorDePonteirosParaFuncao[0x79] = &ExecutionEngine::i_lshl;
	vetorDePonteirosParaFuncao[0x7a] = &ExecutionEngine::i_ishr;
	vetorDePonteirosParaFuncao[0x7b] = &ExecutionEngine::i_lshr;
	vetorDePonteirosParaFuncao[0x7c] = &ExecutionEngine::i_iushr;
	vetorDePonteirosParaFuncao[0x7d] = &ExecutionEngine::i_lushr;
	vetorDePonteirosParaFuncao[0x7e] = &ExecutionEngine::i_iand;
	vetorDePonteirosParaFuncao[0x7f] = &ExecutionEngine::i_land;
	vetorDePonteirosParaFuncao[0x80] = &ExecutionEngine::i_ior;
	vetorDePonteirosParaFuncao[0x81] = &ExecutionEngine::i_lor;
	vetorDePonteirosParaFuncao[0x82] = &ExecutionEngine::i_ixor;
	vetorDePonteirosParaFuncao[0x83] = &ExecutionEngine::i_lxor;
	vetorDePonteirosParaFuncao[0x84] = &ExecutionEngine::i_iinc;
	vetorDePonteirosParaFuncao[0x85] = &ExecutionEngine::i_i2l;
	vetorDePonteirosParaFuncao[0x86] = &ExecutionEngine::i_i2f;
	vetorDePonteirosParaFuncao[0x87] = &ExecutionEngine::i_i2d;
	vetorDePonteirosParaFuncao[0x88] = &ExecutionEngine::i_l2i;
	vetorDePonteirosParaFuncao[0x89] = &ExecutionEngine::i_l2f;
	vetorDePonteirosParaFuncao[0x8a] = &ExecutionEngine::i_l2d;
	vetorDePonteirosParaFuncao[0x8b] = &ExecutionEngine::i_f2i;
	vetorDePonteirosParaFuncao[0x8c] = &ExecutionEngine::i_f2l;
	vetorDePonteirosParaFuncao[0x8d] = &ExecutionEngine::i_f2d;
	vetorDePonteirosParaFuncao[0x8e] = &ExecutionEngine::i_d2i;
	vetorDePonteirosParaFuncao[0x8f] = &ExecutionEngine::i_d2l;
	vetorDePonteirosParaFuncao[0x90] = &ExecutionEngine::i_d2f;
	vetorDePonteirosParaFuncao[0x91] = &ExecutionEngine::i_i2b;
	vetorDePonteirosParaFuncao[0x92] = &ExecutionEngine::i_i2c;
	vetorDePonteirosParaFuncao[0x93] = &ExecutionEngine::i_i2s;
	vetorDePonteirosParaFuncao[0x94] = &ExecutionEngine::i_lcmp;
	vetorDePonteirosParaFuncao[0x95] = &ExecutionEngine::i_fcmpl;
	vetorDePonteirosParaFuncao[0x96] = &ExecutionEngine::i_fcmpg;
	vetorDePonteirosParaFuncao[0x97] = &ExecutionEngine::i_dcmpl;
	vetorDePonteirosParaFuncao[0x98] = &ExecutionEngine::i_dcmpg;
	vetorDePonteirosParaFuncao[0x99] = &ExecutionEngine::i_ifeq;
	vetorDePonteirosParaFuncao[0x9a] = &ExecutionEngine::i_ifne;
	vetorDePonteirosParaFuncao[0x9b] = &ExecutionEngine::i_iflt;
	vetorDePonteirosParaFuncao[0x9c] = &ExecutionEngine::i_ifge;
	vetorDePonteirosParaFuncao[0x9d] = &ExecutionEngine::i_ifgt;
	vetorDePonteirosParaFuncao[0x9e] = &ExecutionEngine::i_ifle;
	vetorDePonteirosParaFuncao[0x9f] = &ExecutionEngine::i_if_icmpeq;
	vetorDePonteirosParaFuncao[0xa0] = &ExecutionEngine::i_if_icmpne;
	vetorDePonteirosParaFuncao[0xa1] = &ExecutionEngine::i_if_icmplt;
	vetorDePonteirosParaFuncao[0xa2] = &ExecutionEngine::i_if_icmpge;
	vetorDePonteirosParaFuncao[0xa3] = &ExecutionEngine::i_if_icmpgt;
	vetorDePonteirosParaFuncao[0xa4] = &ExecutionEngine::i_if_icmple;
	vetorDePonteirosParaFuncao[0xa5] = &ExecutionEngine::i_if_acmpeq;
	vetorDePonteirosParaFuncao[0xa6] = &ExecutionEngine::i_if_acmpne;
	vetorDePonteirosParaFuncao[0xa7] = &ExecutionEngine::i_goto;
	vetorDePonteirosParaFuncao[0xa8] = &ExecutionEngine::i_jsr;
	vetorDePonteirosParaFuncao[0xa9] = &ExecutionEngine::i_ret;
	vetorDePonteirosParaFuncao[0xaa] = &ExecutionEngine::i_tableswitch;
	vetorDePonteirosParaFuncao[0xab] = &ExecutionEngine::i_lookupswitch;
	vetorDePonteirosParaFuncao[0xac] = &ExecutionEngine::i_ireturn;
	vetorDePonteirosParaFuncao[0xad] = &ExecutionEngine::i_lreturn;
	vetorDePonteirosParaFuncao[0xae] = &ExecutionEngine::i_freturn;
	vetorDePonteirosParaFuncao[0xaf] = &ExecutionEngine::i_dreturn;
	vetorDePonteirosParaFuncao[0xb0] = &ExecutionEngine::i_areturn;
	vetorDePonteirosParaFuncao[0xb1] = &ExecutionEngine::i_return;
	vetorDePonteirosParaFuncao[0xb2] = &ExecutionEngine::i_getstatic;
	vetorDePonteirosParaFuncao[0xb3] = &ExecutionEngine::i_putstatic;
	vetorDePonteirosParaFuncao[0xb4] = &ExecutionEngine::i_getfield;
	vetorDePonteirosParaFuncao[0xb5] = &ExecutionEngine::i_putfield;
	vetorDePonteirosParaFuncao[0xb6] = &ExecutionEngine::i_invokevirtual;
	vetorDePonteirosParaFuncao[0xb7] = &ExecutionEngine::i_invokespecial;
	vetorDePonteirosParaFuncao[0xb8] = &ExecutionEngine::i_invokestatic;
	vetorDePonteirosParaFuncao[0xb9] = &ExecutionEngine::i_invokeinterface;
	vetorDePonteirosParaFuncao[0xbb] = &ExecutionEngine::i_new;
	vetorDePonteirosParaFuncao[0xbc] = &ExecutionEngine::i_newarray;
	vetorDePonteirosParaFuncao[0xbd] = &ExecutionEngine::i_anewarray;
	vetorDePonteirosParaFuncao[0xbe] = &ExecutionEngine::i_arraylength;
	vetorDePonteirosParaFuncao[0xbf] = &ExecutionEngine::i_athrow;
	vetorDePonteirosParaFuncao[0xc0] = &ExecutionEngine::i_checkcast;
	vetorDePonteirosParaFuncao[0xc1] = &ExecutionEngine::i_instanceof;
	vetorDePonteirosParaFuncao[0xc2] = &ExecutionEngine::i_monitorenter;
	vetorDePonteirosParaFuncao[0xc3] = &ExecutionEngine::i_monitorexit;
	vetorDePonteirosParaFuncao[0xc4] = &ExecutionEngine::i_wide;
	vetorDePonteirosParaFuncao[0xc5] = &ExecutionEngine::i_multianewarray;
	vetorDePonteirosParaFuncao[0xc6] = &ExecutionEngine::i_ifnull;
	vetorDePonteirosParaFuncao[0xc7] = &ExecutionEngine::i_ifnonnull;
	vetorDePonteirosParaFuncao[0xc8] = &ExecutionEngine::i_goto_w;
	vetorDePonteirosParaFuncao[0xc9] = &ExecutionEngine::i_jsr_w;

}

void ExecutionEngine::i_nop(){
	//anda uma posição e faz nada
	//incrementa pc + 1
	runtimeDataArea->topoPilha()->incrementaPC(1);

}

void ExecutionEngine::i_aconst_null(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	Valor valor;
	valor.tipo = TipoDado::REFERENCE;
	valor.dado = (uint32_t)NULL;
	toppilha->empilharOperando(valor);
}

void ExecutionEngine::i_iconst_m1(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor;
	valor.tipo = TipoDado::INT;
	valor.dado = (uint32_t)-1;
	//falta uma parada de print do bastos

	toppilha->empilharOperando(valor);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_iconst_0(){

	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor;
	valor.tipo = TipoDado::INT;
	valor.dado = (uint32_t)0;
	//falta uma parada de print do bastos
	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_iconst_1(){

	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor;
	valor.tipo = TipoDado::INT;
	valor.dado = (uint32_t)1;
	//falta uma parada de print do bastos
	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);

}
void ExecutionEngine::i_iconst_2(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor;
	valor.tipo = TipoDado::INT;
	valor.dado = (uint32_t)2;
	//falta uma parada de print do bastos
	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_iconst_3(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor;
	valor.tipo = TipoDado::INT;
	valor.dado = (uint32_t)3;
	//falta uma parada de print do bastos
	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_iconst_4(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor;
	valor.tipo = TipoDado::INT;
	valor.dado = (uint32_t)4;
	//falta uma parada de print do bastos
	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);

}
void ExecutionEngine::i_iconst_5(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor;
	valor.tipo = TipoDado::INT;
	valor.dado = (uint32_t)5;
	//falta uma parada de print do bastos
	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_lconst_0(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor padding;
	padding.tipo = TipoDado::PADDING;
	padding.dado = (uint32_t)0;

	Valor valor;
	valor.tipo = TipoDado::LONG;
	valor.dado = (uint32_t)0;

	toppilha->empilharOperando(padding);
	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);


}
void ExecutionEngine::i_lconst_1(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor padding;
	padding.tipo = TipoDado::PADDING;
	padding.dado = (uint32_t)0;

	Valor valor;
	valor.tipo = TipoDado::LONG;
	valor.dado = (uint32_t)1;

	toppilha->empilharOperando(padding);
	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_fconst_0(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor;
	valor.tipo = TipoDado::FLOAT;
	valor.dado = (uint32_t)0;

	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_fconst_1(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor;
	valor.tipo = TipoDado::FLOAT;
	valor.dado = (uint32_t)1;

	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_fconst_2(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor;
	valor.tipo = TipoDado::FLOAT;
	valor.dado = (uint32_t)2;

	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_dconst_0(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor padding;
	padding.tipo = TipoDado::PADDING;

	Valor valor;
	valor.tipo = TipoDado::DOUBLE;
	double temp =0;
	memcpy(&valor.dado, &temp, 8/*sizeof(double)*/);

	toppilha->empilharOperando(padding);
	toppilha->empilharOperando(valor);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_dconst_1(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor padding;
	padding.tipo = TipoDado::PADDING;

	Valor valor;
	valor.tipo = TipoDado::DOUBLE;
	double temp =1;
	memcpy(&valor.dado, &temp, 8/*sizeof(double)*/);

	toppilha->empilharOperando(padding);
	toppilha->empilharOperando(valor);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_bipush(){

	Frame *topo = runtimeDataArea->topoPilha();

		uint8_t *code = topo->getCode();
	uint8_t byte = code[1];

		Valor valor;
		valor.tipo = TipoDado::INT;
		valor.dado = (int32_t) (int8_t) byte; // convertendo para inteiro e estendendo o sinal

		topo->empilharOperando(valor);

		topo->incrementaPC(2);

}
void ExecutionEngine::i_sipush(){

}
void ExecutionEngine::i_ldc(){
	//usa no helloworld
}
void ExecutionEngine::i_ldc_w(){

}
void ExecutionEngine::i_ldc2_w(){
	//double

}
void ExecutionEngine::i_iload(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	uint8_t *code = toppilha->getCode();
	uint8_t byte1 = code[1];
	int16_t index = (int16_t)byte1;
	
	if(isWide) {
		uint16_t byte2 = code[2];
		index = (byte1 << 8) | byte2;
		runtimeDataArea->topoPilha()->incrementaPC(3);
		isWide = false;
	}
	else {
		runtimeDataArea->topoPilha()->incrementaPC(2);
	}
	assert(((int16_t)(toppilha->tamanhoVetorVariaveis())) > index);
	Valor valor = toppilha->getValorVariavelLocal(index);
	assert(valor.tipo == TipoDado::INT);
	
	toppilha->empilharOperando(valor);
}
void ExecutionEngine::i_lload(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	uint8_t *code = toppilha->getCode();
	uint8_t byte1 = code[1];
	int16_t index = (int16_t)byte1;
	
	if(isWide) {
		uint16_t byte2 = code[2];
		index = (byte1 << 8) | byte2;
		runtimeDataArea->topoPilha()->incrementaPC(3);
		isWide = false;
	}
	else {
		runtimeDataArea->topoPilha()->incrementaPC(2);
	}
	assert(((int16_t)(toppilha->tamanhoVetorVariaveis())) > index + 1);
	Valor valor = toppilha->getValorVariavelLocal(index);
	assert(valor.tipo == TipoDado::LONG);
	
	Valor padding;
	padding.dado = TipoDado::PADDING;
	
	toppilha->empilharOperando(padding);
	toppilha->empilharOperando(valor);
}
void ExecutionEngine::i_fload(){
	Frame *topPilha = runtimeDataArea->topoPilha();
	
	uint8_t *code = topPilha->getCode();
	uint8_t byte1 = code[1];
	int16_t index = (int16_t)byte1;
	
	if(isWide) {
		uint16_t byte2 = code[2];
		index = (byte1 << 8) | byte2;
		runtimeDataArea->topoPilha()->incrementaPC(3);
		isWide = false;
	}
	else {
		runtimeDataArea->topoPilha()->incrementaPC(2);
	}
	assert(((int16_t)(topPilha->tamanhoVetorVariaveis())) > index);
	Valor valor = topPilha->getValorVariavelLocal(index);
	assert(valor.tipo == TipoDado::FLOAT);
	
	topPilha->empilharOperando(valor);
}
void ExecutionEngine::i_dload(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	uint8_t *code = toppilha->getCode();
	uint8_t byte1 = code[1];
	int16_t index = (int16_t)byte1;
	
	if(isWide) {
		uint16_t byte2 = code[2];
		index = (byte1 << 8) | byte2;
		runtimeDataArea->topoPilha()->incrementaPC(3);
		isWide = false;
	}
	else {
		runtimeDataArea->topoPilha()->incrementaPC(2);
	}
	assert(((int16_t)(toppilha->tamanhoVetorVariaveis())) > index + 1);
	Valor valor = toppilha->getValorVariavelLocal(index);
	assert(valor.tipo == TipoDado::DOUBLE);
	
	Valor padding;
	padding.dado = TipoDado::PADDING;
	
	toppilha->empilharOperando(padding);
	toppilha->empilharOperando(valor);
}
void ExecutionEngine::i_aload(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	uint8_t *code = toppilha->getCode();
	uint8_t byte1 = code[1];
	int16_t index = (int16_t)byte1;
	
	if(isWide) {
		uint16_t byte2 = code[2];
		index = (byte1 << 8) | byte2;
		runtimeDataArea->topoPilha()->incrementaPC(3);
		isWide = false;
	}
	else {
		runtimeDataArea->topoPilha()->incrementaPC(2);
	}
	assert(((int16_t)(toppilha->tamanhoVetorVariaveis())) > index);
	Valor valor = toppilha->getValorVariavelLocal(index);
	assert(valor.tipo == TipoDado::REFERENCE);
	
	toppilha->empilharOperando(valor);
}
void ExecutionEngine::i_iload_0(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->getValorVariavelLocal(0);
	assert(valor.tipo == TipoDado::INT);
	toppilha->empilharOperando(valor);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_iload_1(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->getValorVariavelLocal(1);
	assert(valor.tipo == TipoDado::INT);
	toppilha->empilharOperando(valor);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_iload_2(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->getValorVariavelLocal(2);
	assert(valor.tipo == TipoDado::INT);
	toppilha->empilharOperando(valor);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_iload_3(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->getValorVariavelLocal(3);
	assert(valor.tipo == TipoDado::INT);
	toppilha->empilharOperando(valor);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_lload_0(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->getValorVariavelLocal(1);
	assert(valor.tipo == TipoDado::PADDING);
	toppilha->empilharOperando(valor);

	valor = toppilha->getValorVariavelLocal(0);
	assert(valor.tipo == TipoDado::LONG);
	toppilha->empilharOperando(valor);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_lload_1(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->getValorVariavelLocal(2);
	assert(valor.tipo == TipoDado::PADDING);
	toppilha->empilharOperando(valor);

	valor = toppilha->getValorVariavelLocal(1);
	assert(valor.tipo == TipoDado::LONG);
	toppilha->empilharOperando(valor);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_lload_2(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->getValorVariavelLocal(1);
	assert(valor.tipo == TipoDado::PADDING);
	toppilha->empilharOperando(valor);

	valor = toppilha->getValorVariavelLocal(2);
	assert(valor.tipo == TipoDado::LONG);
	toppilha->empilharOperando(valor);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_lload_3(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->getValorVariavelLocal(4);
	assert(valor.tipo == TipoDado::PADDING);
	toppilha->empilharOperando(valor);

	valor = toppilha->getValorVariavelLocal(3);
	assert(valor.tipo == TipoDado::LONG);
	toppilha->empilharOperando(valor);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_fload_0(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->getValorVariavelLocal(0);
	assert(valor.tipo == TipoDado::FLOAT);
	toppilha->empilharOperando(valor);

	runtimeDataArea->topoPilha()->incrementaPC(1);	
}
void ExecutionEngine::i_fload_1(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->getValorVariavelLocal(1);
	assert(valor.tipo == TipoDado::FLOAT);
	toppilha->empilharOperando(valor);

	runtimeDataArea->topoPilha()->incrementaPC(1);	
}
void ExecutionEngine::i_fload_2(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->getValorVariavelLocal(2);
	assert(valor.tipo == TipoDado::FLOAT);
	toppilha->empilharOperando(valor);

	runtimeDataArea->topoPilha()->incrementaPC(1);		
}
void ExecutionEngine::i_fload_3(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->getValorVariavelLocal(3);
	assert(valor.tipo == TipoDado::FLOAT);
	toppilha->empilharOperando(valor);

	runtimeDataArea->topoPilha()->incrementaPC(1);	
}
void ExecutionEngine::i_dload_0(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->getValorVariavelLocal(1);
	assert(valor.tipo == TipoDado::PADDING);
	toppilha->empilharOperando(valor);

	valor = toppilha->getValorVariavelLocal(0);
	assert(valor.tipo == TipoDado::DOUBLE);
	toppilha->empilharOperando(valor);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}	
void ExecutionEngine::i_dload_1(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->getValorVariavelLocal(2);
	assert(valor.tipo == TipoDado::PADDING);
	toppilha->empilharOperando(valor);

	valor = toppilha->getValorVariavelLocal(1);
	assert(valor.tipo == TipoDado::DOUBLE);
	toppilha->empilharOperando(valor);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_dload_2(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->getValorVariavelLocal(3);
	assert(valor.tipo == TipoDado::PADDING);
	toppilha->empilharOperando(valor);

	valor = toppilha->getValorVariavelLocal(2);
	assert(valor.tipo == TipoDado::DOUBLE);
	toppilha->empilharOperando(valor);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_dload_3(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->getValorVariavelLocal(4);
	assert(valor.tipo == TipoDado::PADDING);
	toppilha->empilharOperando(valor);

	valor = toppilha->getValorVariavelLocal(3);
	assert(valor.tipo == TipoDado::DOUBLE);
	toppilha->empilharOperando(valor);

	runtimeDataArea->topoPilha()->incrementaPC(1);

}
void ExecutionEngine::i_aload_0(){
	//usa na mainvazia
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->getValorVariavelLocal(0);
	assert(valor.tipo == TipoDado::REFERENCE);

	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_aload_1(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->getValorVariavelLocal(1);
	assert(valor.tipo == TipoDado::REFERENCE);

	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_aload_2(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->getValorVariavelLocal(2);
	assert(valor.tipo == TipoDado::REFERENCE);

	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_aload_3(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->getValorVariavelLocal(3);
	assert(valor.tipo == TipoDado::REFERENCE);

	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_iaload(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	ObjetoArray *array;
	
	Valor index = toppilha->desempilhaOperando();
	assert(index.tipo == TipoDado::INT);
	
	Valor arrayref = toppilha->desempilhaOperando();
	assert(arrayref.tipo == TipoDado::REFERENCE);
	assert(((Objeto*)(arrayref.dado))->ObterTipoObjeto() == TipoObjeto::ARRAY);
	
	array = (ObjetoArray*)(arrayref.dado);
	
	if (array == NULL) {
		throw new Erro("Array esta vazia.", "ExecutionEngine", "i_iaload");
	}
	int32_t num;
	memcpy(&num, &(index.dado), 4);
	if (num > array->ObterTamanho() || num < 0) {
		throw new Erro("Index do array esta fora do limite.", "ExecutionEngine", "i_iaload");
	}
	toppilha->empilharOperando(array->ObterValor(num));
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_laload(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	ObjetoArray *array;
	
	Valor index = toppilha->desempilhaOperando();
	assert(index.tipo == TipoDado::LONG);
	
	Valor arrayref = toppilha->desempilhaOperando();
	assert(arrayref.tipo == TipoDado::REFERENCE);
	assert(((Objeto*)(arrayref.dado))->ObterTipoObjeto() == TipoObjeto::ARRAY);
	
	array = (ObjetoArray*)(arrayref.dado);
	
	if (array == NULL) {
		throw new Erro("Array esta vazia.", "ExecutionEngine", "i_laload");
	}
	int64_t num;
	memcpy(&num, &(index.dado), 8);
	if (num > array->ObterTamanho() || num < 0) {
		throw new Erro("Index do array esta fora do limite.", "ExecutionEngine", "i_laload");
	}
	
	Valor padding;
	padding.dado = TipoDado::PADDING;
	
	toppilha->empilharOperando(padding);
	toppilha->empilharOperando(array->ObterValor(num));
	
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_faload(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	ObjetoArray *array;
	
	Valor index = toppilha->desempilhaOperando();
	assert(index.tipo == TipoDado::FLOAT);
	
	Valor arrayref = toppilha->desempilhaOperando();
	assert(arrayref.tipo == TipoDado::REFERENCE);
	assert(((Objeto*)(arrayref.dado))->ObterTipoObjeto() == TipoObjeto::ARRAY);
	
	array = (ObjetoArray*)(arrayref.dado);
	
	if (array == NULL) {
		throw new Erro("Array esta vazia.", "ExecutionEngine", "i_faload");
	}
	int32_t num;
	memcpy(&num, &(index.dado), 4);
	if (num > array->ObterTamanho() || num < 0) {
		throw new Erro("Index do array esta fora do limite.", "ExecutionEngine", "i_faload");
	}
	toppilha->empilharOperando(array->ObterValor(num));
	
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_daload(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	ObjetoArray *array;
	
	Valor index = toppilha->desempilhaOperando();
	assert(index.tipo == TipoDado::DOUBLE);
	
	Valor arrayref = toppilha->desempilhaOperando();
	assert(arrayref.tipo == TipoDado::REFERENCE);
	assert(((Objeto*)(arrayref.dado))->ObterTipoObjeto() == TipoObjeto::ARRAY);
	
	array = (ObjetoArray*)(arrayref.dado);
	
	if (array == NULL) {
		throw new Erro("Array esta vazia.", "ExecutionEngine", "i_daload");
	}
	int64_t num;
	memcpy(&num, &(index.dado), 8);
	if (num > array->ObterTamanho() || num < 0) {
		throw new Erro("Index do array esta fora do limite.", "ExecutionEngine", "i_daload");
	}
	
	Valor padding;
	padding.dado = TipoDado::PADDING;
	
	toppilha->empilharOperando(padding);
	toppilha->empilharOperando(array->ObterValor(num));
	
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_aaload(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	ObjetoArray *array;
	
	Valor index = toppilha->desempilhaOperando();
	assert(index.tipo == TipoDado::REFERENCE);
	
	Valor arrayref = toppilha->desempilhaOperando();
	assert(arrayref.tipo == TipoDado::REFERENCE);
	assert(((Objeto*)(arrayref.dado))->ObterTipoObjeto() == TipoObjeto::ARRAY);
	
	array = (ObjetoArray*)(arrayref.dado);
	
	if (array == NULL) {
		throw new Erro("Array esta vazia.", "ExecutionEngine", "i_aaload");
	}
	int32_t num;
	memcpy(&num, &(index.dado), 4);
	if (num > array->ObterTamanho() || num < 0) {
		throw new Erro("Index do array esta fora do limite.", "ExecutionEngine", "i_aaload");
	}
	toppilha->empilharOperando(array->ObterValor(num));
	
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_baload(){}
void ExecutionEngine::i_caload(){}
void ExecutionEngine::i_saload(){}
void ExecutionEngine::i_istore(){}
void ExecutionEngine::i_lstore(){}
void ExecutionEngine::i_fstore(){}
void ExecutionEngine::i_dstore(){}
void ExecutionEngine::i_astore(){}
void ExecutionEngine::i_istore_0(){}
void ExecutionEngine::i_istore_1(){}
void ExecutionEngine::i_istore_2(){}
void ExecutionEngine::i_istore_3(){}
void ExecutionEngine::i_lstore_0(){}
void ExecutionEngine::i_lstore_1(){}
void ExecutionEngine::i_lstore_2(){}
void ExecutionEngine::i_lstore_3(){}
void ExecutionEngine::i_fstore_0(){}
void ExecutionEngine::i_fstore_1(){}
void ExecutionEngine::i_fstore_2(){}
void ExecutionEngine::i_fstore_3(){}
void ExecutionEngine::i_dstore_0(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->desempilhaOperando();
	assert(valor.tipo == TipoDado::DOUBLE);
	
	toppilha->mudarVariavelLocal(valor, 0);

	valor = toppilha->desempilhaOperando();
	assert(valor.tipo == TipoDado::PADDING);
	toppilha->mudarVariavelLocal(valor, 1);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_dstore_1(){
	//double
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->desempilhaOperando();
	assert(valor.tipo == TipoDado::DOUBLE);
	
	toppilha->mudarVariavelLocal(valor, 1);

	valor = toppilha->desempilhaOperando();
	assert(valor.tipo == TipoDado::PADDING);
	toppilha->mudarVariavelLocal(valor, 2);

	runtimeDataArea->topoPilha()->incrementaPC(1);

}
void ExecutionEngine::i_dstore_2(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->desempilhaOperando();
	assert(valor.tipo == TipoDado::DOUBLE);
	
	toppilha->mudarVariavelLocal(valor, 2);

	valor = toppilha->desempilhaOperando();
	assert(valor.tipo == TipoDado::PADDING);
	toppilha->mudarVariavelLocal(valor, 3);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_dstore_3(){
	//double
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->desempilhaOperando();
	assert(valor.tipo == TipoDado::DOUBLE);
	
	toppilha->mudarVariavelLocal(valor, 3);

	valor = toppilha->desempilhaOperando();
	assert(valor.tipo == TipoDado::PADDING);
	toppilha->mudarVariavelLocal(valor, 4);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_astore_0(){}
void ExecutionEngine::i_astore_1(){}
void ExecutionEngine::i_astore_2(){}
void ExecutionEngine::i_astore_3(){}
void ExecutionEngine::i_iastore(){}
void ExecutionEngine::i_lastore(){}
void ExecutionEngine::i_fastore(){}
void ExecutionEngine::i_dastore(){}
void ExecutionEngine::i_aastore(){}
void ExecutionEngine::i_bastore(){}
void ExecutionEngine::i_castore(){}
void ExecutionEngine::i_sastore(){}
void ExecutionEngine::i_pop(){}
void ExecutionEngine::i_pop2(){}
void ExecutionEngine::i_dup(){}
void ExecutionEngine::i_dup_x1(){}
void ExecutionEngine::i_dup_x2(){}
void ExecutionEngine::i_dup2(){}
void ExecutionEngine::i_dup2_x1(){}
void ExecutionEngine::i_dup2_x2(){}
void ExecutionEngine::i_swap(){}
void ExecutionEngine::i_iadd(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	Valor valor1 = toppilha->desempilhaOperando();
	
	assert(valor2.tipo == TipoDado::INT);
	assert(valor1.tipo == TipoDado::INT);
	
	int32_t num1, num2;
	memcpy(&num1,&valor1.dado,4);
	memcpy(&num2,&valor2.dado,4);
	
	num1 = num1 + num2;
	memcpy(&valor1.dado,&num1,4);
	
	toppilha->empilharOperando(valor1);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_ladd(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	toppilha->desempilhaOperando(); //padding
	Valor valor1 = toppilha->desempilhaOperando();
	
	assert(valor2.tipo == TipoDado::LONG);
	assert(valor1.tipo == TipoDado::LONG);
	
	int64_t num1, num2;
	memcpy(&num1,&valor1.dado,8);
	memcpy(&num2,&valor2.dado,8);
	
	num1 = num1 + num2;
	memcpy(&valor1.dado,&num1,8);
	
	toppilha->empilharOperando(valor1);
	runtimeDataArea->topoPilha()->incrementaPC(1);	
}
void ExecutionEngine::i_fadd(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	Valor valor1 = toppilha->desempilhaOperando();
	
	assert(valor2.tipo == TipoDado::FLOAT);
	assert(valor1.tipo == TipoDado::FLOAT);
	
	int32_t num1, num2;
	memcpy(&num1,&valor1.dado,4);
	memcpy(&num2,&valor2.dado,4);
	
	num1 = num1 + num2;
	memcpy(&valor1.dado,&num1,4);
	
	toppilha->empilharOperando(valor1);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_dadd(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	toppilha->desempilhaOperando(); //padding
	Valor valor1 = toppilha->desempilhaOperando();
	
	assert(valor2.tipo == TipoDado::DOUBLE);
	assert(valor1.tipo == TipoDado::DOUBLE);
	
	int64_t num1, num2;
	memcpy(&num1,&valor1.dado,8);
	memcpy(&num2,&valor2.dado,8);
	
	num1 = num1 + num2;
	memcpy(&valor1.dado,&num1,8);
	
	toppilha->empilharOperando(valor1);
	runtimeDataArea->topoPilha()->incrementaPC(1);	
}
void ExecutionEngine::i_isub(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	Valor valor1 = toppilha->desempilhaOperando();
	
	assert(valor2.tipo == TipoDado::INT);
	assert(valor1.tipo == TipoDado::INT);
	
	int32_t num1, num2;
	memcpy(&num1,&valor1.dado,4);
	memcpy(&num2,&valor2.dado,4);
	
	num1 = num1 - num2;
	memcpy(&valor1.dado,&num1,4);
	
	toppilha->empilharOperando(valor1);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_lsub(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	toppilha->desempilhaOperando(); //padding
	Valor valor1 = toppilha->desempilhaOperando();
	
	assert(valor2.tipo == TipoDado::LONG);
	assert(valor1.tipo == TipoDado::LONG);
	
	int64_t num1, num2;
	memcpy(&num1,&valor1.dado,8);
	memcpy(&num2,&valor2.dado,8);
	
	num1 = num1 - num2;
	memcpy(&valor1.dado,&num1,8);
	
	toppilha->empilharOperando(valor1);
	runtimeDataArea->topoPilha()->incrementaPC(1);	
}
void ExecutionEngine::i_fsub(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	Valor valor1 = toppilha->desempilhaOperando();
	
	assert(valor2.tipo == TipoDado::FLOAT);
	assert(valor1.tipo == TipoDado::FLOAT);
	
	int32_t num1, num2;
	memcpy(&num1,&valor1.dado,4);
	memcpy(&num2,&valor2.dado,4);
	
	num1 = num1 - num2;
	memcpy(&valor1.dado,&num1,4);
	
	toppilha->empilharOperando(valor1);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_dsub(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	toppilha->desempilhaOperando(); //padding
	Valor valor1 = toppilha->desempilhaOperando();
	
	assert(valor2.tipo == TipoDado::DOUBLE);
	assert(valor1.tipo == TipoDado::DOUBLE);
	
	int64_t num1, num2;
	memcpy(&num1,&valor1.dado,8);
	memcpy(&num2,&valor2.dado,8);
	
	num1 = num1 - num2;
	memcpy(&valor1.dado,&num1,8);
	
	toppilha->empilharOperando(valor1);
	runtimeDataArea->topoPilha()->incrementaPC(1);	
}
void ExecutionEngine::i_imul(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	Valor valor1 = toppilha->desempilhaOperando();
	
	assert(valor2.tipo == TipoDado::INT);
	assert(valor1.tipo == TipoDado::INT);
	
	int32_t num1, num2;
	memcpy(&num1,&valor1.dado,4);
	memcpy(&num2,&valor2.dado,4);
	
	num1 = num1 * num2;
	memcpy(&valor1.dado,&num1,4);
	
	toppilha->empilharOperando(valor1);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_lmul(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	toppilha->desempilhaOperando(); //padding
	Valor valor1 = toppilha->desempilhaOperando();
	
	assert(valor2.tipo == TipoDado::LONG);
	assert(valor1.tipo == TipoDado::LONG);
	
	int64_t num1, num2;
	memcpy(&num1,&valor1.dado,8);
	memcpy(&num2,&valor2.dado,8);
	
	num1 = num1 * num2;
	memcpy(&valor1.dado,&num1,8);
	
	toppilha->empilharOperando(valor1);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_fmul(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	Valor valor1 = toppilha->desempilhaOperando();
	
	assert(valor2.tipo == TipoDado::FLOAT);
	assert(valor1.tipo == TipoDado::FLOAT);
	
	int32_t num1, num2;
	memcpy(&num1,&valor1.dado,4);
	memcpy(&num2,&valor2.dado,4);
	
	num1 = num1 * num2;
	memcpy(&valor1.dado,&num1,4);
	
	toppilha->empilharOperando(valor1);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_dmul(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	toppilha->desempilhaOperando(); //padding
	Valor valor1 = toppilha->desempilhaOperando();
	
	assert(valor2.tipo == TipoDado::DOUBLE);
	assert(valor1.tipo == TipoDado::DOUBLE);
	
	int64_t num1, num2;
	memcpy(&num1,&valor1.dado,8);
	memcpy(&num2,&valor2.dado,8);
	
	num1 = num1 * num2;
	memcpy(&valor1.dado,&num1,8);
	
	toppilha->empilharOperando(valor1);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_idiv(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	Valor valor1 = toppilha->desempilhaOperando();
	
	assert(valor2.tipo == TipoDado::INT);
	assert(valor1.tipo == TipoDado::INT);
	
	int32_t num1, num2;
	memcpy(&num1,&valor1.dado,4);
	memcpy(&num2,&valor2.dado,4);
	
	if (num2 == 0) {
		throw new Erro("Divisao por zero.","ExecutionEngine","i_idiv");
	}
	
	num1 = num1 / num2;
	memcpy(&valor1.dado,&num1,4);
	
	toppilha->empilharOperando(valor1);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_ldiv(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	toppilha->desempilhaOperando(); //padding
	Valor valor1 = toppilha->desempilhaOperando();
	
	assert(valor2.tipo == TipoDado::LONG);
	assert(valor1.tipo == TipoDado::LONG);
	
	int64_t num1, num2;
	memcpy(&num1,&valor1.dado,8);
	memcpy(&num2,&valor2.dado,8);
	
	if (num2 == 0) {
		throw new Erro("Divisao por zero.","ExecutionEngine","i_ldiv");
	}
	
	num1 = num1 / num2;
	memcpy(&valor1.dado,&num1,8);
	
	toppilha->empilharOperando(valor1);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_fdiv(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	Valor valor1 = toppilha->desempilhaOperando();
	
	assert(valor2.tipo == TipoDado::FLOAT);
	assert(valor1.tipo == TipoDado::FLOAT);
	
	int32_t num1, num2;
	memcpy(&num1,&valor1.dado,4);
	memcpy(&num2,&valor2.dado,4);
	
	if (num2 == 0) {
		throw new Erro("Divisao por zero.","ExecutionEngine","i_fdiv");
	}
	
	num1 = num1 / num2;
	memcpy(&valor1.dado,&num1,4);
	
	toppilha->empilharOperando(valor1);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_ddiv(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	toppilha->desempilhaOperando(); //padding
	Valor valor1 = toppilha->desempilhaOperando();
	
	assert(valor2.tipo == TipoDado::DOUBLE);
	assert(valor1.tipo == TipoDado::DOUBLE);
	
	int64_t num1, num2;
	memcpy(&num1,&valor1.dado,8);
	memcpy(&num2,&valor2.dado,8);
	
	if (num2 == 0) {
		throw new Erro("Divisao por zero.","ExecutionEngine","i_ddiv");
	}
	
	num1 = num1 / num2;
	memcpy(&valor1.dado,&num1,8);
	
	toppilha->empilharOperando(valor1);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_irem(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	Valor valor1 = toppilha->desempilhaOperando();
	
	assert(valor2.tipo == TipoDado::INT);
	assert(valor1.tipo == TipoDado::INT);
	
	int32_t num1, num2;
	memcpy(&num1,&valor1.dado,4);
	memcpy(&num2,&valor2.dado,4);
	
	if (num2 == 0) {
		throw new Erro("Divisao por zero.","ExecutionEngine","i_idiv");
	}
	
	num1 = num1 - ((num1 / num2) * num2);
	memcpy(&valor1.dado,&num1,4);
	
	toppilha->empilharOperando(valor1);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_lrem(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	toppilha->desempilhaOperando(); //padding
	Valor valor1 = toppilha->desempilhaOperando();
	
	assert(valor2.tipo == TipoDado::LONG);
	assert(valor1.tipo == TipoDado::LONG);
	
	int64_t num1, num2;
	memcpy(&num1,&valor1.dado,8);
	memcpy(&num2,&valor2.dado,8);
	
	if (num2 == 0) {
		throw new Erro("Divisao por zero.","ExecutionEngine","i_ldiv");
	}
	
	num1 = num1 - ((num1 / num2) * num2);
	memcpy(&valor1.dado,&num1,8);
	
	toppilha->empilharOperando(valor1);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_frem(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	Valor valor1 = toppilha->desempilhaOperando();
	
	assert(valor2.tipo == TipoDado::FLOAT);
	assert(valor1.tipo == TipoDado::FLOAT);
	
	int32_t num1, num2;
	memcpy(&num1,&valor1.dado,4);
	memcpy(&num2,&valor2.dado,4);
	
	if (num2 == 0) {
		throw new Erro("Divisao por zero.","ExecutionEngine","i_fdiv");
	}
	
	num1 = num1 - ((num1 / num2) * num2);
	memcpy(&valor1.dado,&num1,4);
	
	toppilha->empilharOperando(valor1);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_drem(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	toppilha->desempilhaOperando(); //padding
	Valor valor1 = toppilha->desempilhaOperando();
	
	assert(valor2.tipo == TipoDado::DOUBLE);
	assert(valor1.tipo == TipoDado::DOUBLE);
	
	int64_t num1, num2;
	memcpy(&num1,&valor1.dado,8);
	memcpy(&num2,&valor2.dado,8);
	
	if (num2 == 0) {
		throw new Erro("Divisao por zero.","ExecutionEngine","i_ddiv");
	}
	
	num1 = num1 - ((num1 / num2) * num2);
	memcpy(&valor1.dado,&num1,8);
	
	toppilha->empilharOperando(valor1);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_ineg(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor = toppilha->desempilhaOperando();
	assert(valor.tipo == TipoDado::INT);
	
	int32_t num;
	memcpy(&num,&valor.dado,4);
	
	num = -num;
	memcpy(&valor.dado,&num,4);
	
	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_lneg(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor = toppilha->desempilhaOperando();
	assert(valor.tipo == TipoDado::LONG);
	
	int64_t num;
	memcpy(&num,&valor.dado,8);
	
	num = -num;
	memcpy(&valor.dado,&num,8);
	
	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_fneg(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor = toppilha->desempilhaOperando();
	assert(valor.tipo == TipoDado::FLOAT);
	
	int32_t num;
	memcpy(&num,&valor.dado,4);
	
	num = -num;
	memcpy(&valor.dado,&num,4);
	
	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_dneg(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor = toppilha->desempilhaOperando();
	assert(valor.tipo == TipoDado::DOUBLE);
	
	int64_t num;
	memcpy(&num,&valor.dado,8);
	
	num = -num;
	memcpy(&valor.dado,&num,8);
	
	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_ishl(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	Valor valor1 = toppilha->desempilhaOperando();
	
	assert(valor2.tipo == TipoDado::INT);
	assert(valor1.tipo == TipoDado::INT);
	
	int32_t num1, num2;
	memcpy(&num1,&valor1.dado,4);
	memcpy(&num2,&valor2.dado,4);
	
	num2 = 0x1f & num2;
	num1 = num1 << num2;
	memcpy(&valor1.dado,&num1,4);
	
	toppilha->empilharOperando(valor1);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_lshl(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	Valor valor1 = toppilha->desempilhaOperando();
	
	assert(valor2.tipo == TipoDado::INT);
	assert(valor1.tipo == TipoDado::LONG);
	
	int32_t num1, num2;
	memcpy(&num1,&valor1.dado,8);
	memcpy(&num2,&valor2.dado,8);
	
	num2 = 0x3f & num2;
	num1 = num1 << num2;
	memcpy(&valor1.dado,&num1,8);
	
	toppilha->empilharOperando(valor1);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_ishr(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	Valor valor1 = toppilha->desempilhaOperando();
	
	assert(valor2.tipo == TipoDado::INT);
	assert(valor1.tipo == TipoDado::INT);
	
	int32_t num1, num2;
	memcpy(&num1,&valor1.dado,4);
	memcpy(&num2,&valor2.dado,4);
	
	num2 = 0x1f & num2;
	num1 = num1 >> num2;
	memcpy(&valor1.dado,&num1,4);
	
	toppilha->empilharOperando(valor1);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_lshr(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	Valor valor1 = toppilha->desempilhaOperando();
	
	assert(valor2.tipo == TipoDado::INT);
	assert(valor1.tipo == TipoDado::LONG);
	
	int32_t num1, num2;
	memcpy(&num1,&valor1.dado,8);
	memcpy(&num2,&valor2.dado,8);
	
	num2 = 0x3f & num2;
	num1 = num1 >> num2;
	memcpy(&valor1.dado,&num1,8);
	
	toppilha->empilharOperando(valor1);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_iushr(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	Valor valor1 = toppilha->desempilhaOperando();
	
	assert(valor2.tipo == TipoDado::INT);
	assert(valor1.tipo == TipoDado::INT);
	
	int32_t num1, num2;
	memcpy(&num1,&valor1.dado,4);
	memcpy(&num2,&valor2.dado,4);
	
	num2 = 0x1f & num2;
	num1 = num1 >> num2;
	
	if (num1 < 0) {
		num1 = num1 + (2<<~(num2));
	}
	
	memcpy(&valor1.dado,&num1,4);
	
	toppilha->empilharOperando(valor1);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_lushr(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	Valor valor1 = toppilha->desempilhaOperando();
	
	assert(valor2.tipo == TipoDado::INT);
	assert(valor1.tipo == TipoDado::LONG);
	
	int32_t num1, num2;
	memcpy(&num1,&valor1.dado,8);
	memcpy(&num2,&valor2.dado,8);
	
	num2 = 0x3f & num2;
	num1 = num1 >> num2;
	
	if (num1 < 0) {
		num1 = num1 + (2<<~(num2));
	}
	
	memcpy(&valor1.dado,&num1,8);
	
	toppilha->empilharOperando(valor1);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_iand(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	Valor valor1 = toppilha->desempilhaOperando();
	
	assert(valor2.tipo == TipoDado::INT);
	assert(valor1.tipo == TipoDado::INT);
	
	int32_t num1, num2;
	memcpy(&num1,&valor1.dado,4);
	memcpy(&num2,&valor2.dado,4);
	
	num1 = num1 & num2;
	memcpy(&valor1.dado,&num1,4);
	
	toppilha->empilharOperando(valor1);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_land(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	toppilha->desempilhaOperando(); //padding
	Valor valor1 = toppilha->desempilhaOperando();
	
	assert(valor2.tipo == TipoDado::LONG);
	assert(valor1.tipo == TipoDado::LONG);
	
	int64_t num1, num2;
	memcpy(&num1,&valor1.dado,8);
	memcpy(&num2,&valor2.dado,8);
	
	num1 = num1 & num2;
	memcpy(&valor1.dado,&num1,8);
	
	toppilha->empilharOperando(valor1);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_ior(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	Valor valor1 = toppilha->desempilhaOperando();
	
	assert(valor2.tipo == TipoDado::INT);
	assert(valor1.tipo == TipoDado::INT);
	
	int32_t num1, num2;
	memcpy(&num1,&valor1.dado,4);
	memcpy(&num2,&valor2.dado,4);
	
	num1 = num1 | num2;
	memcpy(&valor1.dado,&num1,4);
	
	toppilha->empilharOperando(valor1);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_lor(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	toppilha->desempilhaOperando(); //padding
	Valor valor1 = toppilha->desempilhaOperando();
	
	assert(valor2.tipo == TipoDado::LONG);
	assert(valor1.tipo == TipoDado::LONG);
	
	int64_t num1, num2;
	memcpy(&num1,&valor1.dado,8);
	memcpy(&num2,&valor2.dado,8);
	
	num1 = num1 | num2;
	memcpy(&valor1.dado,&num1,8);
	
	toppilha->empilharOperando(valor1);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_ixor(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	Valor valor1 = toppilha->desempilhaOperando();
	
	assert(valor2.tipo == TipoDado::INT);
	assert(valor1.tipo == TipoDado::INT);
	
	int32_t num1, num2;
	memcpy(&num1,&valor1.dado,4);
	memcpy(&num2,&valor2.dado,4);
	
	num1 = num1 ^ num2;
	memcpy(&valor1.dado,&num1,4);
	
	toppilha->empilharOperando(valor1);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_lxor(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	toppilha->desempilhaOperando(); //padding
	Valor valor1 = toppilha->desempilhaOperando();
	
	assert(valor2.tipo == TipoDado::LONG);
	assert(valor1.tipo == TipoDado::LONG);
	
	int64_t num1, num2;
	memcpy(&num1,&valor1.dado,8);
	memcpy(&num2,&valor2.dado,8);
	
	num1 = num1 ^ num2;
	memcpy(&valor1.dado,&num1,8);
	
	toppilha->empilharOperando(valor1);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_iinc(){}
void ExecutionEngine::i_i2l(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor1 = toppilha->desempilhaOperando();
	assert(valor1.tipo == TipoDado::INT);
	
	Valor valor2;
	valor2.tipo = TipoDado::LONG;
	Valor padding;
	padding.tipo = TipoDado::PADDING;
	toppilha->empilharOperando(padding);
	
	int32_t num1;
	int64_t num2;
	
	memcpy(&num1,&valor1.dado,4);
	num2 = (int64_t) num1;
	memcpy(&valor2.dado,&num2,8);
	
	toppilha->empilharOperando(valor2);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_i2f(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor1 = toppilha->desempilhaOperando();
	assert(valor1.tipo == TipoDado::INT);
	
	Valor valor2;
	valor2.tipo = TipoDado::FLOAT;
	
	int32_t num1, num2;
	
	memcpy(&num1,&valor1.dado,4);
	num2 = (float) num1;
	memcpy(&valor2.dado,&num2,4);
	
	toppilha->empilharOperando(valor2);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_i2d(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor1 = toppilha->desempilhaOperando();
	assert(valor1.tipo == TipoDado::INT);
	
	Valor valor2;
	valor2.tipo = TipoDado::DOUBLE;
	Valor padding;
	padding.tipo = TipoDado::PADDING;
	toppilha->empilharOperando(padding);
	
	int32_t num1;
	int64_t num2;
	
	memcpy(&num1,&valor1.dado,4);
	num2 = (double) num1;
	memcpy(&valor2.dado,&num2,8);
	
	toppilha->empilharOperando(valor2);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_l2i(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor1 = toppilha->desempilhaOperando();
	toppilha->desempilhaOperando(); //padding
	assert(valor1.tipo == TipoDado::LONG);
	
	Valor valor2;
	valor2.tipo = TipoDado::INT;
	
	int64_t num1;
	int32_t num2;
	
	memcpy(&num1,&valor1.dado,8);
	num2 = (int32_t) num1;
	memcpy(&valor2.dado,&num2,4);
	
	toppilha->empilharOperando(valor2);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_l2f(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor1 = toppilha->desempilhaOperando();
	toppilha->desempilhaOperando(); //padding
	assert(valor1.tipo == TipoDado::LONG);
	
	Valor valor2;
	valor2.tipo = TipoDado::FLOAT;
	
	int64_t num1;
	int32_t num2;
	
	memcpy(&num1,&valor1.dado,8);
	num2 = (float) num1;
	memcpy(&valor2.dado,&num2,4);
	
	toppilha->empilharOperando(valor2);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_l2d(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor1 = toppilha->desempilhaOperando();
	assert(valor1.tipo == TipoDado::LONG);
	
	Valor valor2;
	valor2.tipo = TipoDado::DOUBLE;
	
	int64_t num1, num2;
	
	memcpy(&num1,&valor1.dado,8);
	num2 = (double) num1;
	memcpy(&valor2.dado,&num2,8);
	
	toppilha->empilharOperando(valor2);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_f2i(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor1 = toppilha->desempilhaOperando();
	assert(valor1.tipo == TipoDado::FLOAT);
	
	Valor valor2;
	valor2.tipo = TipoDado::INT;
	
	int32_t num1, num2;
	
	memcpy(&num1,&valor1.dado,4);
	num2 = (int32_t) num1;
	memcpy(&valor2.dado,&num2,4);
	
	toppilha->empilharOperando(valor2);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_f2l(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor1 = toppilha->desempilhaOperando();
	assert(valor1.tipo == TipoDado::FLOAT);
	
	Valor valor2;
	valor2.tipo = TipoDado::LONG;
	Valor padding;
	padding.tipo = TipoDado::PADDING;
	toppilha->empilharOperando(padding);
	
	int32_t num1;
	int64_t num2;
	
	memcpy(&num1,&valor1.dado,4);
	num2 = (int64_t) num1;
	memcpy(&valor2.dado,&num2,8);
	
	toppilha->empilharOperando(valor2);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_f2d(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor1 = toppilha->desempilhaOperando();
	assert(valor1.tipo == TipoDado::INT);
	
	Valor valor2;
	valor2.tipo = TipoDado::DOUBLE;
	Valor padding;
	padding.tipo = TipoDado::PADDING;
	toppilha->empilharOperando(padding);
	
	int32_t num1;
	int64_t num2;
	
	memcpy(&num1,&valor1.dado,4);
	num2 = (double) num1;
	memcpy(&valor2.dado,&num2,8);
	
	toppilha->empilharOperando(valor2);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_d2i(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor1 = toppilha->desempilhaOperando();
	toppilha->desempilhaOperando(); //padding
	assert(valor1.tipo == TipoDado::DOUBLE);
	
	Valor valor2;
	valor2.tipo = TipoDado::INT;
	
	int64_t num1;
	int32_t num2;
	
	memcpy(&num1,&valor1.dado,8);
	num2 = (int32_t) num1;
	memcpy(&valor2.dado,&num2,4);
	
	toppilha->empilharOperando(valor2);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_d2l(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor1 = toppilha->desempilhaOperando();
	assert(valor1.tipo == TipoDado::DOUBLE);
	
	Valor valor2;
	valor2.tipo = TipoDado::LONG;
	
	int64_t num1, num2;
	
	memcpy(&num1,&valor1.dado,8);
	num2 = (int64_t) num1;
	memcpy(&valor2.dado,&num2,8);
	
	toppilha->empilharOperando(valor2);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_d2f(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor1 = toppilha->desempilhaOperando();
	toppilha->desempilhaOperando(); //padding
	assert(valor1.tipo == TipoDado::DOUBLE);
	
	Valor valor2;
	valor2.tipo = TipoDado::FLOAT;
	
	int64_t num1;
	int32_t num2;
	
	memcpy(&num1,&valor1.dado,8);
	num2 = (float) num1;
	memcpy(&valor2.dado,&num2,4);
	
	toppilha->empilharOperando(valor2);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_i2b(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor1 = toppilha->desempilhaOperando();
	assert(valor1.tipo == TipoDado::INT);
	
	Valor valor2;
	valor2.tipo = TipoDado::BYTE;
	
	int32_t num1=0; 
	int8_t num2=0;
	
	memcpy(&num1,&valor1.dado,4);
	num2 = (int8_t) num1;
	memcpy(&valor2.dado,&num2,1);
	
	toppilha->empilharOperando(valor2);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_i2c(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor1 = toppilha->desempilhaOperando();
	assert(valor1.tipo == TipoDado::INT);
	
	Valor valor2;
	valor2.tipo = TipoDado::CHAR;
	
	int32_t num1=0; 
	int8_t num2=0;
	
	memcpy(&num1,&valor1.dado,4);
	num2 = (int8_t) num1;
	memcpy(&valor2.dado,&num2,1);
	
	toppilha->empilharOperando(valor2);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_i2s(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor1 = toppilha->desempilhaOperando();
	assert(valor1.tipo == TipoDado::INT);
	
	Valor valor2;
	valor2.tipo = TipoDado::SHORT;
	
	int32_t num1=0; 
	int16_t num2=0;
	
	memcpy(&num1,&valor1.dado,4);
	num2 = (int8_t) num1;
	memcpy(&valor2.dado,&num2,2);
	
	toppilha->empilharOperando(valor2);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_lcmp(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	toppilha->desempilhaOperando(); //padding
	Valor valor1 = toppilha->desempilhaOperando();
	toppilha->desempilhaOperando(); //padding
	
	assert(valor2.tipo == TipoDado::LONG);
	assert(valor1.tipo == TipoDado::LONG);
	
	int64_t num1, num2;
	int32_t num3;
	memcpy(&num1,&valor1.dado,8);
	memcpy(&num2,&valor2.dado,8);
	
	Valor resultado;
	resultado.tipo = TipoDado::INT;
	
	if (num1 > num2) {
		num3 = 1;
	} else if (num1 == num2) {
		num3 = 0;
	} else {
		num3 = -1;
	}
	memcpy(&resultado.dado,&num3,4);
	
	toppilha->empilharOperando(resultado);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_fcmpl(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	Valor valor1 = toppilha->desempilhaOperando();
	
	assert(valor2.tipo == TipoDado::FLOAT);
	assert(valor1.tipo == TipoDado::FLOAT);
	
	int64_t num1, num2;
	int32_t num3;
	memcpy(&num1,&valor1.dado,4);
	memcpy(&num2,&valor2.dado,4);
	
	Valor resultado;
	resultado.tipo = TipoDado::INT;
	
	if (isnan(num1) || isnan(num2)) {
		num3 = -1;
	} else if (num1 > num2) {
		num3 = 1;
	} else if (num1 == num2) {
		num3 = 0;
	} else {
		num3 = -1;
	}
	memcpy(&resultado.dado,&num3,4);
	
	toppilha->empilharOperando(resultado);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_fcmpg(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	Valor valor1 = toppilha->desempilhaOperando();
	
	assert(valor2.tipo == TipoDado::FLOAT);
	assert(valor1.tipo == TipoDado::FLOAT);
	
	int64_t num1, num2;
	int32_t num3;
	memcpy(&num1,&valor1.dado,4);
	memcpy(&num2,&valor2.dado,4);
	
	Valor resultado;
	resultado.tipo = TipoDado::INT;
	
	if (isnan(num1) || isnan(num2)) {
		num3 = 1;
	} else if (num1 > num2) {
		num3 = 1;
	} else if (num1 == num2) {
		num3 = 0;
	} else {
		num3 = -1;
	}
	memcpy(&resultado.dado,&num3,4);
	
	toppilha->empilharOperando(resultado);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_dcmpl(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	toppilha->desempilhaOperando(); //padding
	Valor valor1 = toppilha->desempilhaOperando();
	toppilha->desempilhaOperando(); //padding
	
	assert(valor2.tipo == TipoDado::DOUBLE);
	assert(valor1.tipo == TipoDado::DOUBLE);
	
	int64_t num1, num2;
	int32_t num3;
	memcpy(&num1,&valor1.dado,8);
	memcpy(&num2,&valor2.dado,8);
	
	Valor resultado;
	resultado.tipo = TipoDado::INT;
	
	if (isnan(num1) || isnan(num2)) {
		num3 = -1;
	} else if (num1 > num2) {
		num3 = 1;
	} else if (num1 == num2) {
		num3 = 0;
	} else {
		num3 = -1;
	}
	memcpy(&resultado.dado,&num3,4);
	
	toppilha->empilharOperando(resultado);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_dcmpg(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	toppilha->desempilhaOperando(); //padding
	Valor valor1 = toppilha->desempilhaOperando();
	toppilha->desempilhaOperando(); //padding
	
	assert(valor2.tipo == TipoDado::DOUBLE);
	assert(valor1.tipo == TipoDado::DOUBLE);
	
	int64_t num1, num2;
	int32_t num3;
	memcpy(&num1,&valor1.dado,8);
	memcpy(&num2,&valor2.dado,8);
	
	Valor resultado;
	resultado.tipo = TipoDado::INT;
	
	if (isnan(num1) || isnan(num2)) {
		num3 = 1;
	} else if (num1 > num2) {
		num3 = 1;
	} else if (num1 == num2) {
		num3 = 0;
	} else {
		num3 = -1;
	}
	memcpy(&resultado.dado,&num3,4);
	
	toppilha->empilharOperando(resultado);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_ifeq(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor = toppilha->desempilhaOperando();
	assert(valor.tipo == TipoDado::INT);
	
	int32_t num;
	memcpy(&num,&valor.dado,4);
	
	if (num == 0) {
		uint8_t *code = toppilha->getCode();
		uint8_t byte1 = code[1];
		uint8_t byte2 = code[2];
		uint16_t offsetPC = (byte1 << 8) | byte2;
		runtimeDataArea->topoPilha()->incrementaPC(offsetPC);
	} else {
		runtimeDataArea->topoPilha()->incrementaPC(3);
	}
}
void ExecutionEngine::i_ifne(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor = toppilha->desempilhaOperando();
	assert(valor.tipo == TipoDado::INT);
	
	int32_t num;
	memcpy(&num,&valor.dado,4);
	
	if (num != 0) {
		uint8_t *code = toppilha->getCode();
		uint8_t byte1 = code[1];
		uint8_t byte2 = code[2];
		uint16_t offsetPC = (byte1 << 8) | byte2;
		runtimeDataArea->topoPilha()->incrementaPC(offsetPC);
	} else {
		runtimeDataArea->topoPilha()->incrementaPC(3);
	}
}
void ExecutionEngine::i_iflt(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor = toppilha->desempilhaOperando();
	assert(valor.tipo == TipoDado::INT);
	
	int32_t num;
	memcpy(&num,&valor.dado,4);
	
	if (num < 0) {
		uint8_t *code = toppilha->getCode();
		uint8_t byte1 = code[1];
		uint8_t byte2 = code[2];
		uint16_t offsetPC = (byte1 << 8) | byte2;
		runtimeDataArea->topoPilha()->incrementaPC(offsetPC);
	} else {
		runtimeDataArea->topoPilha()->incrementaPC(3);
	}
}
void ExecutionEngine::i_ifge(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor = toppilha->desempilhaOperando();
	assert(valor.tipo == TipoDado::INT);
	
	int32_t num;
	memcpy(&num,&valor.dado,4);
	
	if (num >= 0) {
		uint8_t *code = toppilha->getCode();
		uint8_t byte1 = code[1];
		uint8_t byte2 = code[2];
		uint16_t offsetPC = (byte1 << 8) | byte2;
		runtimeDataArea->topoPilha()->incrementaPC(offsetPC);
	} else {
		runtimeDataArea->topoPilha()->incrementaPC(3);
	}
}
void ExecutionEngine::i_ifgt(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor = toppilha->desempilhaOperando();
	assert(valor.tipo == TipoDado::INT);
	
	int32_t num;
	memcpy(&num,&valor.dado,4);
	
	if (num > 0) {
		uint8_t *code = toppilha->getCode();
		uint8_t byte1 = code[1];
		uint8_t byte2 = code[2];
		uint16_t offsetPC = (byte1 << 8) | byte2;
		runtimeDataArea->topoPilha()->incrementaPC(offsetPC);
	} else {
		runtimeDataArea->topoPilha()->incrementaPC(3);
	}
}
void ExecutionEngine::i_ifle(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor = toppilha->desempilhaOperando();
	assert(valor.tipo == TipoDado::INT);
	
	int32_t num;
	memcpy(&num,&valor.dado,4);
	
	if (num <= 0) {
		uint8_t *code = toppilha->getCode();
		uint8_t byte1 = code[1];
		uint8_t byte2 = code[2];
		uint16_t offsetPC = (byte1 << 8) | byte2;
		runtimeDataArea->topoPilha()->incrementaPC(offsetPC);
	} else {
		runtimeDataArea->topoPilha()->incrementaPC(3);
	}
}
void ExecutionEngine::i_if_icmpeq(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	Valor valor1 = toppilha->desempilhaOperando();
	assert(valor1.tipo == TipoDado::INT);
	assert(valor2.tipo == TipoDado::INT);
	
	int32_t num1, num2;
	memcpy(&num1,&valor1.dado,4);
	memcpy(&num2,&valor2.dado,4);
	
	if (num1 == num2) {
		uint8_t *code = toppilha->getCode();
		uint8_t byte1 = code[1];
		uint8_t byte2 = code[2];
		uint16_t offsetPC = (byte1 << 8) | byte2;
		runtimeDataArea->topoPilha()->incrementaPC(offsetPC);
	} else {
		runtimeDataArea->topoPilha()->incrementaPC(3);
	}
}
void ExecutionEngine::i_if_icmpne(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	Valor valor1 = toppilha->desempilhaOperando();
	assert(valor1.tipo == TipoDado::INT);
	assert(valor2.tipo == TipoDado::INT);
	
	int32_t num1, num2;
	memcpy(&num1,&valor1.dado,4);
	memcpy(&num2,&valor2.dado,4);
	
	if (num1 != num2) {
		uint8_t *code = toppilha->getCode();
		uint8_t byte1 = code[1];
		uint8_t byte2 = code[2];
		uint16_t offsetPC = (byte1 << 8) | byte2;
		runtimeDataArea->topoPilha()->incrementaPC(offsetPC);
	} else {
		runtimeDataArea->topoPilha()->incrementaPC(3);
	}
}
void ExecutionEngine::i_if_icmplt(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	Valor valor1 = toppilha->desempilhaOperando();
	assert(valor1.tipo == TipoDado::INT);
	assert(valor2.tipo == TipoDado::INT);
	
	int32_t num1, num2;
	memcpy(&num1,&valor1.dado,4);
	memcpy(&num2,&valor2.dado,4);
	
	if (num1 < num2) {
		uint8_t *code = toppilha->getCode();
		uint8_t byte1 = code[1];
		uint8_t byte2 = code[2];
		uint16_t offsetPC = (byte1 << 8) | byte2;
		runtimeDataArea->topoPilha()->incrementaPC(offsetPC);
	} else {
		runtimeDataArea->topoPilha()->incrementaPC(3);
	}
}
void ExecutionEngine::i_if_icmpge(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	Valor valor1 = toppilha->desempilhaOperando();
	assert(valor1.tipo == TipoDado::INT);
	assert(valor2.tipo == TipoDado::INT);
	
	int32_t num1, num2;
	memcpy(&num1,&valor1.dado,4);
	memcpy(&num2,&valor2.dado,4);
	
	if (num1 >= num2) {
		uint8_t *code = toppilha->getCode();
		uint8_t byte1 = code[1];
		uint8_t byte2 = code[2];
		uint16_t offsetPC = (byte1 << 8) | byte2;
		runtimeDataArea->topoPilha()->incrementaPC(offsetPC);
	} else {
		runtimeDataArea->topoPilha()->incrementaPC(3);
	}
}
void ExecutionEngine::i_if_icmpgt(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	Valor valor1 = toppilha->desempilhaOperando();
	assert(valor1.tipo == TipoDado::INT);
	assert(valor2.tipo == TipoDado::INT);
	
	int32_t num1, num2;
	memcpy(&num1,&valor1.dado,4);
	memcpy(&num2,&valor2.dado,4);
	
	if (num1 > num2) {
		uint8_t *code = toppilha->getCode();
		uint8_t byte1 = code[1];
		uint8_t byte2 = code[2];
		uint16_t offsetPC = (byte1 << 8) | byte2;
		runtimeDataArea->topoPilha()->incrementaPC(offsetPC);
	} else {
		runtimeDataArea->topoPilha()->incrementaPC(3);
	}
}
void ExecutionEngine::i_if_icmple(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	Valor valor1 = toppilha->desempilhaOperando();
	assert(valor1.tipo == TipoDado::INT);
	assert(valor2.tipo == TipoDado::INT);
	
	int32_t num1, num2;
	memcpy(&num1,&valor1.dado,4);
	memcpy(&num2,&valor2.dado,4);
	
	if (num1 <= num2) {
		uint8_t *code = toppilha->getCode();
		uint8_t byte1 = code[1];
		uint8_t byte2 = code[2];
		uint16_t offsetPC = (byte1 << 8) | byte2;
		runtimeDataArea->topoPilha()->incrementaPC(offsetPC);
	} else {
		runtimeDataArea->topoPilha()->incrementaPC(3);
	}
}
void ExecutionEngine::i_if_acmpeq(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	Valor valor1 = toppilha->desempilhaOperando();
	assert(valor1.tipo == TipoDado::REFERENCE);
	assert(valor2.tipo == TipoDado::REFERENCE);
	
	int64_t num1, num2;
	memcpy(&num1,&valor1.dado,sizeof(void*));
	memcpy(&num2,&valor2.dado,sizeof(void*));
	
	if (num1 == num2) {
		uint8_t *code = toppilha->getCode();
		uint8_t byte1 = code[1];
		uint8_t byte2 = code[2];
		uint16_t offsetPC = (byte1 << 8) | byte2;
		runtimeDataArea->topoPilha()->incrementaPC(offsetPC);
	} else {
		runtimeDataArea->topoPilha()->incrementaPC(3);
	}
}
void ExecutionEngine::i_if_acmpne(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	Valor valor1 = toppilha->desempilhaOperando();
	assert(valor1.tipo == TipoDado::REFERENCE);
	assert(valor2.tipo == TipoDado::REFERENCE);
	
	int64_t num1, num2;
	memcpy(&num1,&valor1.dado,sizeof(void*));
	memcpy(&num2,&valor2.dado,sizeof(void*));
	
	if (num1 != num2) {
		uint8_t *code = toppilha->getCode();
		uint8_t byte1 = code[1];
		uint8_t byte2 = code[2];
		uint16_t offsetPC = (byte1 << 8) | byte2;
		runtimeDataArea->topoPilha()->incrementaPC(offsetPC);
	} else {
		runtimeDataArea->topoPilha()->incrementaPC(3);
	}
}
void ExecutionEngine::i_goto(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	uint8_t *code = toppilha->getCode();
	uint8_t byte1 = code[1];
	uint8_t byte2 = code[2];
	uint16_t offsetPC = (byte1 << 8) | byte2;
	runtimeDataArea->topoPilha()->incrementaPC(offsetPC);
}
void ExecutionEngine::i_jsr(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	uint8_t *code = toppilha->getCode();
	uint8_t byte1 = code[1];
	uint8_t byte2 = code[2];
	uint16_t offsetPC = (byte1 << 8) | byte2;
	
	Valor enderecoRetorno;
	enderecoRetorno.tipo = TipoDado::RETURN_ADDR;
	int64_t num;
	num = runtimeDataArea->topoPilha()->getPC() + 3;
	memcpy(&enderecoRetorno.dado,&num,sizeof(void*));
	
	toppilha->empilharOperando(enderecoRetorno);
	runtimeDataArea->topoPilha()->incrementaPC(offsetPC);
}
void ExecutionEngine::i_ret(){}
void ExecutionEngine::i_tableswitch(){}
void ExecutionEngine::i_lookupswitch(){}
void ExecutionEngine::i_ireturn(){}
void ExecutionEngine::i_lreturn(){}
void ExecutionEngine::i_freturn(){}
void ExecutionEngine::i_dreturn(){}
void ExecutionEngine::i_areturn(){}
void ExecutionEngine::i_return(){
	//usa no mainvazia
	runtimeDataArea->desempilharFrame();

}
void ExecutionEngine::i_getstatic() {
	//usa no helloworld
#ifdef DEBUG
	cout<< "ExecutionEngine::i_getstatic" << endl;
#endif
	Frame *toppilha = runtimeDataArea->topoPilha();
#ifdef DEBUG
	cout<< "ExecutionEngine::i_getstatic1" << endl;
#endif
	vector<cp_info*> constantPool;
	JavaClass *classe= (toppilha->getObjeto()== NULL )? toppilha->ObterJavaClass(): ((ObjetoInstancia*)toppilha->getObjeto())->ObterJavaClass();
	constantPool = classe->getConstantPool();
#ifdef DEBUG
	cout<< "ExecutionEngine::i_getstatic2" << endl;
#endif
	uint8_t *code = toppilha->getCode();
#ifdef DEBUG
	cout<< "ExecutionEngine::i_getstatic3" << endl;
#endif

	//argumentos da instrucao
	uint8_t byte1 = code[1];
	uint8_t byte2 = code[2];
	
	uint16_t campoIndex = (byte1 << 8) | byte2;
#ifdef DEBUG
	cout<< "ExecutionEngine::i_getstatic4" << endl;
#endif


	CONSTANT_Fieldref_info *fieldRef = (CONSTANT_Fieldref_info*) constantPool[campoIndex-1];
#ifdef DEBUG
	cout<< "ExecutionEngine::i_getstatic5" << endl;
#endif
	string className = classe->getUTF8(fieldRef->GetClassIndex());
#ifdef DEBUG
	cout<< "ExecutionEngine::i_getstatic6" << endl;
#endif
	CONSTANT_NameAndType_info *campoNameAndtipoCP = (CONSTANT_NameAndType_info *)constantPool[fieldRef->GetNameAndTypeIndex()-1];
#ifdef DEBUG
	cout<< "ExecutionEngine::i_getstatic7" << endl;
#endif
	string campoName = classe->getUTF8(campoNameAndtipoCP->GetNameIndex());
	string campoDescriptor = classe->getUTF8(campoNameAndtipoCP->GetDescriptorIndex());
#ifdef DEBUG
	cout<< "ExecutionEngine::i_getstatic8" << endl;
#endif
	if (className == "java/lang/System" && campoDescriptor == "Ljava/io/PrintStream;" ) {
		runtimeDataArea->topoPilha()->incrementaPC(3);
		return;
	}	


	JavaClass *classRuntime = runtimeDataArea->CarregarClasse(className);

	while (classRuntime != NULL) {
		if (classRuntime->FieldExiste(campoName) == false) {
			if (classRuntime->ObterSuperClasse()) {
				classRuntime = NULL;
			} else {

				string superClassName = classRuntime->getUTF8(classRuntime->ObterSuperClasse());
				classRuntime = runtimeDataArea->CarregarClasse(superClassName);
	  		  
	  
			}
		} else {
			break;
		}
	}// fim while classRuntime   
	
	if (classRuntime == NULL) {
		cerr << "NoSuchFieldError" << endl;
		exit(1);
	}
	if (runtimeDataArea->topoPilha() != toppilha)
   		return;

	Valor valorStatico = classRuntime->getValorDoField(campoName);
	
	switch (valorStatico.tipo) {
		case TipoDado::BOOLEAN:
			valorStatico.tipo = TipoDado::INT;
			break;
		case TipoDado::BYTE:
			valorStatico.tipo = TipoDado::INT;
			break;
		case TipoDado::SHORT:
			valorStatico.tipo = TipoDado::INT;
			break;
		case TipoDado::INT:
			valorStatico.tipo = TipoDado::INT;
			break;
		default:
			break;
	}
	if (valorStatico.tipo == TipoDado::DOUBLE || valorStatico.tipo == TipoDado::LONG) {
		Valor padding;
		padding.tipo = TipoDado::PADDING;
		toppilha->empilharOperando(padding);
	}

	toppilha->empilharOperando(valorStatico);

	runtimeDataArea->topoPilha()->incrementaPC(3);

}

void ExecutionEngine::i_putstatic(){}
void ExecutionEngine::i_getfield(){}
void ExecutionEngine::i_putfield()
{
	/*
	Frame *toppilha = runtimeDataArea->topoPilha();
	stack<Valor> operandStackBackup = toppilha->retornaPilhaOperandos();
	
	vector<cp_info*> constantPool = ((ObjetoInstancia*)toppilha->getObjeto())->ObterJavaClass()->getConstantPool();
	uint8_t *code = toppilha->getCode();

	//argumentos da instrucao
	uint8_t byte1 = code[1];
	uint8_t byte2 = code[2];
	uint16_t methodIndex = (byte1 << 8) | byte2;

	//...	

	runtimeDataArea->topoPilha()->desempilhaOperando();
	*/

}//fim metodo

void ExecutionEngine::i_invokevirtual()
{
	Frame *topoDaPilha= runtimeDataArea->topoPilha();
	stack<Valor> pilhaDeOperandosDeReserva= topoDaPilha->retornaPilhaOperandos();
	uint8_t *instrucoes=topoDaPilha->getCode();
	uint16_t indiceMetodo;
	memcpy(&indiceMetodo, instrucoes, 2);
	JavaClass *javaClass= topoDaPilha->ObterJavaClass();
	if(javaClass->getConstantPool().at(indiceMetodo-1)->GetTag() != CONSTANT_Methodref)
	{
		throw new Erro("Esperado encontrar um CONSTANT_Methodref", "ExecutionEngine", "i_invokevirtual");
	}
	CONSTANT_Methodref_info *metodo= (CONSTANT_Methodref_info *)javaClass->getConstantPool().at(indiceMetodo-1);
	string nomeDaClasse= javaClass->getUTF8(metodo->GetClassIndex());
	if(javaClass->getConstantPool().at(metodo->GetNameAndTypeIndex()-1)->GetTag() != CONSTANT_NameAndType)
	{
		throw new Erro("Esperado encontrar um CONSTANT_NameAndType", "ExecutionEngine", "i_invokevirtual");
	}
	CONSTANT_NameAndType_info *assinaturaDoMetodo= (CONSTANT_NameAndType_info*) javaClass->getConstantPool().at(metodo->GetNameAndTypeIndex()-1);
	string nomeDoMetodo= javaClass->getUTF8(assinaturaDoMetodo->GetNameIndex());
	string descritorDoMetodo= javaClass->getUTF8(assinaturaDoMetodo->GetDescriptorIndex());
	
	if(nomeDaClasse.find("java/") != string::npos)
	{//Provavelmente estamos tratando de um print
		if(nomeDaClasse== "java/io/PrintStream" && (nomeDoMetodo == "print" || nomeDoMetodo == "println"))
		{
			if(descritorDoMetodo != "()V")
			{
				Valor valorQueSeraImpresso= topoDaPilha->desempilhaOperando();
				switch(valorQueSeraImpresso.tipo)
				{
					case(BOOLEAN):
					{
						printf("%s", valorQueSeraImpresso.dado != 0 ? "true" : "true");
						break;
					}
					case(BYTE):
					{
						int8_t aux;
						memcpy(&aux, &(valorQueSeraImpresso.dado), 1);
						printf("%c", aux);
						break;
					}
					case(SHORT):
					{
						int16_t aux;
						memcpy(&aux, &(valorQueSeraImpresso.dado), 2);
						printf("%hd", aux);
						break;
					}
					case(INT):
					{
						int32_t aux;
						memcpy(&aux, &(valorQueSeraImpresso.dado), 4);
						printf("%d", aux);
						break;
					}
					case(DOUBLE):
					{
						topoDaPilha->desempilhaOperando();//desempilhando a entrada de preenchimento
						double aux;
						memcpy(&aux, &(valorQueSeraImpresso.dado), 8);
						printf("%f", aux);
						break;
					}
					case(FLOAT):
					{
						float aux;
						memcpy(&aux, &(valorQueSeraImpresso.dado), 4);
						printf("%f", aux);
						break;
					}
					case(LONG):
					{
						topoDaPilha->desempilhaOperando();//desempilhando a entrada de preenchimento
						int64_t aux;
						memcpy(&aux, &(valorQueSeraImpresso.dado), 8);
#ifdef ENVIRONMENT32
						printf("%lld", aux);
#else
						printf("%ld", aux);
#endif
						break;
					}
					case(REFERENCE):
					{
						if(((Objeto*)valorQueSeraImpresso.dado)->ObterTipoObjeto() != STRING)
						{
							throw new Erro("String esperado quando deve imprimir referencias", "ExecutionEngine", "invokevirtual");
						}
						ObjetoString *stringPtr;
						memcpy(&stringPtr, &(valorQueSeraImpresso.dado), sizeof(ObjetoString *));
						printf("%s", stringPtr->ObterString().c_str());
						break;
					}
					default:
					{
						throw new Erro("Tentou-se imprimir um tipo de dado invalido");
					}
				}
			}
			if(nomeDoMetodo == "println")
			{
				cout << endl;
			}
			else if(nomeDaClasse== "java/lang/String")
			{
				if(nomeDoMetodo == "lenght")
				{
					Valor string1= topoDaPilha->desempilhaOperando();
					if(string1.tipo != REFERENCE)
					{
						throw new Erro("Esperado valor do tipo referencia para pegar comprimento da string", "ExecutionEngine", "i_invokevirtual");
					}
					if(((Objeto*)string1.dado)->ObterTipoObjeto() == STRING)
					{
						throw new Erro("Esperado objeto do tipo string para calcular", "ExecutionEngine", "i_invokevirtual");
					}
					ObjetoString *stringObj= (ObjetoString *)string1.dado;
					Valor tamanhoDaString;
					tamanhoDaString.tipo= INT;
					tamanhoDaString.dado=stringObj->ObterString().size();
					topoDaPilha->empilharOperando(tamanhoDaString);
				}
				else if(nomeDoMetodo == "equals")
				{
					Valor string1 = topoDaPilha->desempilhaOperando();
					if(string1.tipo != REFERENCE)
					{
						throw new Erro("Esperado valor do tipo referencia para analisar igualdade de strings(erro na primeira string)", "ExecutionEngine", "i_invokevirtual");
					}
					if(((Objeto*)string1.dado)->ObterTipoObjeto() == STRING)
					{
						throw new Erro("Esperado objeto do tipo string  para analisar igualdade de strings(erro na primeira string)", "ExecutionEngine", "i_invokevirtual");
					}
					Valor string2 = topoDaPilha->desempilhaOperando();
					if(string2.tipo != REFERENCE)
					{
						throw new Erro("Esperado valor do tipo referencia para analisar igualdade de strings(erro na  string)", "ExecutionEngine", "i_invokevirtual");
					}
					if(((Objeto*)string2.dado)->ObterTipoObjeto() == STRING)
					{
						throw new Erro("Esperado objeto do tipo string  para analisar igualdade de strings(erro na segunda string string)", "ExecutionEngine", "i_invokevirtual");
					}
					//se chegou ate aqui é pq os operandos são válidos
					string stringReal1= ((ObjetoString*)string1.dado)->ObterString();
					string stringReal2= ((ObjetoString*)string2.dado)->ObterString();
					Valor resultado;
					resultado.tipo=BOOLEAN;
					if(stringReal1 == stringReal2)
					{
						resultado.dado= 0xFFFFFFFFFFFFFFFF;
					}
					else
					{
						resultado.dado= 0;
					}
					topoDaPilha->empilharOperando(resultado);
				}
			}
		}
		else
		{
			throw new Erro("Metodo que esta tentando invocar um metodo desconhecido", "ExecutionEngine", "invokevirtual");
		}
	}
	else
	{
		uint16_t numeroDeargumentos;
		for(int cont =1; descritorDoMetodo[cont] != ')'; cont++)//pula o abre parenteses
		{
			char indicadorDeTipo= descritorDoMetodo[cont];
			if(indicadorDeTipo == 'J' || indicadorDeTipo == 'D')
			{
				numeroDeargumentos+= 2;
			}
			else if(indicadorDeTipo == 'L')
			{
				numeroDeargumentos++;
				while(descritorDoMetodo[++cont] != ';');
			}
			else if(indicadorDeTipo == '[')
			{
				if(descritorDoMetodo[++cont] == 'L')
				{
					while(descritorDoMetodo[++cont] != ';');
				}
			}
			else
			{
				numeroDeargumentos++;
			}
		}
		vector<Valor> argumentos;
		Valor temp;
		for(int cont =0; cont < numeroDeargumentos; cont++)
		{
			temp= topoDaPilha->desempilhaOperando();
			if(temp.tipo == PADDING)
			{
				argumentos.insert(argumentos.begin()+1, temp);
			}
			else
			{
				argumentos.insert(argumentos.begin(), temp);
			}
		}
		Valor valorQueArmazenaObjeto= topoDaPilha->desempilhaOperando();
		if(valorQueArmazenaObjeto.tipo != REFERENCE)
		{
			throw new Erro("Esperava um valor do tipo referencia", "EnxecutionEngine", "InvokeVirtual");
		}
		argumentos.insert(argumentos.begin(), valorQueArmazenaObjeto);
		Objeto *obj= (Objeto*) valorQueArmazenaObjeto.dado;
		if(obj->ObterTipoObjeto() != INSTANCIA)
		{
			throw new Erro("Esperava-se um objeto do tipo instancia", "ExecutionEngine", "Invokevirtual");
		}
		ObjetoInstancia *instancia= (ObjetoInstancia*) valorQueArmazenaObjeto.dado;
		runtimeDataArea->CarregarClasse(nomeDaClasse);
		Frame *novoFrame= new Frame(instancia, javaClass, nomeDoMetodo, descritorDoMetodo, argumentos, runtimeDataArea);
		if(runtimeDataArea->topoPilha() != topoDaPilha)
		{
			topoDaPilha->setaPilhaOperandos(pilhaDeOperandosDeReserva);
			delete novoFrame;
			return;
		}
		runtimeDataArea->pilhaJVM.push(*novoFrame);
	}
	topoDaPilha->incrementaPC(3);
}
void ExecutionEngine::i_invokespecial(){ 
	//usa no mainvazia
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	stack<Valor> operandStackBackup = toppilha->retornaPilhaOperandos();
	//cp_info *constantPool = *(topFrame->getConstantPool());
	vector<cp_info*> constantPool = ((ObjetoInstancia*)toppilha->getObjeto())->ObterJavaClass()->getConstantPool();
	
	uint8_t *code = toppilha->getCode();
	
	//argumentos da instrucao
	uint8_t byte1 = code[1];
	uint8_t byte2 = code[2];
	uint16_t methodIndex = (byte1 << 8) | byte2;
	

	CONSTANT_Methodref_info *methodInfo = (CONSTANT_Methodref_info*) constantPool[methodIndex-1]; //em 1 linha
	//assert(validar referencia a um metodo)
	string className = ((ObjetoInstancia*)toppilha->getObjeto())->ObterJavaClass()->getUTF8(methodInfo->GetClassIndex());

	CONSTANT_NameAndType_info *nameAndTypeCP = (CONSTANT_NameAndType_info *)constantPool[methodInfo->GetNameAndTypeIndex()-1];
	string methodName = ((ObjetoInstancia*)toppilha->getObjeto())->ObterJavaClass()->getUTF8(nameAndTypeCP->GetNameIndex());

	string methodDescriptor =  ((ObjetoInstancia*)toppilha->getObjeto())->ObterJavaClass()->getUTF8(nameAndTypeCP->GetDescriptorIndex());

	// casos especiais
	if ((className == "java/lang/Object" || className == "java/lang/String") && methodName == "<init>") {
		if (className == "java/lang/String") {
			toppilha->desempilhaOperando();
		}
		
		runtimeDataArea->topoPilha()->incrementaPC(3);
		return;
	}
	// fim dos casos especiais
	
	if (className.find("java/") != string::npos) {
		cerr << "Tentando invocar metodo especial invalido: " << methodName << endl;
		exit(1);
	} else {
		uint16_t nargs = 0; // numero de argumentos contidos na pilha de operandos
		uint16_t i = 1; // pulando o primeiro '('
		while (methodDescriptor[i] != ')') {
			char baseType = methodDescriptor[i];
			if (baseType == 'D' || baseType == 'J') {
				nargs += 2;
			} else if (baseType == 'L') {
				nargs++;
				while (methodDescriptor[++i] != ';');
			} else if (baseType == '[') {
				nargs++;
				while (methodDescriptor[++i] == '[');
				if (methodDescriptor[i] == 'L') while (methodDescriptor[++i] != ';');
			} else {
				nargs++;
			}
			i++;
		}

		vector<Valor> args;
		for (int i = 0; i < nargs; i++) {
			Valor valor = toppilha->desempilhaOperando();
			if (valor.tipo == TipoDado::PADDING) {
				args.insert(args.begin() + 1, valor); // adicionando o padding após o valor double/long.
			} else {
				args.insert(args.begin(), valor);
			}
		}

		Valor objectValor = toppilha->desempilhaOperando();
		assert(objectValor.tipo == TipoDado::REFERENCE); // necessita ser uma referência para objeto
		args.insert(args.begin(), objectValor);

		Objeto *objeto = (Objeto*)objectValor.dado;

		//assert(object->objectType() == ObjectType::CLASS_INSTANCE); // objeto precisa ser uma instância
		ObjetoInstancia *instance = (ObjetoInstancia *) objeto;

		JavaClass *classRuntime = runtimeDataArea->CarregarClasse(className);

		Frame *newFrame = new Frame(instance,classRuntime, methodName, methodDescriptor,args,runtimeDataArea);

		if (runtimeDataArea->topoPilha() != toppilha) {
			toppilha->setaPilhaOperandos(operandStackBackup);
			delete newFrame;
			return;
		}
		newFrame = runtimeDataArea->topoPilha();
	}




	runtimeDataArea->topoPilha()->incrementaPC(3);	  

}
void ExecutionEngine::i_invokestatic(){}
void ExecutionEngine::i_invokeinterface(){}
void ExecutionEngine::i_new(){}
void ExecutionEngine::i_newarray(){}
void ExecutionEngine::i_anewarray(){}

void ExecutionEngine::i_arraylength(){

	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor arrayref = toppilha->desempilhaOperando();
	assert(arrayref.tipo == TipoDado::REFERENCE);

	if ((Objeto*)arrayref.dado == NULL) {
		cerr << "NullPointerException" << endl;
		exit(1);
	} 
	
	Valor length;
	length.tipo = TipoDado::INT;
	length.dado = ((ObjetoArray *) arrayref.dado)->ObterTamanho();
	toppilha->empilharOperando(length);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_athrow(){
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_checkcast(){}

void ExecutionEngine::i_instanceof(){

	Frame *topo = runtimeDataArea->topoPilha();

	uint8_t *code = topo->getCode();
	uint8_t byte1 = code[1];
	uint8_t byte2 = code[2];

	uint16_t cpIndex = (byte1 << 8) | byte2;
	vector<cp_info*> constantPool = ((ObjetoInstancia*)(topo->getObjeto()))->ObterJavaClass()->getConstantPool();
	cp_info *cpElement = constantPool[cpIndex-1];

	assert(cpElement->GetTag() == CONSTANT_Class);

	Valor objectrefValue = topo->desempilhaOperando();
	assert(objectrefValue.tipo == TipoDado::REFERENCE);
 	
	string className = ((ObjetoInstancia*)topo->getObjeto())->ObterJavaClass()->getUTF8(cpIndex);

	Valor resultValor;
	resultValor.tipo = TipoDado::INT;

	assert(cpElement->GetTag() == CONSTANT_Class);
   
	if ((Objeto*)objectrefValue.dado == NULL) {
		resultValor.dado = 0;
	}

	else {
		Objeto *obj = (Objeto*)objectrefValue.dado;

		if (obj->ObterTipoObjeto() == TipoObjeto::INSTANCIA) {
			ObjetoInstancia *classInstance = (ObjetoInstancia *) obj;
			JavaClass *classRuntime = classInstance->ObterJavaClass();

			bool found = false;
			while (!found) {
					JavaClass *auxJavaClass = classRuntime;
					string currClassName = classRuntime->NomeDaClasse();

				if (currClassName == className) {
					found = true;
				} 
								else {
					if (auxJavaClass->ObterSuperClasse() == 0) {
						break;
					} else {
						string superClassName = classRuntime->NomeDaClasse();;
						classRuntime = runtimeDataArea->CarregarClasse(superClassName);
					}
				}
			}

			resultValor.dado = found ? 1 : 0;
		} 
				else if (obj->ObterTipoObjeto() == TipoObjeto::STRING) {
			resultValor.dado = (className == "java/lang/String" || className == "java/lang/Object") ? 1 : 0;
		} 
				else {
			if (className == "java/lang/Object") {
				resultValor.dado = 1;
			} 
		else {
			resultValor.dado = 0;

			}
		}
	}

	topo->empilharOperando(resultValor);

	topo->incrementaPC(1);

}

void ExecutionEngine::i_monitorenter(){

	Frame *topo = runtimeDataArea->topoPilha();
	topo->incrementaPC(1);

}
void ExecutionEngine::i_monitorexit(){

	Frame *topo = runtimeDataArea->topoPilha();
	topo->incrementaPC(1);

}
void ExecutionEngine::i_wide(){

	Frame *topo = runtimeDataArea->topoPilha();
	isWide = true;
	topo->incrementaPC(1);

}

void ExecutionEngine::i_multianewarray(){
/*
	cout<<"Consertar ExecutionEngine::i_multianewarray" << endl;
	Frame *topo = runtimeDataArea->topoPilha();
	vector<cp_info*> constantPool = ((ObjetoInstancia*)topo->getObjeto())->ObterJavaClass()->getConstantPool();

	uint8_t *code = topo->getCode();
	uint8_t byte1 = code[1];
	uint8_t byte2 = code[2];
	uint8_t dimensoes = code[3];
	assert(dimensoes >= 1);

	uint16_t classIndex = (byte1 << 8) | byte2;

	CONSTANT_Class_info *classInfo = (CONSTANT_Class_info*)constantPool[classIndex-1];
	assert(classInfo->GetTag() == CONSTANT_Class);

	string className = ((ObjetoInstancia*)topo->getObjeto())->ObterJavaClass()->getUTF8(classInfo->GetNameIndex());

	// obter o tipo dentro de className:
	TipoDado TipoDado;
	int i = 0;
	while (className[i] == '[') i++;

	string multiArrayType = className.substr(i+1, className.size()-i-2); // em caso de ser uma referência ([[[Ljava/lang/String;)

	switch (className[i]) {
		case 'L':
			if (multiArrayType != "java/lang/String") {
				runtimeDataArea->CarregarClasse(multiArrayType); // verifica se existe classe com esse nome
			}
			TipoDado = TipoDado::REFERENCE;
			break;
		case 'B':
			TipoDado = TipoDado::BYTE;
			break;
		case 'C':
			TipoDado = TipoDado::CHAR;
			break;
		case 'D':
			TipoDado = TipoDado::DOUBLE;
			break;
		case 'F':
			TipoDado = TipoDado::FLOAT;
			break;
		case 'I':
			TipoDado = TipoDado::INT;
			break;
		case 'J':
			TipoDado = TipoDado::LONG;
			break;
		case 'S':
			TipoDado = TipoDado::SHORT;
			break;
		case 'Z':
			TipoDado = TipoDado::BOOLEAN;
			break;
		default:
			cerr << "Descritor invalido em multianewarray" << endl;
			exit(1);
	}

	stack<int> count;
	for (int i = 0; i < dimensoes; i++) {
		Valor dimLength = topo->desempilhaOperando();
		assert(dimLength.tipo == TipoDado::INT);
		count.push(dimLength.dado);
	}

	cout<<"Consertar ExecutionEngine::i_multianewarray" << endl;
//	ObjetoArray *arr = new ObjetoArray((dimensoes > 1) ? TipoDado::REFERENCE : TipoDado);
//	arr->popularSubArray(TipoDado, count);  

	Valor valorArr;
	valorArr.tipo = TipoDado::REFERENCE;
	valorArr.dado = (uint64_t)arr;

	topo->empilharOperando(valorArr);

	topo->incrementaPC(4);
*/
}
 
void ExecutionEngine::i_ifnull(){

	Frame *topo = runtimeDataArea->topoPilha();

	Valor referencia = topo->desempilhaOperando();

	assert(referencia.tipo == TipoDado::REFERENCE);

	if ((Objeto*)((void*)(referencia.dado)) == NULL) {

		uint8_t *code = topo->getCode();
		uint8_t byte1 = code[1];
		uint8_t byte2 = code[2];
		int16_t salto =  (byte1 << 8) | byte2;
		topo->incrementaPC(salto);
	}
	else {

		topo->incrementaPC(3);

	}
}

void ExecutionEngine::i_ifnonnull(){

	Frame *topo = runtimeDataArea->topoPilha();

	Valor referencia = topo->desempilhaOperando();

	assert(referencia.tipo == TipoDado::REFERENCE);

	if ((Objeto*)(referencia.dado) != NULL) {
		uint8_t *code = topo->getCode();
		uint8_t byte1 = code[1];
		uint8_t byte2 = code[2];
		int16_t salto =  (byte1 << 8) | byte2;
		topo->incrementaPC(salto);
	}
	else {

		topo->incrementaPC(3);

	}

}

void ExecutionEngine::i_goto_w(){

	Frame *topo = runtimeDataArea->topoPilha();

	uint8_t *code = topo->getCode();
	uint8_t byte1 = code[1];
	uint8_t byte2 = code[2];
	uint8_t byte3 = code[3];
	uint8_t byte4 = code[4];
	int32_t offsetSalto = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

	topo->incrementaPC(offsetSalto);
	assert(topo->getPC() < (int32_t)topo->tamanhoCode());

}

void ExecutionEngine::i_jsr_w(){

	Frame *topo = runtimeDataArea->topoPilha();

	uint8_t *code = topo->getCode();
	uint8_t byte1 = code[1];
	uint8_t byte2 = code[2];
	uint8_t byte3 = code[3];
	uint8_t byte4 = code[4];
	int32_t offsetSalto = (byte1 << 24) | (byte2 << 16) | (byte3 << 8)| byte4;

	Valor endRetorno;
	endRetorno.tipo = TipoDado::RETURN_ADDR;
	endRetorno.dado = topo->getPC() + 5;
	topo->empilharOperando(endRetorno);

	topo->incrementaPC(offsetSalto);
	assert(topo->getPC() < (int32_t)(topo->tamanhoCode()));


}

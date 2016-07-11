#include "ExecutionEngine.hpp"
#include "ObjetoArray.hpp"
#include "ObjetoString.hpp"
#include "ObjetoInstancia.hpp"
#include "Erro.hpp"
#include "Endian.hpp"
#include <string.h>
#include <inttypes.h>
#include <cmath>
#include <string>
#include <memory>

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

#define DEBUG_EE
//#define DEBUG_EE_GET_STATIC
//#define DEBUG_EE_PLAY
//#define DEBUG_EE_INVOKEVIRTUAL
#define DEBUG_EE_EMPILHAR_FRAME
#define DEBUG_EE_STORE_VALOR
#define MINI_DEBUG
#ifdef DEBUG_EE
	#include"Opcode.hpp"
#endif
#ifdef MINI_DEBUG
	#include"Opcode.hpp"
#endif

ExecutionEngine::ExecutionEngine(void)
{
	inicializaInstrucoes();
	isWide= false;
}

void ExecutionEngine::SetRuntimeDataArea(RuntimeDataArea *runtimeDataArea)
{
	this->runtimeDataArea= runtimeDataArea;
}

void ExecutionEngine::Play(string classComMain)
{


	uint8_t instrucao;
#ifdef DEBUG_EE
	cout<< "ExecutionEngine::Play" << endl;
#endif
	if(runtimeDataArea == NULL)
	{
		throw new Erro("RuntimeDataArea nao instanciado!", "ExecutionEngine", "Play");
	}
	JavaClass *javaClass= runtimeDataArea->CarregarClasse(classComMain);
#ifdef DEBUG_EE_PLAY
	cout<< "ExecutionEngine::Play2" << endl;
#endif
#ifdef DEBUG_EE
	cout<< "Empilhando Main" << endl;
#endif
	if(javaClass->getMetodo("main","([Ljava/lang/String;)V") == NULL)
	{
		throw new Erro("Classe informada não contém main");
	}
#ifdef DEBUG_EE_PLAY
	cout<< "ExecutionEngine::Play3" << endl;
#endif
	vector<Valor>argumentos;
	Valor argumentosDaLinhaDeComando;
	argumentosDaLinhaDeComando.tipo= REFERENCIA;
	ObjetoArray *obj= new ObjetoArray(REFERENCIA);
	memcpy(&(argumentosDaLinhaDeComando.dado), &obj, sizeof(void*));
	argumentos.push_back(argumentosDaLinhaDeComando);
	
	runtimeDataArea->empilharFrame(new Frame(javaClass, "main", "([Ljava/lang/String;)V", argumentos, runtimeDataArea));
#ifdef DEBUG_EE_PLAY
	cout<< "ExecutionEngine::Play4" << endl;
#endif
	if(javaClass->getMetodo("<clinit>","()V") != NULL)
	{
#ifdef DEBUG_EE
	cout<< "Empilhando clinit da main" << endl;
#endif
#ifdef DEBUG_EE_PLAY
	cout<< "ExecutionEngine::Play5" << endl;
#endif
		runtimeDataArea->empilharFrame(new Frame(javaClass, "<clinit>","()V", argumentos, runtimeDataArea));
	}
#ifdef DEBUG_EE_PLAY
	cout<< "ExecutionEngine::Play6" << endl;
#endif

	do
	
	{
#ifdef DEBUG_EE_PLAY
	cout<< "ExecutionEngine::Play7\tTamanho da pilha: " << runtimeDataArea->ObterTamanhoDaPilhaDeFrames() << endl;
#endif
		instrucao = *(runtimeDataArea->topoPilha()->getCode());
#ifdef DEBUG_EE_PLAY
	cout<< "ExecutionEngine::Play8\t" << OpCode::GetReferencia()->GetMinemonico(instrucao) << " \t PC= " << runtimeDataArea->topoPilha()->getPC() << endl;
#endif
#ifdef MINI_DEBUG
	cout<< "ExecutionEngine::Play8\t" << OpCode::GetReferencia()->GetMinemonico(instrucao) << " \t PC= " << runtimeDataArea->topoPilha()->getPC() << endl;
#endif

		(this->*vetorDePonteirosParaFuncao[instrucao])();

#ifdef DEBUG_EE_PLAY

	cout<< "ExecutionEngine::Play9" << endl;
#endif

	}
	while(runtimeDataArea->ObterTamanhoDaPilhaDeFrames() > 0);
#ifdef DEBUG_EE_PLAY
	cout<< "ExecutionEngine::Play10" << endl;
#endif
	cout<<"****************************************************" << endl;
	cout<<"programa terminado com sucesso!" << endl;
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
//#define BREAK_NOP
#ifdef BREAK_NOP
	static int nopCount=0;
	nopCount++;
#endif
	runtimeDataArea->topoPilha()->incrementaPC(1);
#ifdef BREAK_NOP
	if(nopCount >10)
	{
		throw new Erro("Break no NOP");
	}
#endif
	
}

void ExecutionEngine::i_aconst_null(){ //Push the null object reference onto the operand stack. 
	Frame *toppilha = runtimeDataArea->topoPilha();
	Valor valor;
	valor.tipo = TipoDado::REFERENCIA;
	valor.dado = (uint64_t)NULL;
	toppilha->empilharOperando(valor);
}

void ExecutionEngine::i_iconst_m1(){ // Push the int constant i onto the operand stack. 

	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor;
	valor.tipo = TipoDado::INTEIRO;
	valor.dado=0;
	int32_t m1= -1;
	memcpy(&(valor.dado), &m1, 4);
//	valor.dado = (uint32_t)-1;

	toppilha->empilharOperando(valor);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_iconst_0(){ //Push the int constant 0 onto the operand stack. 

	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor;
	valor.tipo = TipoDado::INTEIRO;
	valor.dado = (uint32_t)0;

	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_iconst_1(){  //Push the int constant 1 onto the operand stack. 

	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor;
	valor.tipo = TipoDado::INTEIRO;
	valor.dado = (uint32_t)1;

	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);

}
void ExecutionEngine::i_iconst_2(){ //Push the int constant 2 onto the operand stack. 
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor;
	valor.tipo = TipoDado::INTEIRO;
	valor.dado = (uint32_t)2;

	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_iconst_3(){ //Push the int constant 3 onto the operand stack. 
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor;
	valor.tipo = TipoDado::INTEIRO;
	valor.dado = (uint32_t)3;

	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_iconst_4(){ //Push the int constant 4 onto the operand stack. 
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor;
	valor.tipo = TipoDado::INTEIRO;
	valor.dado = (uint32_t)4;

	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);

}
void ExecutionEngine::i_iconst_5(){//Push the int constant 5 onto the operand stack. 
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor;
	valor.tipo = TipoDado::INTEIRO;
	valor.dado = (uint32_t)5;

	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_lconst_0(){ //Push the long constant 0 onto the operand stack. 
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor pad;
	pad.tipo = TipoDado::PREENCHIMENTO;
	pad.dado = (uint32_t)0;

	Valor valor;
	valor.tipo = TipoDado::LONG;
	valor.dado = (uint64_t)0;

	toppilha->empilharOperando(pad);
	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);


}
void ExecutionEngine::i_lconst_1(){//Push the long constant 1 onto the operand stack. 
	
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor pad;
	pad.tipo = TipoDado::PREENCHIMENTO;
	pad.dado = (uint32_t)0;

	Valor valor;
	valor.tipo = TipoDado::LONG;
	valor.dado = (int64_t)1;

	toppilha->empilharOperando(pad);
	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_fconst_0(){//Push the float constant 0 onto the operand stack. 
	
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor;
	valor.tipo = TipoDado::FLOAT;
	valor.dado = (uint32_t)0;

	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_fconst_1(){//Push the float constant 1 onto the operand stack. 
	
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor;
	valor.tipo = TipoDado::FLOAT;
	float num=1.0;
	valor.dado = 0;
	memcpy(&(valor.dado), &num, 4);

	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_fconst_2(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor;
	valor.tipo = TipoDado::FLOAT;
	float num=2.0;
	valor.dado = 0;
	memcpy(&(valor.dado), &num, 4);

	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_dconst_0(){//Push the double constant 0 onto the operand stack. 
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor pad;
	pad.tipo = TipoDado::PREENCHIMENTO;
	pad.dado=0;

	Valor valor;
	valor.tipo = TipoDado::DOUBLE;
	double temp = 0;
	valor.dado=0;
	memcpy(&valor.dado, &temp, 8/*sizeof(double)*/);

	toppilha->empilharOperando(pad);
	toppilha->empilharOperando(valor);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_dconst_1(){//Push the double constant 1 onto the operand stack. 
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor pad;
	pad.tipo = TipoDado::PREENCHIMENTO;
	pad.dado=0;

	Valor valor;
	valor.tipo = TipoDado::DOUBLE;
	double temp =1;
	valor.dado=0;
	memcpy(&valor.dado, &temp, 8/*sizeof(double)*/);

	toppilha->empilharOperando(pad);
	toppilha->empilharOperando(valor);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}
//push byte pra pilha de operando
void ExecutionEngine::i_bipush(){

	Frame *toppilha = runtimeDataArea->topoPilha();
	uint8_t *code = toppilha->getCode();
	uint8_t byte = code[1];

	Valor valor;
	valor.tipo = TipoDado::INTEIRO;
	valor.dado = (int32_t)(int8_t) byte; // convertendo para inteiro e estendendo o sinal

	toppilha->empilharOperando(valor);

	toppilha->incrementaPC(2);

}
void ExecutionEngine::i_sipush(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	uint8_t *code = toppilha->getCode();
	int16_t num;
	memcpy(&num, &(code[1]), 2);
	num = InverterEndianess<int16_t>(num);

	Valor valor;
	valor.tipo = TipoDado::INTEIRO;
	valor.dado = num;

	toppilha->empilharOperando(valor);

	toppilha->incrementaPC(3);
}
//Push item from run-time constant pool
void ExecutionEngine::i_ldc(){

	//usa no helloworld


	Frame *topo = runtimeDataArea->topoPilha();
	
	Valor valor;
	uint8_t *code = topo->getCode();
	uint8_t index = code[1];
	
	JavaClass *classe= (topo->getObjeto()== NULL )? topo->ObterJavaClass(): ((ObjetoInstancia*)topo->getObjeto())->ObterJavaClass();

	vector<cp_info*> constantPool = classe->getConstantPool();
	
	cp_info *ponteiroCpInfo = constantPool[index - 1];
	
	if(ponteiroCpInfo->GetTag() == CONSTANT_String)
	{
		CONSTANT_Utf8_info *utf8Entry = (CONSTANT_Utf8_info*) constantPool[((CONSTANT_String_info*)ponteiroCpInfo)->GetStringIndex() - 1];
		string utf8String = utf8Entry->GetString();
#ifdef DEBUG_EE
cout<<"chegou i_ldc" << endl;
#endif
		valor.tipo = TipoDado::REFERENCIA;
		ObjetoString * temp = new ObjetoString(utf8String);
		valor.dado = 0;
		memcpy(&(valor.dado), &temp, sizeof(void*));
#ifdef DEBUG_EE
cout<<"i_ldc\tvalor.dado= " << temp->ObterString() << endl;
#endif
	}
	else if (ponteiroCpInfo->GetTag()  == CONSTANT_Integer)
	{
		valor.tipo = TipoDado::INTEIRO;
		valor.dado = ((CONSTANT_Integer_info*)constantPool[index -1])->GetNumero();
	} 
	else if (ponteiroCpInfo->GetTag()  == CONSTANT_Float)
	{
		float numero = ((CONSTANT_Float_info*)constantPool[index -1])->GetNumero();
		
		valor.tipo = TipoDado::FLOAT;
		valor.dado = numero;
		
	}
	else
	{
		string errMsg= "CP invalido em i_LDC: ";
		errMsg+= std::to_string(constantPool[index -1]->GetTag());
		throw new Erro(errMsg, "ExecutionEngine", "i_ldc");
	}
	
	topo->empilharOperando(valor);
	topo->incrementaPC(2);

}

void ExecutionEngine::i_ldc_w(){
	
	Frame *topo = runtimeDataArea->topoPilha();
	
	Valor valor;
	uint8_t *code = topo->getCode();
	uint8_t byte1 = code[1];
	uint8_t byte2 = code[2];
	uint16_t index = (byte1 << 8) | byte2;
	
	JavaClass *classe= topo->ObterJavaClass();

	vector<cp_info*> constantPool = classe->getConstantPool();
	
	cp_info *ponteiroCpInfo = constantPool[index - 1];
	
	if(ponteiroCpInfo->GetTag() == CONSTANT_String)
	{
		CONSTANT_Utf8_info *utf8Entry = (CONSTANT_Utf8_info*) constantPool[((CONSTANT_String_info*)ponteiroCpInfo)->GetStringIndex() - 1];
		string utf8String = utf8Entry->GetString();
#ifdef DEBUG_EE
cout<<"chegou i_ldc" << endl;
#endif
		valor.tipo = TipoDado::REFERENCIA;
		ObjetoString * temp = new ObjetoString(utf8String);
		valor.dado=0;
		memcpy(&(valor.dado), &temp, sizeof(void*));
#ifdef DEBUG_EE
cout<<"i_ldc\tvalor.dado= " << temp->ObterString() << endl;
#endif
	}
	else if (ponteiroCpInfo->GetTag()  == CONSTANT_Integer)
	{
		valor.tipo = TipoDado::INTEIRO;
		valor.dado = ((CONSTANT_Integer_info*)constantPool[index -1])->GetNumero();
	} 
	else if (ponteiroCpInfo->GetTag()  == CONSTANT_Float)
	{
		float numero = ((CONSTANT_Float_info*)constantPool[index -1])->GetNumero();
		
		valor.tipo = TipoDado::FLOAT;
		valor.dado = numero;
		
	}
	else
	{
		string errMsg= "CP invalido em i_LDC_w: ";
		errMsg+= std::to_string(constantPool[index -1]->GetTag());
		throw new Erro(errMsg, "ExecutionEngine", "i_ldc_w");
	}
	
	topo->empilharOperando(valor);
	topo->incrementaPC(3);
}

void ExecutionEngine::i_ldc2_w(){ 

	Frame *toppilha = runtimeDataArea->topoPilha();

	uint8_t *code = toppilha->getCode();
	uint8_t byte1 = code[1];
	uint8_t byte2 = code[2];
	uint16_t index = (byte1 << 8) | byte2;
	
	JavaClass *classe= (toppilha->getObjeto()== NULL )? toppilha->ObterJavaClass(): ((ObjetoInstancia*)toppilha->getObjeto())->ObterJavaClass();
	vector<cp_info*> constantPool = classe->getConstantPool();
	cp_info *ponteiroCpInfo = constantPool[index - 1];
	
	Valor valor;
	
	if (ponteiroCpInfo->GetTag() == CONSTANT_Long) {
		int64_t num= ((CONSTANT_Long_info*)ponteiroCpInfo)->GetNumero();
		memcpy(&(valor.dado), &num, 8);
		valor.tipo = TipoDado::LONG;
		
		Valor padding;
		padding.tipo = TipoDado::PREENCHIMENTO;
		padding.dado= 0;
		
		toppilha->empilharOperando(padding);
	} else if (ponteiroCpInfo->GetTag() == CONSTANT_Double) {
		
		double num= ((CONSTANT_Double_info*)ponteiroCpInfo)->GetNumero();
		memcpy(&(valor.dado), &num, 8);
		valor.tipo = TipoDado::DOUBLE;
		
		Valor padding;
		padding.tipo = TipoDado::PREENCHIMENTO;
		padding.dado= 0;
		
		toppilha->empilharOperando(padding);
	} else {
		string strErr= "ldc2_w tentando acessar um elemento da CP invalido: ";
		strErr+= to_string(ponteiroCpInfo->GetTag());
		throw new Erro(strErr.c_str(), "ExecutionEngine", "ldc2_w");
	}
	
	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(3);

}

void ExecutionEngine::i_iload(){

	Frame *toppilha = runtimeDataArea->topoPilha();
	
	uint8_t *code = toppilha->getCode();
	uint8_t byte1 = code[1];
	int16_t index = (int16_t)byte1;

	//Verifica se a funcao i_wide foi chamada anteriormente
	if(isWide) {
		//Copia byte[1] concatenado com byte[2] para index
		memcpy(&index, &(code[1]), 2/*sizeof(double)*/);
		index= InverterEndianess<int16_t>(index);//nao esquecer de inerter o endian;

		runtimeDataArea->topoPilha()->incrementaPC(3);
		isWide = false;

	}

	else {

		runtimeDataArea->topoPilha()->incrementaPC(2);

	}



	if(((int16_t)(toppilha->tamanhoVetorVariaveis())) <= index){

		throw new Erro("Tamanho do vetor de variáveis menor que o index", "ExecutionEngine", "i_iload");

	}
	Valor valor = toppilha->getValorVariavelLocal(index);
	
	toppilha->empilharOperando(valor);
}
void ExecutionEngine::i_lload(){

	Frame *toppilha = runtimeDataArea->topoPilha();
	
	uint8_t *code = toppilha->getCode();
	uint8_t byte1 = code[1];
	int16_t index = (int16_t)byte1;
	//Verifica se a função chamada anteriormente é um wide
	if(isWide) {

		uint16_t byte2 = code[2];
		index = (byte1 << 8) | byte2;
		runtimeDataArea->topoPilha()->incrementaPC(3);
		isWide = false;

	}
	else {

		runtimeDataArea->topoPilha()->incrementaPC(2);

	}

	if(((int16_t)(toppilha->tamanhoVetorVariaveis())) <= index + 1){

		throw new Erro("Tamanho do vetor de variáveis menor que o index + 1", "ExecutionEngine", "i_lload");

	}

	Valor valor = toppilha->getValorVariavelLocal(index);
	if(!(valor.tipo == TipoDado::LONG)){

		throw new Erro("valor.tipo diferente de LONG", "ExecutionEngine", "i_lload");

	}
	
	Valor pad;
	pad.tipo = TipoDado::PREENCHIMENTO;
	pad.dado = 0;
	
	toppilha->empilharOperando(pad);
	toppilha->empilharOperando(valor);
}
void ExecutionEngine::i_fload(){
	Frame *topPilha = runtimeDataArea->topoPilha();
	
	uint8_t *code = topPilha->getCode();
	uint8_t byte1 = code[1];
	int16_t index = (int16_t)byte1;
	//Verifica se i_wide foi chamada anteriormente
	if(isWide) {
		uint16_t byte2 = code[2];
		index = (byte1 << 8) | byte2;
		runtimeDataArea->topoPilha()->incrementaPC(3);
		isWide = false;
	}
	else {
		runtimeDataArea->topoPilha()->incrementaPC(2);
	}

	if(((int16_t)(topPilha->tamanhoVetorVariaveis())) <= index){

		throw new Erro("Tamanho do vetor de variaveis é menor que o index", "ExecutionEngine", "i_fload");

	}

	Valor valor = topPilha->getValorVariavelLocal(index);
	
	topPilha->empilharOperando(valor);
}
void ExecutionEngine::i_dload(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	uint8_t *code = toppilha->getCode();
	uint8_t byte1 = code[1];
	int16_t index = (int16_t)byte1;
	//Verifica se i_wide foi chamada
	if(isWide) {
		uint16_t byte2 = code[2];
		index = (byte1 << 8) | byte2;
		runtimeDataArea->topoPilha()->incrementaPC(3);
		isWide = false;
	}
	else {

		runtimeDataArea->topoPilha()->incrementaPC(2);

	}

	if(((int16_t)(toppilha->tamanhoVetorVariaveis())) <= index + 1){

		throw new Erro("Tamanho do vetor de variaveis é menor que o index + 1", "ExecutionEngine", "i_dload");
	
	}

	Valor valor = toppilha->getValorVariavelLocal(index);
	if(!(valor.tipo == TipoDado::DOUBLE)){

		throw new Erro("Tipo de dado diferente de DOUBLE ", "ExecutionEngine", "i_dload");

	}
	
	Valor pad;
	pad.tipo = TipoDado::PREENCHIMENTO;
	pad.dado = 0;
	
	toppilha->empilharOperando(pad);
	toppilha->empilharOperando(valor);
}
void ExecutionEngine::i_aload(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	uint8_t *code = toppilha->getCode();
	uint8_t byte1 = code[1];
	int16_t index = (int16_t)byte1;
	//Verifica se i_wide foi chamada anteriormente
	if(isWide) {
		uint16_t byte2 = code[2];
		index = (byte1 << 8) | byte2;
		runtimeDataArea->topoPilha()->incrementaPC(3);
		isWide = false;
	}
	else {
		runtimeDataArea->topoPilha()->incrementaPC(2);
	}

	if(((int16_t)(toppilha->tamanhoVetorVariaveis())) <= index){

		throw new Erro("Tamanho do vetor de variaveis é menor que o index", "ExecutionEngine", "i_aload");

	}
		
	Valor valor = toppilha->getValorVariavelLocal(index);
	if(!(valor.tipo == TipoDado::REFERENCIA)){

		throw new Erro("O tipo do dado não é uma referencia", "ExecutionEngine", "i_aload");
	}
	
	toppilha->empilharOperando(valor);
}
void ExecutionEngine::i_iload_0(){

	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->getValorVariavelLocal(0);
	if(!(valor.tipo == TipoDado::INTEIRO)){
		
		throw new Erro("O tipo do dado não é um inteiro", "ExecutionEngine", "i_load_0");

	}
		
	toppilha->empilharOperando(valor);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_iload_1(){

	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->getValorVariavelLocal(1);
		if(!(valor.tipo == TipoDado::INTEIRO)){
		
		throw new Erro("O tipo do dado não é um inteiro", "ExecutionEngine", "i_load_1");

	}
	toppilha->empilharOperando(valor);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_iload_2(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->getValorVariavelLocal(2);
	 if(!(valor.tipo == TipoDado::INTEIRO)){
		
		throw new Erro("O tipo do dado não é um inteiro", "ExecutionEngine", "i_load_2");

	}
	toppilha->empilharOperando(valor);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_iload_3(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->getValorVariavelLocal(3);
	 if(!(valor.tipo == TipoDado::INTEIRO)){
		
		throw new Erro("O tipo do dado não é um inteiro", "ExecutionEngine", "i_load_3");

	}
	toppilha->empilharOperando(valor);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_lload_0(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->getValorVariavelLocal(1);
	 if(valor.tipo != TipoDado::PREENCHIMENTO){
		
		throw new Erro("O tipo do dado não é um pad", "ExecutionEngine", "i_lload_0");

	}
	toppilha->empilharOperando(valor);

	valor = toppilha->getValorVariavelLocal(0);
	if(valor.tipo != TipoDado::LONG){
	
			throw new Erro("O tipo do dado não é um LONG", "ExecutionEngine", "i_lload_0");

	}
		
	toppilha->empilharOperando(valor);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_lload_1(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->getValorVariavelLocal(2);
	 if(!(valor.tipo == TipoDado::PREENCHIMENTO)){
		
		throw new Erro("O tipo do dado não é um pad", "ExecutionEngine", "i_lload_1");

	}
	toppilha->empilharOperando(valor);

	valor = toppilha->getValorVariavelLocal(1);
	if(!(valor.tipo == TipoDado::LONG)){
	
			throw new Erro("O tipo do dado não é um LONG", "ExecutionEngine", "i_lload_1");

	}
	toppilha->empilharOperando(valor);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_lload_2(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->getValorVariavelLocal(1);
	 if(!(valor.tipo == TipoDado::PREENCHIMENTO)){
		
		throw new Erro("O tipo do dado não é um pad", "ExecutionEngine", "i_lload_2");

	}
	toppilha->empilharOperando(valor);

	valor = toppilha->getValorVariavelLocal(2);
	if(!(valor.tipo == TipoDado::LONG)){
	
			throw new Erro("O tipo do dado não é um LONG", "ExecutionEngine", "i_lload_2");

	}
	toppilha->empilharOperando(valor);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_lload_3(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->getValorVariavelLocal(4);
	 if(!(valor.tipo == TipoDado::PREENCHIMENTO)){
		
		throw new Erro("O tipo do dado não é um pad", "ExecutionEngine", "i_lload_3");

	}
	toppilha->empilharOperando(valor);

	valor = toppilha->getValorVariavelLocal(3);
	if(!(valor.tipo == TipoDado::LONG)){
	
			throw new Erro("O tipo do dado não é um LONG", "ExecutionEngine", "i_lload_3");

	}
	toppilha->empilharOperando(valor);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_fload_0(){

	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->getValorVariavelLocal(0);
	 if(!(valor.tipo == TipoDado::FLOAT)){
		
		throw new Erro("O tipo do dado não é um float", "ExecutionEngine", "i_fload_0");

	}
	toppilha->empilharOperando(valor);

	runtimeDataArea->topoPilha()->incrementaPC(1)
;	
}
void ExecutionEngine::i_fload_1(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->getValorVariavelLocal(1);
	 if(!(valor.tipo == TipoDado::FLOAT)){
		
		throw new Erro("O tipo do dado não é um float", "ExecutionEngine", "i_fload_1");

	}
	toppilha->empilharOperando(valor);

	runtimeDataArea->topoPilha()->incrementaPC(1);	
}
void ExecutionEngine::i_fload_2(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->getValorVariavelLocal(2);
	 if(!(valor.tipo == TipoDado::FLOAT)){
		
		throw new Erro("O tipo do dado não é um float", "ExecutionEngine", "i_fload_2");

	}
	toppilha->empilharOperando(valor);

	runtimeDataArea->topoPilha()->incrementaPC(1);		
}
void ExecutionEngine::i_fload_3(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->getValorVariavelLocal(3);
	 if(!(valor.tipo == TipoDado::FLOAT)){
		
		throw new Erro("O tipo do dado não é um float", "ExecutionEngine", "i_fload_3");

	}
	toppilha->empilharOperando(valor);

	runtimeDataArea->topoPilha()->incrementaPC(1);	
}
void ExecutionEngine::i_dload_0(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->getValorVariavelLocal(1);
	 if(!(valor.tipo == TipoDado::PREENCHIMENTO)){
		
		throw new Erro("O tipo do dado não é um pad", "ExecutionEngine", "i_dload_0");

	}
	toppilha->empilharOperando(valor);

	valor = toppilha->getValorVariavelLocal(0);
	 if(!(valor.tipo == TipoDado::DOUBLE)){
		
		throw new Erro("O tipo do dado não é um double ", "ExecutionEngine", "i_dload_0");

	}
	toppilha->empilharOperando(valor);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}	
void ExecutionEngine::i_dload_1(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->getValorVariavelLocal(2);
	 if(!(valor.tipo == TipoDado::PREENCHIMENTO)){
		
		throw new Erro("O tipo do dado não é um pad", "ExecutionEngine", "i_dload_1");

	}
	toppilha->empilharOperando(valor);

	valor = toppilha->getValorVariavelLocal(1);
	 if(!(valor.tipo == TipoDado::DOUBLE)){
		
		throw new Erro("O tipo do dado não é um double ", "ExecutionEngine", "i_dload_1");

	}
	toppilha->empilharOperando(valor);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_dload_2(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->getValorVariavelLocal(3);
	 if(!(valor.tipo == TipoDado::PREENCHIMENTO)){
		
		throw new Erro("O tipo do dado não é um pad", "ExecutionEngine", "i_dload_2");

	}
	toppilha->empilharOperando(valor);

	valor = toppilha->getValorVariavelLocal(2);
	 if(!(valor.tipo == TipoDado::DOUBLE)){
		
		throw new Erro("O tipo do dado não é um double ", "ExecutionEngine", "i_dload_2");

	}
	toppilha->empilharOperando(valor);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_dload_3(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->getValorVariavelLocal(4);
	 if(!(valor.tipo == TipoDado::PREENCHIMENTO)){
		
		throw new Erro("O tipo do dado não é um pad", "ExecutionEngine", "i_lload_3");

	}
	toppilha->empilharOperando(valor);

	valor = toppilha->getValorVariavelLocal(3);
	 if(!(valor.tipo == TipoDado::DOUBLE)){
		
		throw new Erro("O tipo do dado não é um double ", "ExecutionEngine", "i_dload_3");

	}
	toppilha->empilharOperando(valor);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_aload_0(){
	//usa na mainvazia
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->getValorVariavelLocal(0);
	 if(!(valor.tipo == TipoDado::REFERENCIA)){
		string errMsg= "O tipo do dado não é um uma referencia \t tipo: ";
		errMsg+= ObterStringTipo(valor.tipo);
		throw new Erro(errMsg, "ExecutionEngine", "i_aload_0");

	}

	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_aload_1(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->getValorVariavelLocal(1);
	 if(!(valor.tipo == TipoDado::REFERENCIA)){
		
		throw new Erro("O tipo do dado não é um uma referencia", "ExecutionEngine", "i_aload_1");

	}

	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_aload_2(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->getValorVariavelLocal(2);
	 if(!(valor.tipo == TipoDado::REFERENCIA)){
		
		throw new Erro("O tipo do dado não é um uma referencia", "ExecutionEngine", "i_aload_2");

	}

	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_aload_3(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->getValorVariavelLocal(3);
	 if(!(valor.tipo == TipoDado::REFERENCIA)){
		
		throw new Erro("O tipo do dado não é um uma referencia", "ExecutionEngine", "i_aload_3");

	}

	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_iaload(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	ObjetoArray *array;
	
	Valor index = toppilha->desempilhaOperando();
		 if(!(index.tipo == TipoDado::INTEIRO)){
		
		throw new Erro("O tipo do dado não é um int", "ExecutionEngine", "i_iload");

	}
	Valor arrayref = toppilha->desempilhaOperando();
	
	array = (ObjetoArray*)(arrayref.dado);
	
	if (array == NULL) {
		throw new Erro("Array esta vazia.", "ExecutionEngine", "i_iaload");
	}
	int32_t num;
	memcpy(&num, &(index.dado), 4);
	if ((uint32_t)num > array->ObterTamanho() || num < 0) {
		throw new Erro("Index do array esta fora do limite.", "ExecutionEngine", "i_iaload");
	}
	toppilha->empilharOperando(array->ObterValor(num));
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_laload(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	ObjetoArray *array;
	
	Valor index = toppilha->desempilhaOperando();
	
	Valor arrayref = toppilha->desempilhaOperando();
	
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
	padding.dado = TipoDado::PREENCHIMENTO;
	
	toppilha->empilharOperando(padding);
	toppilha->empilharOperando(array->ObterValor(num));
	
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_faload(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	ObjetoArray *array;
	
	Valor index = toppilha->desempilhaOperando();
	
	Valor arrayref = toppilha->desempilhaOperando();
	
	array = (ObjetoArray*)(arrayref.dado);
	
	if (array == NULL) {
		throw new Erro("Array esta vazia.", "ExecutionEngine", "i_faload");
	}
	int32_t num;
	memcpy(&num, &(index.dado), 4);
	if ((uint32_t)num > array->ObterTamanho() || num < 0) {
		throw new Erro("Index do array esta fora do limite.", "ExecutionEngine", "i_faload");
	}
	toppilha->empilharOperando(array->ObterValor(num));
	
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_daload(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	ObjetoArray *array;
	
	Valor index = toppilha->desempilhaOperando();

	
	Valor arrayref = toppilha->desempilhaOperando();
	
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
	padding.tipo = TipoDado::PREENCHIMENTO;
	padding.dado = 0;
	
	toppilha->empilharOperando(padding);
	toppilha->empilharOperando(array->ObterValor(num));
	
	runtimeDataArea->topoPilha()->incrementaPC(1);
}

void ExecutionEngine::i_aaload(){ //Load reference from array 
	Frame *toppilha = runtimeDataArea->topoPilha();
	ObjetoArray *array;
	
	Valor index = toppilha->desempilhaOperando();
	
	Valor arrayref = toppilha->desempilhaOperando();
	
	array = (ObjetoArray*)(arrayref.dado);
	
	if (array == NULL) {
		throw new Erro("Array esta vazia.", "ExecutionEngine", "i_aaload");
	}
	int32_t num;
	memcpy(&num, &(index.dado), 4);
	if ((uint32_t)num > array->ObterTamanho() || num < 0) {
		throw new Erro("Index do array esta fora do limite.", "ExecutionEngine", "i_aaload");
	}
	toppilha->empilharOperando(array->ObterValor(num));
	
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_baload(){

Frame *toppilha = runtimeDataArea->topoPilha();
	ObjetoArray *array;
	
	Valor index = toppilha->desempilhaOperando();
	
	Valor arrayref = toppilha->desempilhaOperando();
	
	array = (ObjetoArray*)(arrayref.dado);
	
	if (array == NULL) {
		throw new Erro("Array esta vazia.", "ExecutionEngine", "i_aaload");
	}
	int32_t num;
	memcpy(&num, &(index.dado), 4);
	if ((uint32_t)num > array->ObterTamanho() || num < 0) {
		throw new Erro("Index do array esta fora do limite.", "ExecutionEngine", "i_aaload");
	}

	Valor op = array->ObterValor(index.dado);
	if(!(op.tipo == TipoDado::BOOLEANO || op.tipo == TipoDado::BYTE)){

		throw new Erro("o operando deve ser BOOLEANO ou BYTE.", "ExecutionEngine", "i_baload");
		
	}
	
	op.tipo = TipoDado::INTEIRO;

	toppilha->empilharOperando(op);
	toppilha->incrementaPC(1);
}

void ExecutionEngine::i_caload(){

	Frame *toppilha = runtimeDataArea->topoPilha();	
	ObjetoArray *array;
	
	Valor index = toppilha->desempilhaOperando();
	
	Valor arrayref = toppilha->desempilhaOperando();
	
	array = (ObjetoArray*)(arrayref.dado);
	
	if (array == NULL) {
		throw new Erro("Array esta vazia.", "ExecutionEngine", "i_caload");
	}
	int32_t num;
	memcpy(&num, &(index.dado), 4);
	if ((uint32_t)num > array->ObterTamanho() || num < 0) {
		throw new Erro("Index do array esta fora do limite.", "ExecutionEngine", "i_caload");
	}

	Valor op = array->ObterValor(index.dado);
	if(!(op.tipo == TipoDado::BOOLEANO || op.tipo == TipoDado::BYTE)){

		throw new Erro("o operando deve ser BOOLEANO ou BYTE.", "ExecutionEngine", "i_caload");
		
	}

	op.tipo = TipoDado::INTEIRO;
	
	toppilha->empilharOperando(op);
	toppilha->incrementaPC(1);

}
void ExecutionEngine::i_saload(){

	Frame *topo = runtimeDataArea->topoPilha();
	ObjetoArray *array;

	Valor indice = topo->desempilhaOperando();
	if(!(indice.tipo == TipoDado::INTEIRO)){

		throw new Erro("o operando deve ser INTEIRO.", "ExecutionEngine", "i_saload");
		
	}

	Valor arrayref = topo->desempilhaOperando();

	if(!(arrayref.tipo == TipoDado::REFERENCIA)){
		
		throw new Erro("o operando deve ser uma referencia.", "ExecutionEngine", "i_saload");
		
	}
	if(!(((Objeto*)arrayref.dado)->ObterTipoObjeto() == TipoObjeto::ARRAY)){
		
		throw new Erro("a referencia deve ser para um array.", "ExecutionEngine", "i_saload");
		
	}

	array = (ObjetoArray *) arrayref.dado;

	if (array == NULL) {
		cerr << "NullPointerException" << endl;
		exit(1);
	}

	if (indice.dado > array->ObterTamanho() || indice.dado < 0) {
		cerr << "ArrayIndexOutOfBoundsException" << endl;
		exit(2);
	}
	
	Valor shortOp = array->ObterValor(indice.dado);
	shortOp.tipo = TipoDado::INTEIRO;
	
	topo->empilharOperando(shortOp);
	topo->incrementaPC(1);


}
void ExecutionEngine::i_istore(){
	Frame *topoDaPilhaDeFrames = runtimeDataArea->topoPilha();
	uint8_t *instrucoes = topoDaPilhaDeFrames->getCode();
	Valor val;
	val.tipo = INTEIRO;
	if(isWide)
	{
		int16_t indice;
		memcpy(&indice, &(instrucoes[1]), 2);
		indice= InverterEndianess<uint16_t>(indice);
		int64_t aux= indice; 
		memcpy(&(val.dado), &aux, 8);
		StoreValor(val);
		topoDaPilhaDeFrames->incrementaPC(3);
		isWide= false;
	}
	else
	{
#ifdef DEBUG_EE
cout << "ExecutionEngine::i_istore" << endl;
#endif
		int8_t indice;
		memcpy(&indice, &(instrucoes[1]), 1);
		int64_t aux= indice;
		memcpy(&(val.dado), &aux, 8);
#ifdef DEBUG_EE
cout << "ExecutionEngine::i_istore2 \tval.dado = " << val.dado << endl;
#endif
		StoreValor(val);
		topoDaPilhaDeFrames->incrementaPC(2);
	}
	return;
}
void ExecutionEngine::i_lstore(){

	Frame *topoDaPilhaDeFrames = runtimeDataArea->topoPilha();
	#ifdef DEBUG_EE
	cout << "ExecutionEngine::i_lstore 0 \t  "<< " \tvalor PC=  "<< topoDaPilhaDeFrames->getPC() << endl;
	#endif

	uint8_t *instrucoes = topoDaPilhaDeFrames->getCode();
	int16_t indice;
	Valor val;
	val.tipo = TipoDado::LONG;
	topoDaPilhaDeFrames->getCode();//dando pop do preenchimento
	if(isWide)
	{
		memcpy(&indice, &(instrucoes[1]), 2);
		indice= InverterEndianess<uint16_t>(indice);
		val.dado= (int64_t)indice;
#ifdef DEBUG_EE
cout << "ExecutionEngine::i_lstore 0 \t indice = " << indice << " \ttamanhpilha=  "<< topoDaPilhaDeFrames->tamanhoVetorVariaveis() << endl;
#endif
		StoreValor(val);
		topoDaPilhaDeFrames->incrementaPC(3);
		isWide=false;
	}
	else
	{
#ifdef DEBUG_EE
cout << "ExecutionEngine::i_lstore 1" << endl;
#endif
		//aux para expansao de tipo
		int8_t aux=0;
		memcpy(&aux, &(instrucoes[1]), 1);
		indice= aux;
		val.dado= indice;
#ifdef DEBUG_EE
cout << "ExecutionEngine::i_lstore 2 \tval.dado = " << val.dado << endl;
#endif
		StoreValor(val);
		topoDaPilhaDeFrames->incrementaPC(2);
	}
	
#ifdef DEBUG_EE
cout << "ExecutionEngine::i_lstore 3 " << val.dado << endl;
#endif

	//como é um long devemos colocar preenchimento
	Valor val2;
	val2.tipo= TipoDado::PREENCHIMENTO;
	val2.dado= (val.dado)+1;
#ifdef DEBUG_EE
cout << "ExecutionEngine::i_lstore 3,5 valdado:" << val2.dado << endl;
#endif
	StoreValor(val2);
#ifdef DEBUG_EE
cout << "ExecutionEngine::i_lstore 4 " << val2.dado << endl;
#endif


	return;
}
void ExecutionEngine::i_fstore(){
	Frame *topoDaPilhaDeFrames = runtimeDataArea->topoPilha();
	uint8_t *instrucoes = topoDaPilhaDeFrames->getCode();
	uint16_t indice;
	Valor val;
	val.tipo = FLOAT;
	if(isWide)
	{
		memcpy(&indice, &(instrucoes[1]), 2);
		indice= InverterEndianess<uint16_t>(indice);
		val.dado=0;
		memcpy(&(val.dado), &indice, 2);
		StoreValor(val);
		topoDaPilhaDeFrames->incrementaPC(3);
		isWide=false;
	}
	else
	{
#ifdef DEBUG_EE
cout << "ExecutionEngine::i_fstore" << endl;
#endif
		int8_t aux;
		memcpy(&aux, &(instrucoes[1]), 1);
		indice= aux;
		val.dado= indice;
#ifdef DEBUG_EE
cout << "ExecutionEngine::i_fstore \tval.dado = " << val.dado << endl;
#endif
		StoreValor(val);
		topoDaPilhaDeFrames->incrementaPC(2);
	}

	return;

}
void ExecutionEngine::i_dstore(){
	Frame *topoDaPilhaDeFrames = runtimeDataArea->topoPilha();
	uint8_t *instrucoes = topoDaPilhaDeFrames->getCode();
	uint16_t indice;
	Valor val;
	val.tipo = DOUBLE;
	topoDaPilhaDeFrames->getCode();//dando pop do preenchimento
	if(isWide)
	{
		memcpy(&indice, &(instrucoes[1]), 2);
		indice= InverterEndianess<uint16_t>(indice);
		val.dado= indice;
		StoreValor(val);
		topoDaPilhaDeFrames->incrementaPC(3);
		isWide= false;
	}
	else
	{
#ifdef DEBUG_EE
cout << "ExecutionEngine::i_dstore" << endl;
#endif
		uint8_t aux;
		memcpy(&aux, &(instrucoes[1]), 1);
		indice= aux;
		val.dado= indice;
#ifdef DEBUG_EE
cout << "ExecutionEngine::i_dstore \tval.dado = " << val.dado << endl;
#endif
		StoreValor(val);
		topoDaPilhaDeFrames->incrementaPC(2);
	}
	//como é um long devemos colocar preenchimento
	val.tipo= PREENCHIMENTO;
	val.dado= (val.dado)+1;
	StoreValor(val);
	return;
}

void ExecutionEngine::i_astore(){

	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->desempilhaOperando();

	uint8_t *code = toppilha->getCode();
	uint8_t byte1 = code[1]; //índice do vetor de variáveis locais
	int16_t index = (int16_t)byte1;

	if (isWide) {

		uint8_t byte2 = code[2];
		index = (byte1 << 8) | byte2;
		runtimeDataArea->topoPilha()->incrementaPC(3);
		isWide = false;

	}
	 else {

		runtimeDataArea->topoPilha()->incrementaPC(2);

	}

	toppilha->mudarVariavelLocal(valor, index);
}
void ExecutionEngine::i_istore_0(){

	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->desempilhaOperando();
	toppilha->mudarVariavelLocal(valor, 0);

	runtimeDataArea->topoPilha()->incrementaPC(1);

}
void ExecutionEngine::i_istore_1(){

	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->desempilhaOperando();
	toppilha->mudarVariavelLocal(valor, 1);

	runtimeDataArea->topoPilha()->incrementaPC(1);

}
void ExecutionEngine::i_istore_2(){

	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->desempilhaOperando();
	toppilha->mudarVariavelLocal(valor, 2);

	runtimeDataArea->topoPilha()->incrementaPC(1);

}
void ExecutionEngine::i_istore_3(){

	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->desempilhaOperando();
	toppilha->mudarVariavelLocal(valor, 3);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_lstore_0(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->desempilhaOperando();
	
	toppilha->mudarVariavelLocal(valor, 0);

	valor = toppilha->desempilhaOperando();
	toppilha->mudarVariavelLocal(valor, 1);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_lstore_1(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->desempilhaOperando();
	
	toppilha->mudarVariavelLocal(valor, 1);

	valor = toppilha->desempilhaOperando();
	toppilha->mudarVariavelLocal(valor, 2);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_lstore_2(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->desempilhaOperando();

	
	toppilha->mudarVariavelLocal(valor, 2);

	valor = toppilha->desempilhaOperando();
	toppilha->mudarVariavelLocal(valor, 3);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_lstore_3(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->desempilhaOperando();
	
	toppilha->mudarVariavelLocal(valor, 3);

	valor = toppilha->desempilhaOperando();
	toppilha->mudarVariavelLocal(valor, 4);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_fstore_0(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->desempilhaOperando();
	toppilha->mudarVariavelLocal(valor, 0);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_fstore_1(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->desempilhaOperando();
	toppilha->mudarVariavelLocal(valor, 1);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_fstore_2(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->desempilhaOperando();
	toppilha->mudarVariavelLocal(valor, 2);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_fstore_3(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->desempilhaOperando();
	toppilha->mudarVariavelLocal(valor, 3);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_dstore_0(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor = toppilha->desempilhaOperando();
	
	toppilha->mudarVariavelLocal(valor, 0);

	valor = toppilha->desempilhaOperando();
	toppilha->mudarVariavelLocal(valor, 1);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}

void ExecutionEngine::i_dstore_1(){
	Valor val;
	val.tipo = DOUBLE;
	val.dado= 1;
	StoreValor(val);

	val.tipo = PREENCHIMENTO;
	val.dado= 2;
	StoreValor(val);
	
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_dstore_2(){
	Valor val;
	val.tipo = DOUBLE;
	val.dado= 2;
	StoreValor(val);

	val.tipo = PREENCHIMENTO;
	val.dado= 3;
	StoreValor(val);
	
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_dstore_3(){
	Valor val;
	val.tipo = DOUBLE;
	val.dado= 3;
	StoreValor(val);

	val.tipo = PREENCHIMENTO;
	val.dado= 4;
	StoreValor(val);
	
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_astore_0(){
	Valor val;
	val.tipo = REFERENCIA;
	val.dado= 0;
	StoreValor(val);
	
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_astore_1(){
	Valor val;
	val.tipo = REFERENCIA;
	val.dado= 1;
	StoreValor(val);
	
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_astore_2(){
	Valor val;
	val.tipo = REFERENCIA;
	val.dado= 2;
	StoreValor(val);
	
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_astore_3(){
	Valor val;
	val.tipo = REFERENCIA;
	val.dado= 3;
	StoreValor(val);
	
	runtimeDataArea->topoPilha()->incrementaPC(1);
}

void ExecutionEngine::i_iastore(){
	
	Frame *topo = runtimeDataArea->topoPilha();
	ObjetoArray *array;

	Valor op = topo->desempilhaOperando();
	if(!(op.tipo == TipoDado::INTEIRO)){

		throw new Erro("Valor não é um int", "ExecutionEngine", "i_iastore");

	}
	Valor indice = topo->desempilhaOperando();
	if(!(indice.tipo == TipoDado::INTEIRO)){

		throw new Erro("Valor não é um int", "ExecutionEngine", "i_iastore");

	}
	Valor referArr = topo->desempilhaOperando();
	if(referArr.tipo != TipoDado::REFERENCIA){

		throw new Erro("Valor não é uma referencia", "ExecutionEngine", "i_iastore");
		
	} 
    else {
		topo->incrementaPC(2);
	}
	if(!(((Objeto*)referArr.dado)->ObterTipoObjeto() == TipoObjeto::ARRAY)){

		throw new Erro("objeto não é um array", "ExecutionEngine", "i_iastore");

	}

	array = (ObjetoArray*) referArr.dado;

	if (array == NULL) {

		throw new Erro("NullPointerException", "ExecutionEngine", "i_iastore");

	}

	if (indice.dado >= array->ObterTamanho() || indice.dado < 0) {

		throw new Erro("ArrayIndesxOutOfBoundException", "ExecutionEngine", "i_iastore");

	}
	
	if(op.tipo != array->TipoElementosDoArray()){

		throw new Erro("Operando não é do tipo dos elementos do array", "ExecutionEngine", "i_iastore");

	}	
	
	array->AlterarElementoDaPosicao(indice.dado, op);
	
	topo->incrementaPC(1);

}

void ExecutionEngine::i_lastore(){

	Frame *topo = runtimeDataArea->topoPilha();

	Valor valor = topo->desempilhaOperando();
	if(!(valor.tipo == TipoDado::LONG)){
							
		throw new Erro("Valor não é um long", "ExecutionEngine", "i_lastore");
						
	}
	Valor pad = topo->desempilhaOperando();
	if(!(pad.tipo == TipoDado::PREENCHIMENTO)){
							
		throw new Erro("Valor não é um pad", "ExecutionEngine", "i_lastore");
						
	}
	Valor indice = topo->desempilhaOperando();
	if(!(indice.tipo == TipoDado::INTEIRO)){
							
		throw new Erro("Valor não é um int", "ExecutionEngine", "i_lastore");
						
	}
	Valor referenciaArr = topo->desempilhaOperando();
	if(!(referenciaArr.tipo == TipoDado::REFERENCIA)){
							
		throw new Erro("Valor não é uma referencia", "ExecutionEngine", "i_lastore");
						
	}
	if(!(((Objeto*)referenciaArr.dado)->ObterTipoObjeto() == TipoObjeto::ARRAY)){
							
			throw new Erro("Valor não é uma referencia para array", "ExecutionEngine", "i_lastore");
						
		}

	ObjetoArray *array;
	array = (ObjetoArray *) referenciaArr.dado;

	if (array == NULL) {
		cerr << "NullPointerException" << endl;
		exit(1);
	}

	if (indice.dado >= array->ObterTamanho() || indice.dado < 0) {
		cerr << "ArrayIndexOutOfBoundsException" << endl;
		exit(2);
	}

	if(!(valor.tipo == array->TipoElementosDoArray())){
							
			throw new Erro("tipo errado", "ExecutionEngine", "i_lastore");
						
		}
	array->AlterarElementoDaPosicao(indice.dado, valor);

	topo->incrementaPC(1);

}

void ExecutionEngine::i_fastore(){

	Frame *topo = runtimeDataArea->topoPilha();
	ObjetoArray *array;

	Valor valor = topo->desempilhaOperando();
	if(!(valor.tipo == TipoDado::FLOAT)){
							
			throw new Erro("Valor não é um float", "ExecutionEngine", "i_fastore");
						
		}

	Valor indice = topo->desempilhaOperando();

	if(!(indice.tipo == TipoDado::INTEIRO)){
							
			throw new Erro("Valor não é um int", "ExecutionEngine", "i_fastore");
						
		}
	Valor referenciaArr = topo->desempilhaOperando();
	if(!(referenciaArr.tipo == TipoDado::REFERENCIA)){
							
			throw new Erro("Valor não é uma referencia", "ExecutionEngine", "i_fastore");
						
		}
	if(!(((Objeto*)referenciaArr.dado)->ObterTipoObjeto() == TipoObjeto::ARRAY)){
							
			throw new Erro("Valor não é uma referencia para array", "ExecutionEngine", "i_fastore");
						
		}

	array = (ObjetoArray *) referenciaArr.dado;

	if (array == NULL) {

		cerr << "NullPointerException" << endl;
		exit(1);

	}

	if (indice.dado >= array->ObterTamanho() || indice.dado < 0) {
		cerr << "ArrayIndexOutOfBoundsException" << endl;
		exit(2);
	}

	if(!(valor.tipo == array->TipoElementosDoArray())){
							
			throw new Erro("Valor não é do tipo dos elementos do array", "ExecutionEngine", "i_fastore");
						
		}
	array->AlterarElementoDaPosicao(indice.dado, valor);
	
	topo->incrementaPC(1);

}
void ExecutionEngine::i_dastore(){

	Frame *topo = runtimeDataArea->topoPilha();
	ObjetoArray *array;

	Valor valor = topo->desempilhaOperando();
	if(!(valor.tipo == TipoDado::DOUBLE)){
							
			throw new Erro("Valor não é um DOUBLE", "ExecutionEngine", "i_dastore");
						
		}

	Valor pad = topo->desempilhaOperando();
	if(!(pad.tipo == TipoDado::PREENCHIMENTO)){
							
		throw new Erro("Valor não é um pad", "ExecutionEngine", "i_dastore");
						
	}
	
	Valor indice = topo->desempilhaOperando();

	if(!(indice.tipo == TipoDado::INTEIRO)){
							
			throw new Erro("Valor não é um inteiro", "ExecutionEngine", "i_dastore");
						
		}

	Valor referenciaArr = topo->desempilhaOperando();
	if(!(referenciaArr.tipo == TipoDado::REFERENCIA)){
							
			throw new Erro("Valor não é uma referencia", "ExecutionEngine", "i_dastore");
						
		}

	if(!(((Objeto*)referenciaArr.dado)->ObterTipoObjeto() == TipoObjeto::ARRAY)){
							
			throw new Erro("Valor não é uma referencia para array", "ExecutionEngine", "i_dastore");
						
		}

	array = (ObjetoArray *) referenciaArr.dado;

	if (array == NULL) {

		cerr << "NullPointerException" << endl;
		exit(1);

	}

	if (indice.dado >= array->ObterTamanho() || indice.dado < 0) {
		cerr << "ArrayIndexOutOfBoundsException" << endl;
		exit(2);
	}

	if(!(valor.tipo == array->TipoElementosDoArray())){
							
			throw new Erro("Valor não é do tipo dos elementos do array", "ExecutionEngine", "i_dastore");
						
		}
	array->AlterarElementoDaPosicao(indice.dado, valor);
	
	topo->incrementaPC(1);
}

void ExecutionEngine::i_aastore(){

	Frame *topo = runtimeDataArea->topoPilha();
	ObjetoArray *array;

	Valor valor = topo->desempilhaOperando();
	if(!(valor.tipo == TipoDado::REFERENCIA)){
							
			throw new Erro("Valor não é uma referencia", "ExecutionEngine", "i_aastore");
						
		}

	Valor indice = topo->desempilhaOperando();

	if(!(indice.tipo == TipoDado::INTEIRO)){
							
			throw new Erro("Valor não é um int", "ExecutionEngine", "i_aastore");
						
		}
	Valor referenciaArr = topo->desempilhaOperando();
	if(!(referenciaArr.tipo == TipoDado::REFERENCIA)){
							
			throw new Erro("Valor não é uma referencia", "ExecutionEngine", "i_aastore");
						
		}
	if(!(((Objeto*)referenciaArr.dado)->ObterTipoObjeto() == TipoObjeto::ARRAY)){
							
			throw new Erro("Valor não é uma referencia para array", "ExecutionEngine", "i_aastore");
						
		}

	array = (ObjetoArray *) referenciaArr.dado;

	if (array == NULL) {

		cerr << "NullPointerException" << endl;
		exit(1);

	}

	if (indice.dado >= array->ObterTamanho() || indice.dado < 0) {
		cerr << "ArrayIndexOutOfBoundsException" << endl;
		exit(2);
	}

	if(!(valor.tipo == array->TipoElementosDoArray())){
							
			throw new Erro("Valor não é do tipo dos elementos do array", "ExecutionEngine", "i_aastore");
						
		}
	array->AlterarElementoDaPosicao(indice.dado, valor);
	
	topo->incrementaPC(1);
}
void ExecutionEngine::i_bastore(){

	Frame *topo = runtimeDataArea->topoPilha();
	ObjetoArray *array;

	Valor valor = topo->desempilhaOperando();
	if(!(valor.tipo == TipoDado::INTEIRO)){
							
			throw new Erro("Valor não é um INTEIRO", "ExecutionEngine", "i_bastore");
						
		}

	Valor indice = topo->desempilhaOperando();

	if(!(indice.tipo == TipoDado::INTEIRO)){
							
			throw new Erro("indice não é um int", "ExecutionEngine", "i_bastore");
						
		}
	Valor referenciaArr = topo->desempilhaOperando();
	if(!(referenciaArr.tipo == TipoDado::REFERENCIA)){
							
			throw new Erro("Valor não é uma referencia", "ExecutionEngine", "i_bastore");
						
		}
	if(!(((Objeto*)referenciaArr.dado)->ObterTipoObjeto() == TipoObjeto::ARRAY)){
							
			throw new Erro("Valor não é uma referencia para array", "ExecutionEngine", "i_bastore");
						
		}

	array = (ObjetoArray *) referenciaArr.dado;

	if (array == NULL) {

		cerr << "NullPointerException" << endl;
		exit(1);

	}

	if (indice.dado >= array->ObterTamanho() || indice.dado < 0) {
		cerr << "ArrayIndexOutOfBoundsException" << endl;
		exit(2);
	}

	if (array->TipoElementosDoArray() == TipoDado::BOOLEANO) {

		valor.dado = (valor.dado != 0) ? true : false;
		valor.tipo = TipoDado::BOOLEANO;

	} 
    else {

		valor.dado = (uint8_t) valor.dado;
		valor.tipo = TipoDado::BYTE;

	}
	
	array->AlterarElementoDaPosicao(indice.dado, valor);
	topo->incrementaPC(1);

}

void ExecutionEngine::i_castore(){

	Frame *topo = runtimeDataArea->topoPilha();
	ObjetoArray *array;

	Valor valor = topo->desempilhaOperando();
	if(!(valor.tipo == TipoDado::INTEIRO)){
							
			throw new Erro("Valor não é um INTEIRO", "ExecutionEngine", "i_castore");
						
		}

	Valor indice = topo->desempilhaOperando();

	if(!(indice.tipo == TipoDado::INTEIRO)){
							
			throw new Erro("indice não é um int", "ExecutionEngine", "i_castore");
						
		}
	Valor referenciaArr = topo->desempilhaOperando();
	if(!(referenciaArr.tipo == TipoDado::REFERENCIA)){
							
			throw new Erro("Valor não é uma referencia", "ExecutionEngine", "i_castore");
						
		}
	if(!(((Objeto*)referenciaArr.dado)->ObterTipoObjeto() == TipoObjeto::ARRAY)){
							
			throw new Erro("Valor não é uma referencia para array", "ExecutionEngine", "i_castore");
						
		}

	array = (ObjetoArray *) referenciaArr.dado;

	if (array == NULL) {

		cerr << "NullPointerException" << endl;
		exit(1);

	}

	if (indice.dado >= array->ObterTamanho() || indice.dado < 0) {
		cerr << "ArrayIndexOutOfBoundsException" << endl;
		exit(2);
	}
	valor.dado = (uint8_t) valor.dado;
	valor.tipo = TipoDado::CHAR;
	
	array->AlterarElementoDaPosicao(indice.dado, valor);
	topo->incrementaPC(1);

}
void ExecutionEngine::i_sastore(){

	Frame *topo = runtimeDataArea->topoPilha();
	ObjetoArray *array;

	Valor valor = topo->desempilhaOperando();
	if(!(valor.tipo == TipoDado::INTEIRO)){
							
			throw new Erro("Valor não é um INTEIRO", "ExecutionEngine", "i_sastore");
						
		}

	Valor indice = topo->desempilhaOperando();

	if(!(indice.tipo == TipoDado::INTEIRO)){
							
			throw new Erro("indice não é um int", "ExecutionEngine", "i_sastore");
						
		}
	Valor referenciaArr = topo->desempilhaOperando();
	if(!(referenciaArr.tipo == TipoDado::REFERENCIA)){
							
			throw new Erro("Valor não é uma referencia", "ExecutionEngine", "i_sastore");
						
		}
	if(!(((Objeto*)referenciaArr.dado)->ObterTipoObjeto() == TipoObjeto::ARRAY)){
							
			throw new Erro("Valor não é uma referencia para array", "ExecutionEngine", "i_sastore");
						
		}

	array = (ObjetoArray *) referenciaArr.dado;

	if (array == NULL) {

		cerr << "NullPointerException" << endl;
		exit(1);

	}

	if (indice.dado >= array->ObterTamanho() || indice.dado < 0) {
		cerr << "ArrayIndexOutOfBoundsException" << endl;
		exit(2);
	}

	valor.dado = (int16_t) valor.dado;
	valor.tipo = TipoDado::SHORT;
	array->AlterarElementoDaPosicao(indice.dado, valor);
	
	topo->incrementaPC(1);

}
void ExecutionEngine::i_pop(){

	Frame *topo = runtimeDataArea->topoPilha();
	Valor valor = topo->desempilhaOperando();
	if(!(valor.tipo != TipoDado::LONG)){
							
			throw new Erro("Valor nao pode ser um long", "ExecutionEngine", "i_pop");
						
		}

	if(!(valor.tipo != TipoDado::DOUBLE)){
							
			throw new Erro("Valor nçao pode ser double", "ExecutionEngine", "i_pop");
						
		}

	topo->incrementaPC(1);
}
void ExecutionEngine::i_pop2(){

	Frame *topo = runtimeDataArea->topoPilha();
	topo->desempilhaOperando();
	topo->desempilhaOperando();

	topo->incrementaPC(1);

}
void ExecutionEngine::i_dup(){
	Frame *topoDoFrame = runtimeDataArea->topoPilha();

	Valor valor = topoDoFrame->desempilhaOperando();
	if ((valor.tipo == TipoDado::LONG) || (valor.tipo == TipoDado::DOUBLE))
		throw new Erro("Esperado tipo diferente de long ou double em dup", "ExecutionEngine", "i_dup");

	topoDoFrame->empilharOperando(valor);
	topoDoFrame->empilharOperando(valor);

	topoDoFrame->incrementaPC(1);
}
void ExecutionEngine::i_dup_x1(){
	Frame *topoDoFrame = runtimeDataArea->topoPilha();

	Valor valor_1 = topoDoFrame->desempilhaOperando();
	
	if ((valor_1.tipo == TipoDado::LONG) || (valor_1.tipo == TipoDado::DOUBLE))
		throw new Erro("Esperado tipo diferente de long ou double em dup_x1","ExecutionEngine", "i_dup_x1");

	Valor valor_2 = topoDoFrame->desempilhaOperando();
	
	if ((valor_2.tipo == TipoDado::LONG) || (valor_2.tipo == TipoDado::DOUBLE))
		throw new Erro("Esperado tipo diferente de long ou double em dup_x1", "ExecutionEngine", "i_dup_x1");

	topoDoFrame->empilharOperando(valor_1);
	topoDoFrame->empilharOperando(valor_2);
	topoDoFrame->empilharOperando(valor_1);

	topoDoFrame->incrementaPC(1);
}
void ExecutionEngine::i_dup_x2(){
	Frame *topoDoFrame = runtimeDataArea->topoPilha();

	Valor valor_1 = topoDoFrame->desempilhaOperando();
	
	if ((valor_1.tipo == TipoDado::LONG) || (valor_1.tipo == TipoDado::DOUBLE))
		throw new Erro("Esperado tipo diferente de long ou double em dup_x2","ExecutionEngine", "i_dup_x2");

	Valor valor_2 = topoDoFrame->desempilhaOperando();

	Valor valor_3 = topoDoFrame->desempilhaOperando();
	
	if ((valor_3.tipo == TipoDado::LONG) || (valor_3.tipo == TipoDado::DOUBLE))
		throw new Erro("Esperado tipo diferente de long ou double em dup_x2","ExecutionEngine", "i_dup_x2");


	topoDoFrame->empilharOperando(valor_1);
	topoDoFrame->empilharOperando(valor_3);
	topoDoFrame->empilharOperando(valor_2);
	topoDoFrame->empilharOperando(valor_1);

	topoDoFrame->incrementaPC(1);
}
void ExecutionEngine::i_dup2(){
	Frame *topoDoFrame = runtimeDataArea->topoPilha();

	Valor valor_1 = topoDoFrame->desempilhaOperando();
	
	if ((valor_1.tipo == TipoDado::LONG) || (valor_1.tipo == TipoDado::DOUBLE))
		throw new Erro("Esperado tipo diferente de long ou double em dup2","ExecutionEngine", "i_dup2");

	Valor valor_2 = topoDoFrame->desempilhaOperando();
	
	if ((valor_2.tipo == TipoDado::LONG) || (valor_2.tipo == TipoDado::DOUBLE))
		throw new Erro("Esperado tipo diferente de long ou double em dup2","ExecutionEngine", "i_dup2");

	topoDoFrame->empilharOperando(valor_2);
	topoDoFrame->empilharOperando(valor_1);
	topoDoFrame->empilharOperando(valor_2);
	topoDoFrame->empilharOperando(valor_1);

	topoDoFrame->incrementaPC(1);
}
void ExecutionEngine::i_dup2_x1(){
	Frame *topoDoFrame = runtimeDataArea->topoPilha();

	Valor valor_1 = topoDoFrame->desempilhaOperando();
	Valor valor_2 = topoDoFrame->desempilhaOperando();
	
	if ((valor_2.tipo == TipoDado::LONG) || (valor_2.tipo == TipoDado::DOUBLE))
		throw new Erro("Esperado tipo diferente de long ou double em dup2_x1","ExecutionEngine", "i_dup2_x1");


	Valor valor_3 = topoDoFrame->desempilhaOperando();
	
	if ((valor_3.tipo == TipoDado::LONG) || (valor_3.tipo == TipoDado::DOUBLE))
		throw new Erro("Esperado tipo diferente de long ou double em dup2_x1", "ExecutionEngine", "i_dup2_x1");

	topoDoFrame->empilharOperando(valor_2);
	topoDoFrame->empilharOperando(valor_1);
	topoDoFrame->empilharOperando(valor_3);
	topoDoFrame->empilharOperando(valor_2);
	topoDoFrame->empilharOperando(valor_1);

	topoDoFrame->incrementaPC(1);
}
void ExecutionEngine::i_dup2_x2(){
	Frame *topoDoFrame = runtimeDataArea->topoPilha();

	Valor valor_1 = topoDoFrame->desempilhaOperando();
	Valor valor_2 = topoDoFrame->desempilhaOperando();
	Valor valor_3 = topoDoFrame->desempilhaOperando();
	Valor valor_4 = topoDoFrame->desempilhaOperando();

	if ((valor_2.tipo == TipoDado::LONG) || (valor_2.tipo == TipoDado::DOUBLE))
		throw new Erro("Esperado tipo diferente de long ou double em dup2_x2", "ExecutionEngine", "i_dup2_x2");

	if ((valor_4.tipo == TipoDado::LONG) || (valor_4.tipo == TipoDado::DOUBLE))
		throw new Erro("Esperado tipo diferente de long ou double em dup2_x2", "ExecutionEngine", "i_dup2_x2");

	topoDoFrame->empilharOperando(valor_2);
	topoDoFrame->empilharOperando(valor_1);
	topoDoFrame->empilharOperando(valor_4);
	topoDoFrame->empilharOperando(valor_3);
	topoDoFrame->empilharOperando(valor_2);
	topoDoFrame->empilharOperando(valor_1);

	topoDoFrame->incrementaPC(1);

}
void ExecutionEngine::i_swap(){
    
    Frame *topo = runtimeDataArea->topoPilha();

	Valor op_1 = topo->desempilhaOperando();
	Valor op_2 = topo->desempilhaOperando();

	if(op_1.tipo == TipoDado::LONG || op_1.tipo == TipoDado::DOUBLE){

		throw new Erro("o operador 1 não pode ser um long nem double", "ExecutionEngine", "i_swap");
						
		}
    if(op_2.tipo == TipoDado::LONG || op_2.tipo == TipoDado::DOUBLE){

		throw new Erro("o operador 1 não pode ser um long nem double", "ExecutionEngine", "i_swap");
						
		}

	topo->empilharOperando(op_1);
	topo->empilharOperando(op_2);

	topo->incrementaPC(1);
}
void ExecutionEngine::i_iadd(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	Valor valor1 = toppilha->desempilhaOperando();

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

	if(!((valor2.tipo == TipoDado::LONG) || (valor1.tipo == TipoDado::LONG))){
		throw new Erro("Os operandos devem ser um long","ExecutionEngine","i_ldiv");
	}

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
	
	int32_t num;
	memcpy(&num,&valor.dado,4);
	num= ((num & 0x80000000)^0x80000000)|(num & 0x7FFFFFFF);
	
	memcpy(&valor.dado,&num,4);
	
	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_dneg(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor = toppilha->desempilhaOperando();
	
	double num;
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
	
	int32_t num1, num2;
	memcpy(&num1,&valor1.dado,4);
	memcpy(&num2,&valor2.dado,4);
	
	num2 = 0x1f & num2;
	num1 = num1 << num2;
	memcpy(&valor1.dado,&num1,4);
	
	toppilha->empilharOperando(valor1);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
//shiftleft long
void ExecutionEngine::i_lshl(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	//valor 1 deve ser long e valor 2 deve ser int
	Valor valor2 = toppilha->desempilhaOperando();
	Valor valor1 = toppilha->desempilhaOperando();
	
	if(!(valor2.tipo == TipoDado::INTEIRO)){

		throw new Erro("O segundo operando deve ser um inteiro.","ExecutionEngine","i_ldiv");

	}
	if(!(valor1.tipo == TipoDado::LONG)){

		throw new Erro("O segundo operando deve ser um LONG.","ExecutionEngine","i_ldiv");

	}
	int64_t num1, num2;

	memcpy(&num1,&valor1.dado,8);
	memcpy(&num2,&valor2.dado,8);
	
	num2 = 0x3f & num2;
	num1 = num1 << num2;
	memcpy(&valor1.dado, &num1,8);
	
	toppilha->empilharOperando(valor1);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_ishr(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	Valor valor1 = toppilha->desempilhaOperando();
	
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
	
	int64_t num1, num2;
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
	
	uint32_t num1, num2;
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
	
	uint64_t num1, num2;
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
	
	int64_t num1, num2;
	memcpy(&num1,&valor1.dado,8);
	memcpy(&num2,&valor2.dado,8);
	
	num1 = num1 ^ num2;
	memcpy(&valor1.dado,&num1,8);
	
	toppilha->empilharOperando(valor1);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_iinc(){ //testar
	Frame *toppilha = runtimeDataArea->topoPilha();

	uint8_t *code = toppilha->getCode();
	uint8_t index = 0;

	if (isWide) {
		index = (code[1] << 8) | code[2];
	} 
    else {
		index = index + code[1];
	}

	Valor variavelLocal = toppilha->getValorVariavelLocal(index);

	int32_t i;
    if (isWide) {
        uint16_t incremento = (code[3] << 8) | code[4];
        i = (int32_t) (int16_t) incremento;
    } else {
        i = (int32_t) (int8_t) code[2];
    }
    variavelLocal.dado = variavelLocal.dado + i; 

	toppilha->mudarVariavelLocal(variavelLocal, index);
	
	if(isWide)
		runtimeDataArea->topoPilha()->incrementaPC(5);
	else
		runtimeDataArea->topoPilha()->incrementaPC(3);

	isWide = false;	

}
void ExecutionEngine::i_i2l(){
	Frame *toppilha = runtimeDataArea->topoPilha();
#ifdef DEBUG_EE
	puts("Olar, i2l 0");
#endif
	Valor valor1 = toppilha->desempilhaOperando();
	
	Valor valor2;
	valor2.tipo = TipoDado::LONG;
	Valor padding;
	padding.tipo = TipoDado::PREENCHIMENTO;
	toppilha->empilharOperando(padding);
	//troca o int pra 64?
	int32_t num1;
	int64_t num2;
	
	memcpy(&num1,&valor1.dado,4);
	num2 = (int64_t) num1;
	memcpy(&valor2.dado,&num2,8);
	
	toppilha->empilharOperando(valor2);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
//converte de int para float
void ExecutionEngine::i_i2f(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor1 = toppilha->desempilhaOperando();

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
	
	Valor valor2;
	valor2.tipo = TipoDado::DOUBLE;
	Valor padding;
	padding.tipo = TipoDado::PREENCHIMENTO;
	toppilha->empilharOperando(padding);
	
	int32_t num1;
	double num2;
	
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
	
	Valor valor2;
	valor2.tipo = TipoDado::INTEIRO;
	
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
	
	Valor valor2;
	valor2.tipo = TipoDado::DOUBLE;
	
	int64_t num1;
	double num2;
	
	memcpy(&num1,&valor1.dado,8);
	num2 = (double) num1;
	memcpy(&valor2.dado,&num2,8);
	
	toppilha->empilharOperando(valor2);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_f2i(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor1 = toppilha->desempilhaOperando();
	
	Valor valor2;
	valor2.tipo = TipoDado::INTEIRO;
	
	float num1;
	int num2;
	
	memcpy(&num1,&valor1.dado,4);
	num2 = (int32_t) num1;
	memcpy(&valor2.dado,&num2,4);
	
	toppilha->empilharOperando(valor2);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_f2l(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor1 = toppilha->desempilhaOperando();
	
	Valor valor2;
	valor2.tipo = TipoDado::LONG;
	Valor padding;
	padding.tipo = TipoDado::PREENCHIMENTO;
	toppilha->empilharOperando(padding);
	
	float num1;
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

	Valor valor2;
	valor2.tipo = TipoDado::DOUBLE;
	Valor padding;
	padding.tipo = TipoDado::PREENCHIMENTO;
	toppilha->empilharOperando(padding);
	
	float num1;
	double num2;
	
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
	
	Valor valor2;
	valor2.tipo = TipoDado::INTEIRO;
	
	double num1;
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
//converte de inteiro para byte
void ExecutionEngine::i_i2b(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor1 = toppilha->desempilhaOperando();
	
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
void ExecutionEngine::i_i2c(){ //da segfault
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor = toppilha->desempilhaOperando();
	
	int8_t num2;
	memcpy(&num2,&(valor.dado),1);
	int64_t num1=num2; 
	memcpy(&(valor.dado),&num1,8);
	valor.tipo= CHAR;
	
	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
//converte de int para short
void ExecutionEngine::i_i2s(){ 
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor1 = toppilha->desempilhaOperando();
	
	Valor valor2;
	valor2.tipo = TipoDado::SHORT;
	
	int32_t num1=0; 
	int16_t num2=0;
	
	memcpy(&num1,&valor1.dado,4);
	num2 = (int16_t) num1;
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
	
	int64_t num1, num2;
	int32_t num3;
	memcpy(&num1,&valor1.dado,8);
	memcpy(&num2,&valor2.dado,8);
	
	Valor resultado;
	resultado.tipo = TipoDado::INTEIRO;
	
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
	
	float num1, num2;
	int32_t num3;
	memcpy(&num1,&valor1.dado,4);
	memcpy(&num2,&valor2.dado,4);
	
	Valor resultado;
	resultado.tipo = TipoDado::INTEIRO;
	
	if (isnan(num1) || isnan(num2)) {
		num3 = -1;
	} 
	else if (num1 > num2) {
		num3 = 1;
	}
	 else if (num1 == num2) {
		num3 = 0;
	}
	 else {
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
	
	float num1, num2;
	int32_t num3;
	memcpy(&num1,&valor1.dado,4);
	memcpy(&num2,&valor2.dado,4);
	
	Valor resultado;
	resultado.tipo = TipoDado::INTEIRO;
	
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
	
	int64_t num1, num2;
	int32_t num3;
	memcpy(&num1,&valor1.dado,8);
	memcpy(&num2,&valor2.dado,8);
	
	Valor resultado;
	resultado.tipo = TipoDado::INTEIRO;
	
	if (isnan(num1) || isnan(num2)) {
		num3 = -1;
	}
	 else if (num1 > num2) {
		num3 = 1;
	}
	 else if (num1 == num2) {
		num3 = 0;
	}
	 else {
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
	

	int64_t num1, num2;
	int32_t num3;
	memcpy(&num1,&valor1.dado,8);
	memcpy(&num2,&valor2.dado,8);
	
	Valor resultado;
	resultado.tipo = TipoDado::INTEIRO;
	
	if (isnan(num1) || isnan(num2)) {
		num3 = 1;
	} 
	else if (num1 > num2) {
		num3 = 1;
	}
	 else if (num1 == num2) {
		num3 = 0;
	} 
	else {
		num3 = -1;
	}
	memcpy(&resultado.dado,&num3,4);
	
	toppilha->empilharOperando(resultado);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_ifeq(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor = toppilha->desempilhaOperando();
	
	int32_t num;
	memcpy(&num,&valor.dado,4);
	
	if (num == 0) {
		uint8_t *code = toppilha->getCode();
		uint8_t byte1 = code[1];
		uint8_t byte2 = code[2];
		uint16_t offsetPC = (byte1 << 8) | byte2;
		runtimeDataArea->topoPilha()->incrementaPC(offsetPC);
	} 
		 else {

		runtimeDataArea->topoPilha()->incrementaPC(3);

	}
}
void ExecutionEngine::i_ifne(){

	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor = toppilha->desempilhaOperando();
	
	int32_t num;
	memcpy(&num,&valor.dado,4);
	
	if (num != 0) {

		uint8_t *code = toppilha->getCode();
		uint8_t byte1 = code[1];
		uint8_t byte2 = code[2];
		uint16_t offsetPC = (byte1 << 8) | byte2;
		runtimeDataArea->topoPilha()->incrementaPC(offsetPC);

	} 
		else {

		runtimeDataArea->topoPilha()->incrementaPC(3);

	}
}
void ExecutionEngine::i_iflt(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor = toppilha->desempilhaOperando();
	
	int32_t num;
	memcpy(&num,&valor.dado,4);
	
	if (num < 0) {

		uint8_t *code = toppilha->getCode();
		uint8_t byte1 = code[1];
		uint8_t byte2 = code[2];
		uint16_t offsetPC = (byte1 << 8) | byte2;
		runtimeDataArea->topoPilha()->incrementaPC(offsetPC);

	} 
		else {

		runtimeDataArea->topoPilha()->incrementaPC(3);

	}
}
void ExecutionEngine::i_ifge(){

	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor = toppilha->desempilhaOperando();
	
	int32_t num;
	memcpy(&num,&valor.dado,4);
	
	if (num >= 0) {
		uint8_t *code = toppilha->getCode();
		uint8_t byte1 = code[1];
		uint8_t byte2 = code[2];
		uint16_t offsetPC = (byte1 << 8) | byte2;
		runtimeDataArea->topoPilha()->incrementaPC(offsetPC);
	} 
		 else {

		runtimeDataArea->topoPilha()->incrementaPC(3);

	}
}
void ExecutionEngine::i_ifgt(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor = toppilha->desempilhaOperando();
	
	int32_t num;
	memcpy(&num,&valor.dado,4);
	
	if (num > 0) {

		uint8_t *code = toppilha->getCode();
		uint8_t byte1 = code[1];
		uint8_t byte2 = code[2];
		uint16_t offsetPC = (byte1 << 8) | byte2;
		runtimeDataArea->topoPilha()->incrementaPC(offsetPC);

	} 
	else {

		runtimeDataArea->topoPilha()->incrementaPC(3);

	}
}

void ExecutionEngine::i_ifle(){

	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor = toppilha->desempilhaOperando();
	
	int32_t num;
	memcpy(&num,&valor.dado,4);
	
	if (num <= 0) {

		uint8_t *code = toppilha->getCode();
		uint8_t byte1 = code[1];
		uint8_t byte2 = code[2];
		uint16_t offsetPC = (byte1 << 8) | byte2;
		runtimeDataArea->topoPilha()->incrementaPC(offsetPC);

	} 
	else {

		runtimeDataArea->topoPilha()->incrementaPC(3);

	}
}
void ExecutionEngine::i_if_icmpeq(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	Valor valor1 = toppilha->desempilhaOperando();
			
	int32_t num1, num2;
	memcpy(&num1,&valor1.dado,4);
	memcpy(&num2,&valor2.dado,4);
	
	if (num1 == num2) {

		uint8_t *code = toppilha->getCode();
		uint8_t byte1 = code[1];
		uint8_t byte2 = code[2];
		uint16_t offsetPC = (byte1 << 8) | byte2;
		runtimeDataArea->topoPilha()->incrementaPC(offsetPC);

	}
	 else {

		runtimeDataArea->topoPilha()->incrementaPC(3);

	}
}
void ExecutionEngine::i_if_icmpne(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	Valor valor1 = toppilha->desempilhaOperando();

	int32_t num1, num2;
	memcpy(&num1,&valor1.dado,4);
	memcpy(&num2,&valor2.dado,4);
	
	if (num1 != num2) {
		uint8_t *code = toppilha->getCode();
		uint8_t byte1 = code[1];
		uint8_t byte2 = code[2];
		uint16_t offsetPC = (byte1 << 8) | byte2;
		runtimeDataArea->topoPilha()->incrementaPC(offsetPC);
	} 
		else{

		runtimeDataArea->topoPilha()->incrementaPC(3);

	}
}
void ExecutionEngine::i_if_icmplt(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	Valor valor1 = toppilha->desempilhaOperando();
	
	int32_t num1, num2;
	memcpy(&num1,&valor1.dado,4);
	memcpy(&num2,&valor2.dado,4);
	
	if (num1 < num2) {

		uint8_t *code = toppilha->getCode();
		uint8_t byte1 = code[1];
		uint8_t byte2 = code[2];
		int16_t offsetPC = (byte1 << 8) | byte2;
		runtimeDataArea->topoPilha()->incrementaPC(offsetPC);

	} 
		else {

		runtimeDataArea->topoPilha()->incrementaPC(3);

	}
}
void ExecutionEngine::i_if_icmpge(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	Valor valor1 = toppilha->desempilhaOperando();
	
	int32_t num1, num2;
	memcpy(&num1,&valor1.dado,4);
	memcpy(&num2,&valor2.dado,4);
	
	if (num1 >= num2) {
		uint8_t *code = toppilha->getCode();
		uint8_t byte1 = code[1];
		uint8_t byte2 = code[2];
		int16_t offsetPC = (byte1 << 8) | byte2;
		runtimeDataArea->topoPilha()->incrementaPC(offsetPC);
	} else {
		runtimeDataArea->topoPilha()->incrementaPC(3);
	}
}
void ExecutionEngine::i_if_icmpgt(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	Valor valor1 = toppilha->desempilhaOperando();

	int32_t num1, num2;
	memcpy(&num1,&valor1.dado,4);
	memcpy(&num2,&valor2.dado,4);
	
	if (num1 > num2) {

		uint8_t *code = toppilha->getCode();
		uint8_t byte1 = code[1];
		uint8_t byte2 = code[2];
		int16_t offsetPC = (byte1 << 8) | byte2;
		runtimeDataArea->topoPilha()->incrementaPC(offsetPC);

	} 
	else {

		runtimeDataArea->topoPilha()->incrementaPC(3);

	}
}
void ExecutionEngine::i_if_icmple(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	Valor valor1 = toppilha->desempilhaOperando();
	
	int32_t num1, num2;
	memcpy(&num1,&valor1.dado,4);
	memcpy(&num2,&valor2.dado,4);
	
	if (num1 <= num2) {
		uint8_t *code = toppilha->getCode();
		uint8_t byte1 = code[1];
		uint8_t byte2 = code[2];
		int16_t offsetPC = (byte1 << 8) | byte2;
		runtimeDataArea->topoPilha()->incrementaPC(offsetPC);
	} else {
		runtimeDataArea->topoPilha()->incrementaPC(3);
	}
}
void ExecutionEngine::i_if_acmpeq(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	Valor valor1 = toppilha->desempilhaOperando();
	
	int64_t num1, num2;
	memcpy(&num1,&valor1.dado,sizeof(void*));
	memcpy(&num2,&valor2.dado,sizeof(void*));
	
	if (num1 == num2) {
		uint8_t *code = toppilha->getCode();
		uint8_t byte1 = code[1];
		uint8_t byte2 = code[2];
		int16_t offsetPC = (byte1 << 8) | byte2;
		runtimeDataArea->topoPilha()->incrementaPC(offsetPC);
	} else {
		runtimeDataArea->topoPilha()->incrementaPC(3);
	}
}
void ExecutionEngine::i_if_acmpne(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor valor2 = toppilha->desempilhaOperando();
	Valor valor1 = toppilha->desempilhaOperando();
	
	int64_t num1, num2;
	memcpy(&num1,&valor1.dado,sizeof(void*));
	memcpy(&num2,&valor2.dado,sizeof(void*));
	
	if (num1 != num2) {
		uint8_t *code = toppilha->getCode();
		uint8_t byte1 = code[1];
		uint8_t byte2 = code[2];
		int16_t offsetPC = (byte1 << 8) | byte2;
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
	int16_t offsetPC = (byte1 << 8) | byte2;
	runtimeDataArea->topoPilha()->incrementaPC(offsetPC);
}
void ExecutionEngine::i_jsr(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	uint8_t *code = toppilha->getCode();
	uint8_t byte1 = code[1];
	uint8_t byte2 = code[2];
	int16_t offsetPC = (byte1 << 8) | byte2;
	
	Valor enderecoRetorno;
	enderecoRetorno.tipo = TipoDado::ENDERECO_DE_RETORNO;
	int64_t num;
	num = runtimeDataArea->topoPilha()->getPC() + 3;
	memcpy(&enderecoRetorno.dado,&num,sizeof(void*));
	
	toppilha->empilharOperando(enderecoRetorno);
	runtimeDataArea->topoPilha()->incrementaPC(offsetPC);
}
void ExecutionEngine::i_ret(){
	Frame *topoDaFrame = runtimeDataArea->topoPilha(); 
	
	uint8_t *code = topoDaFrame->getCode();
	
	uint8_t byte_1 = code[1]; //vai ser o index do vetor das variaveis local
	uint16_t index = (uint16_t) byte_1;

	if(isWide){
		uint8_t byte_2 = code[2];
		index = (byte_1 << 8) | byte_2;
	}
	if( !((int16_t)(topoDaFrame->tamanhoVetorVariaveis()) > index) ) //size of Local Variable
		throw new Erro("Nao eh maior que o indice","ExecutionEngine","i_ret");

	Valor valor = topoDaFrame->getValorVariavelLocal(index);


	if(valor.tipo != TipoDado::ENDERECO_DE_RETORNO)
		throw new Erro("valor nao é endereco de retorno","ExecutionEngine","i_ret");


	topoDaFrame->mudarVariavelLocal(valor, index);

	topoDaFrame->alteraPC(valor.dado);
	isWide = false;
	return;
}
void ExecutionEngine::i_tableswitch()
{
	Frame *topoDaPilhaDeFrames= runtimeDataArea->topoPilha();
	uint8_t *instrucoes = topoDaPilhaDeFrames->getCode();
	uint8_t preenchimento= 4-(topoDaPilhaDeFrames->getPC()+1)%4;
	if(preenchimento == 4)
	{
		preenchimento = 0;
	}
	
	int32_t defaulti, low, high;
	memcpy(&defaulti, &(instrucoes[preenchimento+1]), 4);
	defaulti= InverterEndianess<int32_t>(defaulti);
	memcpy(&low, &(instrucoes[preenchimento+5]), 4);
	low= InverterEndianess<int32_t>(low);
	memcpy(&high, &(instrucoes[preenchimento+9]), 4);
	high= InverterEndianess<int32_t>(high);
	
	Valor valorChave= topoDaPilhaDeFrames->desempilhaOperando();
	if(valorChave.tipo != INTEIRO)
	{
		throw new Erro("Esperado valor do tipo INTEIRO", "ExecutionEngine", "i_tableswitch");
	}
	uint32_t indiceDeBase= preenchimento+13;
	int32_t chave, deslocamentos= high - low +1;
	memcpy(&chave, &(valorChave.dado), 4);
	bool achou= false;
	for(int cont =0; cont < deslocamentos; cont++)
	{
		if(chave == low)
		{
			int32_t deslocamento;
			deslocamento= (instrucoes[indiceDeBase] << 24) | (instrucoes[indiceDeBase+1] << 16) | (instrucoes[indiceDeBase+2] << 8) | instrucoes[indiceDeBase+3];
			topoDaPilhaDeFrames->incrementaPC(deslocamento);
			achou = true;
			break;
		}
		indiceDeBase+=4;
		low++;
	}
	if(!achou)
	{//apenas avança o pc o tamanho da instrucao
		topoDaPilhaDeFrames->incrementaPC(defaulti);
	}
}
void ExecutionEngine::i_lookupswitch()
{
	Frame *topoDaPilhaDeFrames= runtimeDataArea->topoPilha();
	uint8_t *instrucoes = topoDaPilhaDeFrames->getCode();
	uint8_t preenchimento= 4-(topoDaPilhaDeFrames->getPC()+1)%4;
	if(preenchimento == 4)
	{
		preenchimento = 0;
	}
	
	int32_t defaulti;
	memcpy(&defaulti, &(instrucoes[preenchimento+1]), 4);
	defaulti= InverterEndianess<int32_t> (defaulti);
	int32_t paresN;
	memcpy(&paresN, &(instrucoes[preenchimento+5]), 4);
	paresN= InverterEndianess<int32_t> (paresN);
	
	Valor valorChave= topoDaPilhaDeFrames->desempilhaOperando();
	if(valorChave.tipo != INTEIRO)
	{
		throw new Erro("Esperado valor do tipo INTEIRO", "ExecutionEngine", "i_lookupswitch");
	}
	
	uint32_t indiceDeBase= preenchimento+9;
	int32_t chave;
	memcpy(&chave, &(valorChave.dado), 4);
	bool achou= false;
	int32_t acerto, deslocamento;
	
	for(int cont =0 ; cont < paresN; cont++)
	{
		acerto= (instrucoes[indiceDeBase] << 24) | (instrucoes[indiceDeBase+1] << 16) |(instrucoes[indiceDeBase+2]) | instrucoes[indiceDeBase+3];
		if(acerto == chave)
		{
			deslocamento = (instrucoes[indiceDeBase+4] << 24) | (instrucoes[indiceDeBase+1+5] << 16) | (instrucoes[indiceDeBase+6]) | instrucoes[indiceDeBase+7];
			topoDaPilhaDeFrames->incrementaPC(deslocamento);
			achou = true;
			break;
		}
		indiceDeBase += 8;
	}
	if(!achou)
	{
		topoDaPilhaDeFrames->incrementaPC(defaulti);
	}
}
//aceita byte, bool e short
void ExecutionEngine::i_ireturn(){
	//desempinha a funcao e empilha o valor de retorno na nova frame
	Frame *topoDaFrame = runtimeDataArea->topoPilha();
	//valor deve ser inteiro
	Valor returnValor = topoDaFrame->desempilhaOperando();
	
	if (returnValor.tipo != TipoDado::INTEIRO)
		throw new Erro("Esperado tipo inteiro em ireturn");

	//testar
	runtimeDataArea->desempilharFrame();
	//so n destruí aqui o antigo mas deboas
	
	Frame *novoTopDoFrame = runtimeDataArea->topoPilha();
	novoTopDoFrame->empilharOperando(returnValor);

}
void ExecutionEngine::i_lreturn(){
	Frame *topoDaFrame = runtimeDataArea->topoPilha();
	//valor deve ser long
	Valor returnValor = topoDaFrame->desempilhaOperando();
	
	if (returnValor.tipo != TipoDado::LONG)
		throw new Erro("Esperado tipo inteiro em i_lreturn");

	
	runtimeDataArea->desempilharFrame();
	//so n destruí aqui o antigo mas deboas
	Frame *novoTopDoFrame = runtimeDataArea->topoPilha();
	Valor padd;
	padd.dado = TipoDado::PREENCHIMENTO;

	novoTopDoFrame->empilharOperando(padd);
	novoTopDoFrame->empilharOperando(returnValor);

}
void ExecutionEngine::i_freturn(){

	Frame *topoDaFrame = runtimeDataArea->topoPilha();
	//valor deve ser float
	Valor returnValor = topoDaFrame->desempilhaOperando();
	
	if (returnValor.tipo != TipoDado::FLOAT)
		throw new Erro("Esperado tipo inteiro em ireturn");	

	runtimeDataArea->desempilharFrame();

	Frame *novoTopDoFrame = runtimeDataArea->topoPilha();
	novoTopDoFrame->empilharOperando(returnValor);
}
void ExecutionEngine::i_dreturn(){
	Frame *topoDaFrame = runtimeDataArea->topoPilha();
	//valor deve ser double
	Valor returnValor = topoDaFrame->desempilhaOperando();

	if (returnValor.tipo != TipoDado::DOUBLE)
		throw new Erro("Esperado tipo inteiro em ireturn");

	//so n destruí aqui o antigo mas deboas
	runtimeDataArea->desempilharFrame();

	Frame *novoTopDoFrame = runtimeDataArea->topoPilha();
	Valor padd;
	padd.dado = TipoDado::PREENCHIMENTO;

	novoTopDoFrame->empilharOperando(padd);
	novoTopDoFrame->empilharOperando(returnValor);
}
void ExecutionEngine::i_areturn(){
	Frame *topoDaFrame = runtimeDataArea->topoPilha();
	//valor deve ser reference
	Valor returnValor = topoDaFrame->desempilhaOperando();

	if (returnValor.tipo != TipoDado::REFERENCIA)
		throw new Erro("Esperado tipo inteiro em areturn");

	runtimeDataArea->desempilharFrame();

	Frame *novoTopDoFrame = runtimeDataArea->topoPilha();
	novoTopDoFrame->empilharOperando(returnValor);
}
void ExecutionEngine::i_return(){
	//usa no mainvazia
	runtimeDataArea->desempilharFrame();

}

/*	*	*	*	*	*	*	*	*	*	*	*	*	*
get a static field value of a class, where the 		*
field is identified by field reference in the 		*
constant pool index (indexbyte1 << 8 + indexbyte2)	*
*	*	*	*	*	*	*	*	*	*	*	*	*	*/
void ExecutionEngine::i_getstatic() {
	//usa no helloworld
	
	#ifdef DEBUG_EE
	cout<< "ExecutionEngine::i_getstatic" << endl;
	#endif
	
	Frame *toppilha = runtimeDataArea->topoPilha();
	
	#ifdef DEBUG_EE_GET_STATIC
	cout<< "ExecutionEngine::i_getstatic1" << endl;
	#endif
	
	vector<cp_info*> constantPool;
	
	JavaClass *classe= (toppilha->getObjeto()== NULL )? toppilha->ObterJavaClass(): ((ObjetoInstancia*)toppilha->getObjeto())->ObterJavaClass();
	

	constantPool = classe->getConstantPool();
	
	#ifdef DEBUG_EE_GET_STATIC
	cout<< "ExecutionEngine::i_getstatic2" << endl;
	#endif
	
	uint8_t *code = toppilha->getCode();
	
	#ifdef DEBUG_EE_GET_STATIC
	cout<< "ExecutionEngine::i_getstatic3" << endl;
	#endif

	//argumentos da instrucao
	uint8_t byte1 = code[1];
	uint8_t byte2 = code[2];
	
	uint16_t campoIndex = (byte1 << 8) | byte2;
	
	#ifdef DEBUG_EE_GET_STATIC
	cout<< "ExecutionEngine::i_getstatic4" << endl;
	#endif

	//consulta a field. percorre os fields do java
	CONSTANT_Fieldref_info *fieldRef = (CONSTANT_Fieldref_info*) constantPool[campoIndex-1];

	#ifdef DEBUG_EE_GET_STATIC
	cout<< "ExecutionEngine::i_getstatic5" << endl;
	#endif
	
	string className = classe->getUTF8(fieldRef->GetClassIndex());
	
	#ifdef DEBUG_EE_GET_STATIC
	cout<< "ExecutionEngine::i_getstatic6" << endl;
	#endif
	
	CONSTANT_NameAndType_info *campoNameAndtipoCP = (CONSTANT_NameAndType_info *)constantPool[fieldRef->GetNameAndTypeIndex()-1];
	
	#ifdef DEBUG_EE_GET_STATIC
	cout<< "ExecutionEngine::i_getstatic7" << endl;
	#endif
	
	string campoName = classe->getUTF8(campoNameAndtipoCP->GetNameIndex()); //pega o nome da field ou campo
	string campoDescricao = classe->getUTF8(campoNameAndtipoCP->GetDescriptorIndex()); //pega o field descriptor

	#ifdef DEBUG_EE_GET_STATIC
	cout<< "ExecutionEngine::i_getstatic8" << endl;
	#endif
	
	if (campoDescricao == "Ljava/io/PrintStream;" && className == "java/lang/System" ) {
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
	
	//bolean, byte, short e int sao empilhados como int. long e double empilham o padding antes
/*	switch (valorStatico.tipo) {
		case TipoDado::BOOLEANO:
		case TipoDado::BYTE:
		case TipoDado::SHORT:
		case TipoDado::INTEIRO:

			valorStatico.tipo = TipoDado::INTEIRO;
			break;

		case TipoDado::DOUBLE:
		case TipoDado::LONG:

			Valor preenchimento;
			preenchimento.tipo = PREENCHIMENTO;
			toppilha->empilharOperando(preenchimento);
			break;

		default://se for reference?
			cerr << "deu ruim" << endl;
			exit(0);
	}//fim switch valor estatico
*/

	if(valorStatico.tipo == DOUBLE || valorStatico.tipo == LONG)
	{
			Valor preenchimento;
			preenchimento.tipo = PREENCHIMENTO;
			toppilha->empilharOperando(preenchimento);
	}
	toppilha->empilharOperando(valorStatico);
	runtimeDataArea->topoPilha()->incrementaPC(3);

}

void ExecutionEngine::i_putstatic()
{
	Frame *topoDaPilhaDeFrames= runtimeDataArea->topoPilha();
	JavaClass *classe= topoDaPilhaDeFrames->ObterJavaClass();
	uint8_t *instrucoes= topoDaPilhaDeFrames->getCode();
	
	uint16_t indiceDoField;
	memcpy(&indiceDoField, &(instrucoes[1]), 2);
	indiceDoField= InverterEndianess<uint16_t>(indiceDoField);
	//verificando se estou acessando um elemento do tipo esperado na constant pool
	if(classe->getConstantPool()[indiceDoField-1]->GetTag() != CONSTANT_Fieldref)
	{
		throw new Erro("Esperado CONSTANT_Fieldref na constant pool", "ExecutionEngine", "i_putstatic");
	}
	//sendo válido, acesso o mesmo
	CONSTANT_Fieldref_info *cpCampo= (CONSTANT_Fieldref_info*)classe->getConstantPool()[indiceDoField-1];
	//verificando se estou acessando um elemento do tipo esperado na constant pool
	if(classe->getConstantPool()[cpCampo->GetNameAndTypeIndex()-1]->GetTag() != CONSTANT_NameAndType)
	{
		throw new Erro("Esperado CONSTANT_NameAndType na constant pool", "ExecutionEngine", "i_putstatic");
	}
	//sendo válido, acesso o mesmo
	CONSTANT_NameAndType_info *assinaturaDoCampo= (CONSTANT_NameAndType_info*)classe->getConstantPool()[cpCampo->GetNameAndTypeIndex()-1];
	//pegando o nome das coisas
	string nomeDaClasse = classe->getUTF8(cpCampo->GetClassIndex());
	string nomeDoField = classe->getUTF8(assinaturaDoCampo->GetNameIndex());
	string descritor = classe->getUTF8(assinaturaDoCampo->GetDescriptorIndex());
	
	//agora carreguemos a classe da qual queremos mexer no campo estático
	JavaClass *classeAlvo= runtimeDataArea->CarregarClasse(nomeDaClasse);
	//agora vamos buscar o field que queremos na hierarquia de classes
	
	while(classeAlvo != NULL)
	{
		if(!classeAlvo->FieldExiste(nomeDoField))//enquanto nao for a classe que tem o campo
		{
			if(classeAlvo->ObterSuperClasse() != 0)
			{
				string nomeDaClassePai= classeAlvo->getUTF8(classeAlvo->ObterSuperClasse());
				classeAlvo= runtimeDataArea->CarregarClasse(nomeDaClassePai);
			}
			else
			{
				classeAlvo= NULL;
			}
		}
		else//achamos o que queriamos
		{
			break;
		}
	}
	
	if(classeAlvo == NULL)
	{
		throw new Erro("NoSuchFieldError");
	}
	//verificando se teve alguma classe que pediu para rodar um clinit
	if(topoDaPilhaDeFrames != runtimeDataArea->topoPilha())
	{//se sim interrompe a execução da instrução sem alterar o pc para que os clinits inicializem os campos estaticos
		return;
	}
	//se chegou aqui está tudo de boas e podemos continuar
	Valor campo= topoDaPilhaDeFrames->desempilhaOperando();
	if(campo.tipo== LONG || campo.tipo == DOUBLE)
	{//retirar preenchimento
		topoDaPilhaDeFrames->desempilhaOperando();
	}
	switch(descritor[0])
	{//OBS: Aqui não estamos trdução de tipos citada aqui:https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.putstatic
	//estamos supondo que o javac nao fez merda
		case ('C'):
		{
			campo.tipo= CHAR;
			break;
		}
		case ('Z'):
		{
			campo.tipo= BOOLEANO;
			break;
		}
		case ('B'):
		{
			campo.tipo= BYTE;
			break;
		}
		case ('S'):
		{
			campo.tipo= SHORT;
		}
	}
	classeAlvo->ColocarValorNoField(nomeDoField, campo);
	topoDaPilhaDeFrames->incrementaPC(3);
}
void ExecutionEngine::i_getfield()
{
	Frame *topoDaPilhaDeFrames= runtimeDataArea->topoPilha();
	JavaClass *classe= topoDaPilhaDeFrames->ObterJavaClass();
	uint8_t *instrucoes= topoDaPilhaDeFrames->getCode();
	
	uint16_t indiceDoField;
	memcpy(&indiceDoField, &(instrucoes[1]), 2);
	indiceDoField= InverterEndianess<uint16_t>(indiceDoField);
	
	if(classe->getConstantPool()[indiceDoField-1]->GetTag() != CONSTANT_Fieldref)
	{
		throw new Erro("Esperado CONSTANT_Fieldref", "ExecutionEngine", "i_getfield");
	}
	CONSTANT_Fieldref_info *cpCampo= (CONSTANT_Fieldref_info*)classe->getConstantPool().at(indiceDoField-1);
	if(classe->getConstantPool().at(cpCampo->GetNameAndTypeIndex()-1)->GetTag() != CONSTANT_NameAndType)
	{
		throw new Erro("Esperado CONSTANT_NameAndType", "ExecutionEngine", "i_getfield");
	}
	CONSTANT_NameAndType_info *cpAssinatura= (CONSTANT_NameAndType_info*)classe->getConstantPool().at(cpCampo->GetNameAndTypeIndex()-1);
	
	string nomeDaClasse= classe->getUTF8(cpCampo->GetClassIndex());
	string nomeDoField= classe ->getUTF8(cpAssinatura->GetNameIndex());
	string descritorDoField= classe-> getUTF8(cpAssinatura->GetDescriptorIndex());
	
	Valor valorInstancia = topoDaPilhaDeFrames->desempilhaOperando();
	if(valorInstancia.tipo != REFERENCIA)
	{
		throw new Erro("Esperado valor do tipo referencia", "ExecutionEngine", "i_getfield");
	}
	if(((Objeto*)valorInstancia.dado)->ObterTipoObjeto() != INSTANCIA)
	{
		throw new Erro("Esperado instancia", "ExecutionEngine", "i_getfield");
	}
	
	ObjetoInstancia *instancia= (ObjetoInstancia*)valorInstancia.dado;
	
	if(!instancia->CampoExiste(nomeDoField))
	{
		throw new Erro("NoSuchFieldError");
	}
	
	Valor campo= instancia->ObterValorDoCampo(nomeDoField);
/*	if(campo.tipo == BOOLEANO)
	{
		
	}*/
	if(campo.tipo == LONG || campo.tipo == DOUBLE)
	{
		Valor preenchimento;
		preenchimento.tipo= PREENCHIMENTO;
		topoDaPilhaDeFrames->empilharOperando(preenchimento);
	}
	topoDaPilhaDeFrames->empilharOperando(campo);
	topoDaPilhaDeFrames-> incrementaPC(3);
}

void ExecutionEngine::i_putfield()
{
	Frame *topoDaPilhaDeFrames= runtimeDataArea->topoPilha();
	JavaClass *classe= topoDaPilhaDeFrames->ObterJavaClass();
	uint8_t *instrucoes= topoDaPilhaDeFrames->getCode();
	
	uint16_t indiceDoField;
	memcpy(&indiceDoField, &(instrucoes[1]), 2);
	indiceDoField= InverterEndianess<uint16_t>(indiceDoField);
	
	if(classe->getConstantPool()[indiceDoField-1]->GetTag() != CONSTANT_Fieldref)
	{
		throw new Erro("Esperado CONSTANT_Fieldref", "ExecutionEngine", "i_putfield");
	}
	CONSTANT_Fieldref_info *cpCampo= (CONSTANT_Fieldref_info*)classe->getConstantPool().at(indiceDoField-1);
	if(classe->getConstantPool().at(cpCampo->GetNameAndTypeIndex()-1)->GetTag() != CONSTANT_NameAndType)
	{
		throw new Erro("Esperado CONSTANT_NameAndType", "ExecutionEngine", "i_putfield");
	}
	CONSTANT_NameAndType_info *cpAssinatura= (CONSTANT_NameAndType_info*)classe->getConstantPool().at(cpCampo->GetNameAndTypeIndex()-1);
	
	string nomeDaClasse= classe->getUTF8(cpCampo->GetClassIndex());
	string nomeDoField= classe ->getUTF8(cpAssinatura->GetNameIndex());
	string descritorDoField= classe-> getUTF8(cpAssinatura->GetDescriptorIndex());

	Valor valorQueSeraInserido= topoDaPilhaDeFrames->desempilhaOperando();
	if(valorQueSeraInserido.tipo == LONG || valorQueSeraInserido.tipo == DOUBLE)
	{
		topoDaPilhaDeFrames->desempilhaOperando();
	}
	
	Valor valorInstancia= topoDaPilhaDeFrames->desempilhaOperando();
	if(valorInstancia.tipo != REFERENCIA)
	{
		throw new Erro("Esperado valor do tipo referencia", "ExecutionEngine", "i_putfield");
	}
	if(((Objeto*)valorInstancia.dado)->ObterTipoObjeto() != INSTANCIA)
	{
		throw new Erro("Esperado instancia", "ExecutionEngine", "i_putfield");
	}
	ObjetoInstancia *instancia= (ObjetoInstancia*)valorInstancia.dado;

	try
	{
		if(instancia->ObterValorDoCampo(nomeDoField).tipo != valorQueSeraInserido.tipo)
		{
			cout<< "WARNING! Vai colocar um valor de tipo diferente do que contém no campo \tTipoDoCampo= " << ObterStringTipo(instancia->ObterValorDoCampo(nomeDoField).tipo) << " \tTipoQueSeraInserido" << ObterStringTipo(valorQueSeraInserido.tipo) << endl;
		}
	}
	catch(Erro *err)
	{
		cout << "WARNING! CAMPO NAO EXISTE! \tNomeCampo: " << nomeDoField << " \t da classe: " << nomeDaClasse << endl;
	}

	
	instancia->ColocarValorNoCampo(nomeDoField, valorQueSeraInserido);
	
	topoDaPilhaDeFrames->incrementaPC(3);

}//fim metodo

void ExecutionEngine::i_invokevirtual()
{
	#ifdef DEBUG_EE_INVOKEVIRTUAL
		cout<< "ExecutionEngine::i_invokevirtual()" << endl;
	#endif
		Frame *topoDaPilha= runtimeDataArea->topoPilha();
	#ifdef DEBUG_EE_INVOKEVIRTUAL
		cout<< "ExecutionEngine::i_invokevirtual()1" << endl;
	#endif
		stack<Valor> pilhaDeOperandosDeReserva= topoDaPilha->retornaPilhaOperandos();
	#ifdef DEBUG_EE_INVOKEVIRTUAL
		cout<< "ExecutionEngine::i_invokevirtual()2" << endl;
	#endif
		uint8_t *instrucoes=topoDaPilha->getCode();
	#ifdef DEBUG_EE_INVOKEVIRTUAL
		cout<< "ExecutionEngine::i_invokevirtual()3" << endl;
	#endif
	uint16_t indiceMetodo;
	memcpy(&indiceMetodo, &(instrucoes[1]), 2);
	indiceMetodo= InverterEndianess<uint16_t>(indiceMetodo);
	JavaClass *javaClass= topoDaPilha->ObterJavaClass();
	#ifdef DEBUG_EE_INVOKEVIRTUAL
		cout<< "ExecutionEngine::i_invokevirtual()4" << endl;
	#endif
	if(javaClass->getConstantPool().at(indiceMetodo-1)->GetTag() != CONSTANT_Methodref)
	{
		throw new Erro("Esperado encontrar um CONSTANT_Methodref", "ExecutionEngine", "i_invokevirtual");
	}
#ifdef DEBUG_EE_INVOKEVIRTUAL
	cout<< "ExecutionEngine::i_invokevirtual()5" << endl;
#endif
	CONSTANT_Methodref_info *metodo= (CONSTANT_Methodref_info *)javaClass->getConstantPool().at(indiceMetodo-1);
#ifdef DEBUG_EE_INVOKEVIRTUAL
	cout<< "ExecutionEngine::i_invokevirtual()6" << endl;
#endif
	string nomeDaClasse= javaClass->getUTF8(metodo->GetClassIndex());
	if(javaClass->getConstantPool().at(metodo->GetNameAndTypeIndex()-1)->GetTag() != CONSTANT_NameAndType)
	{
		throw new Erro("Esperado encontrar um CONSTANT_NameAndType", "ExecutionEngine", "i_invokevirtual");
	}
	CONSTANT_NameAndType_info *assinaturaDoMetodo= (CONSTANT_NameAndType_info*) javaClass->getConstantPool().at(metodo->GetNameAndTypeIndex()-1);
	string nomeDoMetodo= javaClass->getUTF8(assinaturaDoMetodo->GetNameIndex());
	string descritorDoMetodo= javaClass->getUTF8(assinaturaDoMetodo->GetDescriptorIndex());
#ifdef DEBUG_EE_INVOKEVIRTUAL
	cout<< "ExecutionEngine::i_invokevirtual()7" << endl;
#endif
	
	if(nomeDaClasse.find("java/") != string::npos)
	{//Provavelmente estamos tratando de um print
		if(nomeDaClasse== "java/io/PrintStream" && (nomeDoMetodo == "print" || nomeDoMetodo == "println"))
		{
			if(descritorDoMetodo != "()V")
			{
#ifdef DEBUG_EE_INVOKEVIRTUAL
	cout<< "ExecutionEngine::i_invokevirtual()8" << endl;
#endif
				Valor valorQueSeraImpresso= topoDaPilha->desempilhaOperando();
#ifdef DEBUG_EE_INVOKEVIRTUAL
	cout<< "ExecutionEngine::i_invokevirtual()9" << endl;
#endif
				switch(valorQueSeraImpresso.tipo)
				{
					case(BOOLEANO):
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
					case(INTEIRO):
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
					case(REFERENCIA):
					{
#ifdef DEBUG_EE_INVOKEVIRTUAL
	cout<< "ExecutionEngine::i_invokevirtual()10" << endl;
#endif
						if(((Objeto*)valorQueSeraImpresso.dado)->ObterTipoObjeto() != TipoObjeto::STRING)
						{
							throw new Erro("String esperado quando deve imprimir referencias", "ExecutionEngine", "invokevirtual");
						}
#ifdef DEBUG_EE_INVOKEVIRTUAL
	cout<< "ExecutionEngine::i_invokevirtual()11" << endl;
#endif
						ObjetoString *stringPtr;
#ifdef DEBUG_EE_INVOKEVIRTUAL
	cout<< "ExecutionEngine::i_invokevirtual()12" << endl;
#endif
						memcpy(&stringPtr, &(valorQueSeraImpresso.dado), sizeof(ObjetoString *));
#ifdef DEBUG_EE_INVOKEVIRTUAL
	cout<< "ExecutionEngine::i_invokevirtual()13" << endl;
#endif
						printf("%s", stringPtr->ObterString().c_str());
						break;
					}
					default:
					{
						string errMsg= "Tentou-se imprimir um tipo de dado invalido. \t tipo fornecido: ";
						try
						{
							errMsg+= ObterStringTipo(valorQueSeraImpresso.tipo);
						}
						catch(Erro *)
						{
							errMsg+= "TIPO_DESCONHECIDO";
						}
						throw new Erro(errMsg, "ExecutionEngine", "invokevirtual");
					}
				}
#ifdef DEBUG_EE_INVOKEVIRTUAL
	cout<< "ExecutionEngine::i_invokevirtual()14" << endl;
#endif

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
					if(string1.tipo != REFERENCIA)
					{
						throw new Erro("Esperado valor do tipo referencia para pegar comprimento da string", "ExecutionEngine", "i_invokevirtual");
					}
					if(((Objeto*)string1.dado)->ObterTipoObjeto() == STRING)
					{
						throw new Erro("Esperado objeto do tipo string para calcular", "ExecutionEngine", "i_invokevirtual");
					}
					ObjetoString *stringObj= (ObjetoString *)string1.dado;
					Valor tamanhoDaString;
					tamanhoDaString.tipo= INTEIRO;
					tamanhoDaString.dado=stringObj->ObterString().size();
					topoDaPilha->empilharOperando(tamanhoDaString);
				}
				else if(nomeDoMetodo == "equals")
				{
					Valor string1 = topoDaPilha->desempilhaOperando();
					if(string1.tipo != REFERENCIA)
					{
						throw new Erro("Esperado valor do tipo referencia para analisar igualdade de strings(erro na primeira string)", "ExecutionEngine", "i_invokevirtual");
					}
					if(((Objeto*)string1.dado)->ObterTipoObjeto() == STRING)
					{
						throw new Erro("Esperado objeto do tipo string  para analisar igualdade de strings(erro na primeira string)", "ExecutionEngine", "i_invokevirtual");
					}
					Valor string2 = topoDaPilha->desempilhaOperando();
					if(string2.tipo != REFERENCIA)
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
					resultado.tipo=BOOLEANO;
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
			string errMsg = "Metodo que esta tentando invocar um metodo desconhecido \tclasse: ";
			errMsg+= nomeDaClasse;
			errMsg+= " \tmetodo: ";
			errMsg+= nomeDoMetodo;
			errMsg+= " \tdescritor: ";
			errMsg+= descritorDoMetodo;
			throw new Erro(errMsg, "ExecutionEngine", "invokevirtual");
		}
	}
	else
	{
#ifdef DEBUG_EE_INVOKEVIRTUAL
	cout<< "ExecutionEngine::i_invokevirtual()15" << endl;
#endif
		uint16_t numeroDeargumentos=0;
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
			if(temp.tipo == PREENCHIMENTO)
			{
				argumentos.insert(argumentos.begin()+1, temp);
			}
			else
			{
				argumentos.insert(argumentos.begin(), temp);
			}
		}
		Valor valorQueArmazenaObjeto= topoDaPilha->desempilhaOperando();
		if(valorQueArmazenaObjeto.tipo != REFERENCIA)
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
		JavaClass *classeAlvo= runtimeDataArea->CarregarClasse(nomeDaClasse);
		Frame *novoFrame= new Frame(instancia, classeAlvo, nomeDoMetodo, descritorDoMetodo, argumentos, runtimeDataArea);
		if(runtimeDataArea->topoPilha() != topoDaPilha)
		{
			topoDaPilha->setaPilhaOperandos(pilhaDeOperandosDeReserva);
			delete novoFrame;
			return;
		}
		runtimeDataArea->empilharFrame(novoFrame);
		#ifdef DEBUG_EE_EMPILHAR_FRAME
		cout<< "Frame empilhado! classe: " << classeAlvo->getUTF8(classeAlvo->ObterEstaClasse()) << " \tmetodo: " << nomeDoMetodo << " \tdescritor: " << descritorDoMetodo << endl;
		#endif
	}
	topoDaPilha->incrementaPC(3);
}

void ExecutionEngine::i_invokespecial(){ 
	//usa no mainvazia
	Frame *topoDaPilhaDeFrames = runtimeDataArea->topoPilha();
	
	stack<Valor> pilhaDeOperandosDeReserva = topoDaPilhaDeFrames->retornaPilhaOperandos();
	JavaClass *classe= topoDaPilhaDeFrames->ObterJavaClass();
	
	uint8_t *instrucoes = topoDaPilhaDeFrames->getCode();
	//argumentos da instrucao
	uint16_t indiceDoMetodo;
	memcpy(&indiceDoMetodo, &(instrucoes[1]), 2);
	indiceDoMetodo= InverterEndianess<uint16_t>(indiceDoMetodo);
	
	if(classe->getConstantPool().at(indiceDoMetodo-1)->GetTag() != CONSTANT_Methodref)
	{
		throw new Erro("Esperado encontrar um CONSTANT_Methodref", "ExecutionEngine", "invokespecial");
	}
	CONSTANT_Methodref_info *cpMetodo= (CONSTANT_Methodref_info*)classe->getConstantPool().at(indiceDoMetodo-1);
	if(classe->getConstantPool().at(cpMetodo->GetNameAndTypeIndex()-1)->GetTag() != CONSTANT_NameAndType)
	{
		throw new Erro("Esperado encontrar um CONSTANT_NameAndType", "ExecutionEngine", "invokespecial");
	}
	CONSTANT_NameAndType_info *assinatura= (CONSTANT_NameAndType_info*)classe->getConstantPool().at(cpMetodo->GetNameAndTypeIndex()-1);
	
	string nomeDaClasse= classe->getUTF8(cpMetodo->GetClassIndex());
	string nomeDoMetodo= classe->getUTF8(assinatura->GetNameIndex());
	string descritorDoMetodo= classe->getUTF8(assinatura->GetDescriptorIndex());
	
	if(nomeDoMetodo == "<init>" && (nomeDaClasse== "java/lang/Object" || nomeDaClasse == "java/lang/String"))
	{
		if(nomeDaClasse == "java/lang/string")
		{
			topoDaPilhaDeFrames->desempilhaOperando();
		}
		topoDaPilhaDeFrames->incrementaPC(3);
		return;
	}

	
	if (nomeDaClasse.find("java/") == string::npos)
	{
		uint16_t numeroDeArgumentos = 0;
		char indicadorDeTipo;
		for(int cont =1 ; descritorDoMetodo[cont] != ')'; cont++)
		{
			indicadorDeTipo= descritorDoMetodo[cont];
			if (indicadorDeTipo == '[')
			{
				numeroDeArgumentos++;
				while (descritorDoMetodo[++cont] == '[');
				if (descritorDoMetodo[cont] == 'L')
				{
					while (descritorDoMetodo[++cont] != ';')
					{};
				}
			}
			else if (indicadorDeTipo == 'J' || indicadorDeTipo == 'D')
			{
				numeroDeArgumentos += 2;
			}
			else if(indicadorDeTipo == 'L')
			{
				numeroDeArgumentos++;
				while (descritorDoMetodo[++cont] != ';')
				{};
			}
			else
			{
				numeroDeArgumentos++;
			}
		}

		vector<Valor> argumentos;
		for (int cont = 0; cont  < numeroDeArgumentos; cont++)
		{
			Valor temp = topoDaPilhaDeFrames->desempilhaOperando();
			if (temp.tipo == PREENCHIMENTO)
			{
				argumentos.insert(argumentos.begin() + 1, temp);
			}
			else
			{
				argumentos.insert(argumentos.begin(), temp);
			}
		}

		Valor valorQueArmazenaObjeto = topoDaPilhaDeFrames->desempilhaOperando();
		if(valorQueArmazenaObjeto.tipo != REFERENCIA)
		{
			throw new Erro("Esperava um valor do tipo referencia", "EnxecutionEngine", "Invokespecial");
		}
		argumentos.insert(argumentos.begin(), valorQueArmazenaObjeto);//adiciono o objeto com primeiro elemento na lista de argumentos
		Objeto *obj= (Objeto*) valorQueArmazenaObjeto.dado;
		if(obj->ObterTipoObjeto() != INSTANCIA)
		{
			throw new Erro("Esperava-se um objeto do tipo instancia", "ExecutionEngine", "Invokespecial");
		}
		ObjetoInstancia *instancia = (ObjetoInstancia*) valorQueArmazenaObjeto.dado;
		JavaClass *classeAlvo= runtimeDataArea->CarregarClasse(nomeDaClasse);
		
		Frame *novoFrame= new Frame(instancia, classeAlvo, nomeDoMetodo, descritorDoMetodo, argumentos, runtimeDataArea);
		
		if(runtimeDataArea->topoPilha() != topoDaPilhaDeFrames)
		{
			topoDaPilhaDeFrames->setaPilhaOperandos(pilhaDeOperandosDeReserva);
			delete novoFrame;
			return;
		}
		runtimeDataArea->empilharFrame(novoFrame);
		#ifdef DEBUG_EE_EMPILHAR_FRAME
		cout<< "Frame empilhado! classe: " << classeAlvo->getUTF8(classeAlvo->ObterEstaClasse()) << " \tmetodo: " << nomeDoMetodo << " \tdescritor: " << descritorDoMetodo << endl;
		#endif
	}
	topoDaPilhaDeFrames->incrementaPC(3);
}

void ExecutionEngine::i_invokestatic(){
	Frame *topoDaPilhaDeFrames= runtimeDataArea->topoPilha();

	stack<Valor> pilhaDeOperandosDeBackUp= topoDaPilhaDeFrames->retornaPilhaOperandos();
	JavaClass *classe= topoDaPilhaDeFrames->ObterJavaClass();
	uint8_t *instrucoes= topoDaPilhaDeFrames->getCode();

	uint16_t indiceDoMetodo;
	memcpy(&indiceDoMetodo, &(instrucoes[1]), 2);
	indiceDoMetodo= InverterEndianess<uint16_t>(indiceDoMetodo);
	
	if(classe->getConstantPool()[indiceDoMetodo-1]->GetTag() != CONSTANT_Methodref)
	{
		throw new Erro("Esperado CONSTANT_Methodref na constant pool", "ExecutionEngine", "i_invokestatic");
	}
	
	CONSTANT_Methodref_info* cpMetodo= (CONSTANT_Methodref_info*)classe->getConstantPool()[indiceDoMetodo-1];
	string nomeDaClasse= classe->getUTF8(cpMetodo->GetClassIndex());
	
	if(classe->getConstantPool()[cpMetodo->GetNameAndTypeIndex()-1]->GetTag() != CONSTANT_NameAndType)
	{
		throw new Erro("Esperado CONSTANT_NameAndType na constant pool", "ExecutionEngine", "i_invokestatic");
	}
	
	CONSTANT_NameAndType_info *cpAssinatura= (CONSTANT_NameAndType_info*) classe->getConstantPool()[cpMetodo->GetNameAndTypeIndex()-1];
	string nomeDoMetodo = classe->getUTF8(cpAssinatura->GetNameIndex());
	string descritorDoMetodo = classe->getUTF8(cpAssinatura->GetDescriptorIndex());
	
	if(nomeDoMetodo == "registerNatives" && nomeDaClasse== "java/lang/Object")
	{
		topoDaPilhaDeFrames->incrementaPC(3);
		return;
	}
	if(nomeDaClasse.find("java/") != string::npos)
	{
		string mensagemDeErro= "Tentando chamar metodo estatico invalido: ";
		mensagemDeErro+= nomeDoMetodo;
		throw new Erro(mensagemDeErro.c_str(), "ExecutionEngine", "invokestatic");
	}
	else
	{//identificar a quantidade de argumentos
		uint16_t numeroDeArgumentos;
		for(int cont =1; descritorDoMetodo[cont] != ')'; cont++)//pula o abre parenteses
		{
			char indicadorDeTipo= descritorDoMetodo[cont];
			if(indicadorDeTipo == 'J' || indicadorDeTipo == 'D')
			{
				numeroDeArgumentos+= 2;
			}
			else if(indicadorDeTipo == 'L')
			{
				numeroDeArgumentos++;
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
				numeroDeArgumentos++;
			}
		}
		//agora que sabemos a quantidade de arqumentos, vamos remover os argumentos da pilha e colocar no futuro vetor de variaveis locais
		vector<Valor> argumentos;
		Valor temp;
		for(int cont =0; cont < numeroDeArgumentos; cont++)
		{
			temp= topoDaPilhaDeFrames->desempilhaOperando();
			if(temp.tipo == PREENCHIMENTO)
			{
				argumentos.insert(argumentos.begin()+1, temp);
			}
			else
			{
				argumentos.insert(argumentos.begin(), temp);
			}
		}
		JavaClass *classeDaQualChamaremosOMetodo= runtimeDataArea->CarregarClasse(nomeDaClasse);
		Frame* novoFrame= new Frame(classeDaQualChamaremosOMetodo, nomeDoMetodo, descritorDoMetodo, argumentos, runtimeDataArea);
		//verificase se o clinit foi adicionado.
		//TODO: verificar se aqui devemos relamente devemos jogar tudo que fizemos fora ou apenas adicionar o novo frame no inicio+1 da pilha de frames, mas para isso temos que mudar a pilha de frames para uma lista ou vetor
		if(topoDaPilhaDeFrames != runtimeDataArea->topoPilha())
		{
			topoDaPilhaDeFrames->setaPilhaOperandos(pilhaDeOperandosDeBackUp);
			delete novoFrame;
			return;
		}
		runtimeDataArea->empilharFrame(novoFrame);
		#ifdef DEBUG_EE_EMPILHAR_FRAME
		cout<< "Frame empilhado! classe: " << classeDaQualChamaremosOMetodo->getUTF8(classeDaQualChamaremosOMetodo->ObterEstaClasse()) << " \tmetodo: " << nomeDoMetodo << " \tdescritor: " << descritorDoMetodo << endl;
		#endif
	}
	topoDaPilhaDeFrames->incrementaPC(3);
}
void ExecutionEngine::i_invokeinterface()
{
	Frame *topoDaPilhaDeFrames= runtimeDataArea->topoPilha();

	stack<Valor> pilhaDeOperandosDeReserva= topoDaPilhaDeFrames->retornaPilhaOperandos();
	JavaClass *classe= topoDaPilhaDeFrames->ObterJavaClass();
	uint8_t *instrucoes= topoDaPilhaDeFrames->getCode();
	
	uint16_t indiceDoMetodo;
	memcpy(&indiceDoMetodo, &(instrucoes[1]), 2);
	indiceDoMetodo= InverterEndianess<uint16_t>(indiceDoMetodo);
	
	if(classe->getConstantPool().at(indiceDoMetodo-1)->GetTag() != CONSTANT_Methodref)
	{
		throw new Erro("Esperado encontrar um CONSTANT_Methodref", "ExecutionEngine", "i_invokeinterface");
	}
#ifdef DEBUG_EE
	cout<< "ExecutionEngine::i_invokeinterface()5" << endl;
#endif
	CONSTANT_Methodref_info *metodo= (CONSTANT_Methodref_info *)classe->getConstantPool().at(indiceDoMetodo-1);
#ifdef DEBUG_EE
	cout<< "ExecutionEngine::i_invokeinterface()6" << endl;
#endif
	string nomeDaClasse= classe->getUTF8(metodo->GetClassIndex());
	if(classe->getConstantPool().at(metodo->GetNameAndTypeIndex()-1)->GetTag() != CONSTANT_NameAndType)
	{
		throw new Erro("Esperado encontrar um CONSTANT_NameAndType", "ExecutionEngine", "i_invokeinterface");
	}
	CONSTANT_NameAndType_info *assinaturaDoMetodo= (CONSTANT_NameAndType_info*) classe->getConstantPool().at(metodo->GetNameAndTypeIndex()-1);
	string nomeDoMetodo= classe->getUTF8(assinaturaDoMetodo->GetNameIndex());
	string descritorDoMetodo= classe->getUTF8(assinaturaDoMetodo->GetDescriptorIndex());
	
	if(nomeDaClasse.find("java/") == string::npos)
	{
		uint16_t numeroDeArgumentos;
		char infoTipo;
		for(int cont =1; descritorDoMetodo[cont] != ')'; cont++ )
		{
			infoTipo= descritorDoMetodo[cont];
			if(infoTipo == 'L')
			{
				numeroDeArgumentos++;
				while(descritorDoMetodo[++cont]!= ';'){};
			}
			else if(infoTipo == 'J' || infoTipo == 'D')
			{
				numeroDeArgumentos+=2;
			}
			else if(infoTipo == '[')
			{
				numeroDeArgumentos++;
				while(descritorDoMetodo[++cont]== '['){};
				if(descritorDoMetodo[cont] == 'L')
				{
					while(descritorDoMetodo[++cont] != ';'){};
				}
			}
			else
			{
				numeroDeArgumentos++;
			}
		}
		vector<Valor> argumentos;
		Valor temp;
		for(int cont =0; cont < numeroDeArgumentos; cont++)
		{
			temp= topoDaPilhaDeFrames->desempilhaOperando();
			if(temp.tipo == PREENCHIMENTO)
			{
				argumentos.insert(argumentos.begin()+1, temp);
			}
			else
			{
				argumentos.insert(argumentos.begin(), temp);
			}
		}
		Valor valorQueArmazenaObjeto= topoDaPilhaDeFrames->desempilhaOperando();
		if(valorQueArmazenaObjeto.tipo != REFERENCIA)
		{
			throw new Erro("Esperava um valor do tipo referencia", "EnxecutionEngine", "i_invokeinterface");
		}
		argumentos.insert(argumentos.begin(), valorQueArmazenaObjeto);
		Objeto *obj= (Objeto*) valorQueArmazenaObjeto.dado;
		if(obj->ObterTipoObjeto() != INSTANCIA)
		{
			throw new Erro("Esperava-se um objeto do tipo instancia", "ExecutionEngine", "i_invokeinterface");
		}
		ObjetoInstancia *instancia= (ObjetoInstancia*) valorQueArmazenaObjeto.dado;
		JavaClass *classeAlvo= runtimeDataArea->CarregarClasse(nomeDaClasse);
		Frame *novoFrame= new Frame(instancia, classeAlvo, nomeDoMetodo, descritorDoMetodo, argumentos, runtimeDataArea);
		if(classeAlvo != instancia->ObterJavaClass())
		{
			cout<< "Ue"<< endl;
		}
		if(runtimeDataArea->topoPilha() != topoDaPilhaDeFrames)
		{
			topoDaPilhaDeFrames->setaPilhaOperandos(pilhaDeOperandosDeReserva);
			delete novoFrame;
			return;
		}
		runtimeDataArea->empilharFrame(novoFrame);
		#ifdef DEBUG_EE_EMPILHAR_FRAME
		cout<< "Frame empilhado! classe: " << classeAlvo->getUTF8(classeAlvo->ObterEstaClasse()) << " \tmetodo: " << nomeDoMetodo << " \tdescritor: " << descritorDoMetodo << endl;
		#endif
	}
	else
	{
		throw new Erro("Tentaram chamar um metodo de interface nao implementado", "ExecutionEngine", "i_invokeinterface");
	}
	topoDaPilhaDeFrames->incrementaPC(5);

}
void ExecutionEngine::i_new(){
	Frame *topoDaPilhaDeFrames= runtimeDataArea->topoPilha();
	JavaClass *classe = topoDaPilhaDeFrames->ObterJavaClass();
	uint8_t *instrucoes= topoDaPilhaDeFrames->getCode();
	
	uint16_t indiceDaClasse;
	memcpy(&indiceDaClasse, &(instrucoes[1]), 2);
	indiceDaClasse= InverterEndianess<uint16_t> (indiceDaClasse);
	
	if(classe->getConstantPool().at(indiceDaClasse-1)->GetTag() != CONSTANT_Class)
	{
		throw new Erro("Esperado encontrar um CONSTANT_Methodref", "ExecutionEngine", "i_new");
	}
	CONSTANT_Class_info *cpClasse= (CONSTANT_Class_info*)classe->getConstantPool().at(indiceDaClasse-1);
	string nomeDaClasse= classe->getUTF8(cpClasse->GetNameIndex());
	
	Objeto *obj;
	if(nomeDaClasse != "java/lang/String")
	{
		JavaClass *classeAlvo= runtimeDataArea->CarregarClasse(nomeDaClasse);
		obj= new ObjetoInstancia(classeAlvo);
	}
	else
	{
		obj= new ObjetoString();
	}
	Valor referenciaProObjeto;
	referenciaProObjeto.tipo= REFERENCIA;
	memcpy(&(referenciaProObjeto.dado), &obj, sizeof(void*));
	
	topoDaPilhaDeFrames->empilharOperando(referenciaProObjeto);
	topoDaPilhaDeFrames->incrementaPC(3);
}
void ExecutionEngine::i_newarray()
{
	Frame *topoDaPilhaDeFrames= runtimeDataArea->topoPilha();
	uint8_t *instrucoes= topoDaPilhaDeFrames->getCode();
	
	Valor tamanhoDoFuturoArray= topoDaPilhaDeFrames->desempilhaOperando();
	if(tamanhoDoFuturoArray.tipo != INTEIRO)
	{
		throw new Erro("Esperado encontrar um valor do tipo int", "ExecutionEngine", "i_newarray");
	}
	ObjetoArray *arrayQueSeraCriado;
	int32_t temp;
	memcpy(&temp, &(tamanhoDoFuturoArray.dado), 4);
	if(temp < 0)
	{
		throw new Erro("NegativeArraySizeException");
	}
	
	Valor elementoDoArray;
	elementoDoArray.dado =0;
	
	
	uint8_t tipoDoArray = instrucoes[1];
	switch(tipoDoArray)
	{
		case(4):
		{
			arrayQueSeraCriado = new ObjetoArray(BOOLEANO);
			elementoDoArray.tipo= BOOLEANO;
			break;
		}
		case(5):
		{
			arrayQueSeraCriado = new ObjetoArray(CHAR);
			elementoDoArray.tipo= CHAR;
			break;
		}
		case(6):
		{
			arrayQueSeraCriado = new ObjetoArray(FLOAT);
			elementoDoArray.tipo= FLOAT;
			break;
		}
		case(7):
		{
			arrayQueSeraCriado = new ObjetoArray(DOUBLE);
			elementoDoArray.tipo= DOUBLE;
			break;
		}
		case(8):
		{
			arrayQueSeraCriado = new ObjetoArray(BYTE);
			elementoDoArray.tipo= BYTE;
			break;
		}
		case(9):
		{
			arrayQueSeraCriado = new ObjetoArray(SHORT);
			elementoDoArray.tipo= SHORT;
			break;
		}
		case(10):
		{
			arrayQueSeraCriado = new ObjetoArray(INTEIRO);
			elementoDoArray.tipo= INTEIRO;
			break;
		}
		case(11):
		{
			arrayQueSeraCriado = new ObjetoArray(LONG);
			elementoDoArray.tipo= LONG;
		}
	}
	for(unsigned int cont = 0; cont < tamanhoDoFuturoArray.dado; cont++)
	{
		arrayQueSeraCriado->InserirValor(elementoDoArray);
	}
	
	Valor referenciaProArray;
	referenciaProArray.tipo= REFERENCIA;
	memcpy(&(referenciaProArray.dado), &arrayQueSeraCriado, sizeof(void*));
	
	topoDaPilhaDeFrames->empilharOperando(referenciaProArray);
	topoDaPilhaDeFrames->incrementaPC(2);
}
void ExecutionEngine::i_anewarray()
{
	Frame *topoDaPilhaDeFrames= runtimeDataArea->topoPilha();
	uint8_t *instrucoes= topoDaPilhaDeFrames->getCode();
	JavaClass *classe= topoDaPilhaDeFrames->ObterJavaClass();
	
	Valor tamanhoDoFuturoArray= topoDaPilhaDeFrames->desempilhaOperando();
	if(tamanhoDoFuturoArray.tipo != INTEIRO)
	{
		throw new Erro("Esperado encontrar um valor do tipo int", "ExecutionEngine", "i_anewarray");
	}
	if(tamanhoDoFuturoArray.dado < 0)
	{
		throw new Erro("NegativeArraySizeException");
	}
	
	uint16_t indiceDaClasse;
	memcpy(&indiceDaClasse, &(instrucoes[1]), 2);
	indiceDaClasse= InverterEndianess<uint16_t>(indiceDaClasse);
	
	if(classe->getConstantPool().at(indiceDaClasse-1)->GetTag() != CONSTANT_Class)
	{
		throw new Erro("Esperado encontrar um CONSTANT_Class", "ExecutionEngine", "i_anewarray");
	}
	CONSTANT_Class_info *cpClasse= (CONSTANT_Class_info*)classe->getConstantPool().at(indiceDaClasse-1);
	string nomeDaClasse= classe->getUTF8(cpClasse->GetNameIndex());
	
	if(nomeDaClasse != "java/lang/String")
	{
		int cont=0;
		while(nomeDaClasse[cont] == '[')
		{
			cont++;
		}
		if(nomeDaClasse[cont == 'L'])
		{
			runtimeDataArea->CarregarClasse(nomeDaClasse.substr(cont+1, nomeDaClasse.size()-cont -2));
		}
	}
	
	ObjetoArray *arrayQueSeraCriado= new ObjetoArray(REFERENCIA);
	void *null= NULL;
//	memcpy(&temp, &(tamanhoDoFuturoArray.dado), 4);
	
	Valor referenciaProArray;
	referenciaProArray.tipo = REFERENCIA;
	memcpy(&(referenciaProArray.dado), &arrayQueSeraCriado, sizeof(void*));
	
	Valor ponteiroNULL;
	ponteiroNULL.tipo= REFERENCIA;
	memcpy(&(ponteiroNULL.dado), &null, sizeof(void*));
	
	for(unsigned int cont =0 ; cont < tamanhoDoFuturoArray.dado; cont++)
	{
		arrayQueSeraCriado->empilhaValor(ponteiroNULL);
	}
	
	topoDaPilhaDeFrames->empilharOperando(referenciaProArray);
	topoDaPilhaDeFrames->incrementaPC(3);
	
}

void ExecutionEngine::i_arraylength(){

	Frame *toppilha = runtimeDataArea->topoPilha();
	
	Valor arrayref = toppilha->desempilhaOperando();

	if ((Objeto*)arrayref.dado == NULL) {
		cerr << "NullPointerException" << endl;
		exit(1);
	} 
	
	Valor length;
	length.tipo = TipoDado::INTEIRO;
	length.dado = ((ObjetoArray *) arrayref.dado)->ObterTamanho();
	toppilha->empilharOperando(length);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_athrow(){
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_checkcast()
{
	Frame *topoDaPilhaDeFrames= runtimeDataArea->topoPilha();
	uint8_t *instrucoes= topoDaPilhaDeFrames->getCode();
	JavaClass *classe= topoDaPilhaDeFrames->ObterJavaClass();
	
	uint16_t indiceDaCp;
	memcpy(&indiceDaCp, &(instrucoes[1]), 2);
	indiceDaCp= InverterEndianess<uint16_t>(indiceDaCp);
	
	if(classe->getConstantPool().at(indiceDaCp-1)->GetTag() != CONSTANT_Class)
	{
		throw new Erro("Esperado CONSTANT_Class", "ExecutionEngine", "i_checkcast");
	}
	
	string nomeDaClasse= classe->getUTF8(indiceDaCp);
	
	Valor valorRefProObjeto= topoDaPilhaDeFrames->desempilhaOperando();
	
	if(valorRefProObjeto.tipo != REFERENCIA)
	{
		throw new Erro("Esperado valor do tipo referencia");
	}
	Valor valorDoResultado;
	valorDoResultado.tipo = INTEIRO;
	
	if(((Objeto*)valorRefProObjeto.dado) == NULL)
	{
		throw new Erro("ClassCastException");
	}
	if(((Objeto*)valorRefProObjeto.dado)->ObterTipoObjeto() == INSTANCIA)
	{
		ObjetoInstancia *instancia= (ObjetoInstancia*)valorRefProObjeto.dado;
		JavaClass *classeAlvo=  instancia->ObterJavaClass();
		string nomeDaClasseAtual;
		
		bool naoAchou= true;
		while(naoAchou)
		{
			JavaClass *classeTemp= classeAlvo;
			nomeDaClasseAtual= classeTemp->getUTF8(classeTemp->ObterEstaClasse());
			if(nomeDaClasseAtual == nomeDaClasse)
			{
				naoAchou=false;
			}
			else
			{
				if(classeTemp->ObterSuperClasse() != 0)
				{//se tiver dando dau(entrando em loop) troque essa linha
					string nomeDaSuperClasse= classeTemp->getUTF8(classeTemp->ObterEstaClasse());
#ifdef MINI_DEBUG
cout<< "se estiver entrando em loop aqui no i_checkcast faça a substituicao"<< endl;
#endif
					//por essa
//					string nomeDaSuperClasse= classeTemp->getUTF8(classeTemp->ObterSuperClasse());
					//fim da observação
					classeAlvo= runtimeDataArea->CarregarClasse(nomeDaSuperClasse);
				}
				else
				{
					break;
				}
			}
		}
		valorDoResultado.dado= naoAchou? 0 : 1;
	}
	else if(((Objeto*)valorRefProObjeto.dado)->ObterTipoObjeto() == STRING)
	{
		if(nomeDaClasse == "java/lang/String" || nomeDaClasse == "java/lang/Object")
		{
			valorDoResultado.dado= 1;
		}
		else
		{
			valorDoResultado.dado= 0;
		}
	}
	else//então é um array
	{
		if(nomeDaClasse == "java/lang/Object")
		{
			valorDoResultado.dado= 1;
		}
		else
		{
			valorDoResultado.dado= 0;
		}
	}
	topoDaPilhaDeFrames->empilharOperando(valorDoResultado);
	topoDaPilhaDeFrames->incrementaPC(3);
}

void ExecutionEngine::i_instanceof(){

	Frame *topo = runtimeDataArea->topoPilha();

	uint8_t *code = topo->getCode();
	uint8_t byte1 = code[1];
	uint8_t byte2 = code[2];

	uint16_t cpIndex = (byte1 << 8) | byte2;
	vector<cp_info*> constantPool = ((ObjetoInstancia*)(topo->getObjeto()))->ObterJavaClass()->getConstantPool();

	Valor objectrefValue = topo->desempilhaOperando();
 	
	string className = ((ObjetoInstancia*)topo->getObjeto())->ObterJavaClass()->getUTF8(cpIndex);

	Valor resultValor;
	resultValor.tipo = TipoDado::INTEIRO;

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

	cout<<"Consertar ExecutionEngine::i_multianewarray" << endl;
	Frame *topo = runtimeDataArea->topoPilha();
	vector<cp_info*> constantPool = topo->ObterJavaClass()->getConstantPool();

	uint8_t *code = topo->getCode();
	uint8_t byte1 = code[1];
	uint8_t byte2 = code[2];
	uint8_t dimensoes = code[3];

	uint16_t classIndex = (byte1 << 8) | byte2;

	CONSTANT_Class_info *classInfo = (CONSTANT_Class_info*)constantPool[classIndex-1];
	
	string className = topo->ObterJavaClass()->getUTF8(classInfo->GetNameIndex());

	// obter o tipo dentro de className:
	TipoDado tipoDado;
	int i = 0;
	while (className[i] == '[') i++;
		// em caso de ser uma referência ([[[Ljava/lang/String;)
	string multiArrayType = className.substr(i+1, className.size()-i-2); 

	switch (className[i]) {
		case 'L':// verifica se existe classe com esse nome
			if (multiArrayType != "java/lang/String") {
				runtimeDataArea->CarregarClasse(multiArrayType); 
			}
			tipoDado = TipoDado::REFERENCIA;
			break;
		case 'B':
			tipoDado = TipoDado::BYTE;
			break;
		case 'C':
			tipoDado = TipoDado::CHAR;
			break;
		case 'D':
			tipoDado = TipoDado::DOUBLE;
			break;
		case 'F':
			tipoDado = TipoDado::FLOAT;
			break;
		case 'I':
			tipoDado = TipoDado::INTEIRO;
			break;
		case 'J':
			tipoDado = TipoDado::LONG;
			break;
		case 'S':
			tipoDado = TipoDado::SHORT;
			break;
		case 'Z':
			tipoDado = TipoDado::BOOLEANO;
			break;
		default:
			cerr << "Descritor invalido em multianewarray" << endl;
			exit(1);
	}

	stack<int> count;
	for (int i = 0; i < dimensoes; i++) {
		Valor dimLength = topo->desempilhaOperando();
		count.push(dimLength.dado);
	}

	ObjetoArray *arr = new ObjetoArray((dimensoes > 1) ? TipoDado::REFERENCIA : tipoDado);
	arr->popularSubArray(tipoDado, count);  

	Valor valorArr;
	valorArr.tipo = TipoDado::REFERENCIA;
	valorArr.dado = (uint64_t)arr;

	topo->empilharOperando(valorArr);

	topo->incrementaPC(4);

}
 
void ExecutionEngine::i_ifnull(){

	Frame *topo = runtimeDataArea->topoPilha();

	Valor referencia = topo->desempilhaOperando();


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
	endRetorno.tipo = TipoDado::ENDERECO_DE_RETORNO;
	endRetorno.dado = topo->getPC() + 5;
	topo->empilharOperando(endRetorno);

	topo->incrementaPC(offsetSalto);

}

void ExecutionEngine::StoreValor(Valor val)
{



	Frame *topoDaPilhaDeFrames= runtimeDataArea->topoPilha();
#ifdef DEBUG_EE
cout << "ExecutionEngine::i_StoreValor 0 \t indice = " << val.dado << " \ttamanhpilha=  "<< topoDaPilhaDeFrames->tamanhoVetorVariaveis() << endl;
#endif
	Valor valorDaPilha= topoDaPilhaDeFrames->desempilhaOperando();
#ifdef DEBUG_EE_STORE_VALOR
cout << "ExecutionEngine::i_StoreValor 1" << endl;
cout << ObterStringTipo(valorDaPilha.tipo) << endl;
#endif

	if(valorDaPilha.tipo != val.tipo)
	{
#ifdef DEBUG_EE
cout << "ExecutionEngine::i_StoreValor 2" << endl;
#endif
		string errMsg= "Tentativa de store de um valor com tipo incorreto.\t";
		errMsg+= "Esperado: ";
#ifdef DEBUG_EE
cout << "ExecutionEngine::i_StoreValor 3" << endl;
#endif
		errMsg+= ObterStringTipo(val.tipo);
#ifdef DEBUG_EE
cout << "ExecutionEngine::i_StoreValor 4" << endl;
#endif
		errMsg+= "\tFornecido: ";
		errMsg+= ObterStringTipo(valorDaPilha.tipo);
#ifdef DEBUG_EE
cout << "ExecutionEngine::i_StoreValor 5" << endl;
#endif
//		cerr<< errMsg;
		throw new Erro(errMsg, "ExecutionEngine", "StoreValor");
#ifdef DEBUG_EE
cout << "ExecutionEngine::i_StoreValor 6" << endl;
#endif
	}
#ifdef DEBUG_EE
cout << "ExecutionEngine::i_StoreValor 7" << endl;
#endif
	topoDaPilhaDeFrames->mudarVariavelLocal(valorDaPilha, val.dado);
#ifdef DEBUG_EE
cout << "ExecutionEngine::i_StoreValor 8" << endl;
#endif

}





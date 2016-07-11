#ifndef EXECUTIONENGINE_HPP
#define EXECUTIONENGINE_HPP
#include<vector>
#include"RuntimeDataArea.hpp"

#ifndef RUNTIMEDATAAREA
class RuntimeDataArea;
#endif

#define EXECUTIONENGINE
class ExecutionEngine
{
	private:

		void (ExecutionEngine::*vetorDePonteirosParaFuncao[250])();
		RuntimeDataArea *runtimeDataArea;

		//Armazena \c true se a última instrução foi um wide, e \c false caso contrário.
		bool isWide;

		void inicializaInstrucoes();

		void StoreValor(Valor val);

		//Implementacao das funcionalidades de cada uma das 250 instrucoes
		void java_nop();
		//operacoes logicas
		void java_iadd();
		void java_ladd();
		void java_fadd();
		void java_dadd();
		void java_isub();
		void java_lsub();
		void java_fsub();
		void java_dsub();
		void java_imul();
		void java_lmul();
		void java_fmul();
		void java_dmul();
		void java_idiv();
		void java_ldiv();
		void java_fdiv();
		void java_ddiv();
		void java_irem();
		void java_lrem();
		void java_frem();
		void java_drem();

		//stores
		void java_istore();
		void java_lstore();
		void java_fstore();
		void java_dstore();
		void java_astore();
		void java_istore_0();
		void java_istore_1();
		void java_istore_2();
		void java_istore_3();
		void java_lstore_0();
		void java_lstore_1();
		void java_lstore_2();
		void java_lstore_3();
		void java_fstore_0();
		void java_fstore_1();
		void java_fstore_2();
		void java_fstore_3();
		void java_dstore_0();
		void java_dstore_1();
		void java_dstore_2();
		void java_dstore_3();
		void java_astore_0();
		void java_astore_1();
		void java_astore_2();
		void java_astore_3();
		void java_iastore();
		void java_lastore();
		void java_fastore();
		void java_dastore();
		void java_aastore();
		void java_bastore();
		void java_castore();
		void java_sastore();
		//de pilha
		void java_pop();
		void java_pop2();
		void java_dup();
		void java_dup_x1();
		void java_dup_x2();
		void java_dup2();
		void java_dup2_x1();
		void java_dup2_x2();
		void java_swap();
		//bit
		void java_ineg();
		void java_lneg();
		void java_fneg();
		void java_dneg();
		void java_ishl();
		void java_lshl();
		void java_ishr();
		void java_lshr();
		void java_iushr();
		void java_lushr();
		void java_iand();
		void java_land();
		void java_ior();
		void java_lor();
		void java_ixor();
		void java_lxor();
		void java_iinc();
		void java_i2l();
		void java_i2f();
		void java_i2d();
		void java_l2i();
		void java_l2f();
		void java_l2d();
		void java_f2i();
		void java_f2l();
		void java_f2d();
		void java_d2i();
		void java_d2l();
		void java_d2f();
		void java_i2b();
		void java_i2c();
		void java_i2s();
		void java_lcmp();
		void java_fcmpl();
		void java_fcmpg();
		void java_dcmpl();
		void java_dcmpg();
		void java_ifeq();
		void java_ifne();
		void java_iflt();
		void java_ifge();
		void java_ifgt();
		void java_ifle();
		void java_if_icmpeq();
		void java_if_icmpne();
		void java_if_icmplt();
		void java_if_icmpge();
		void java_if_icmpgt();
		void java_if_icmple();
		void java_if_acmpeq();
		void java_if_acmpne();
		void java_goto();
		void java_jsr();
		void java_ret();
		void java_tableswitch();
		void java_lookupswitch();
		void java_ireturn();
		void java_lreturn();
		void java_freturn();
		void java_dreturn();
		void java_areturn();
		void java_return();
		void java_getstatic();
		void java_putstatic();
		void java_getfield();
		void java_putfield();
		void java_invokevirtual();
		void java_invokespecial();
		void java_invokestatic();
		void java_invokeinterface();
		void java_new();
		void java_newarray();
		void java_anewarray();
		void java_arraylength();
		void java_athrow();
		void java_checkcast();//Checa se o objeto é do tipo informado
		void java_instanceof();//Determina se um objeto é do tipo informado
		void java_monitorenter();//na nossa implementação apenas incrementa pc
		void java_monitorexit();//na nossa implementação apenas incrementa pc
		void java_wide();//Retorna void de um método
		void java_multianewarray();//Cria um array multidimensional
		void java_ifnull();//Salta se o endereço é nulo
		void java_ifnonnull();//Salta se o endereço é não nulo
		void java_goto_w();//salta para endereço(sempre)
		void java_jsr_w();//Salta para subrotina

		//consts
		void java_aconst_null();
		void java_iconst_m1();
		void java_iconst_0();
		void java_iconst_1();
		void java_iconst_2();
		void java_iconst_3();
		void java_iconst_4();
		void java_iconst_5();
		void java_lconst_0();
		void java_lconst_1();
		void java_fconst_0();
		void java_fconst_1();
		void java_fconst_2();
		void java_dconst_0();
		void java_dconst_1();
		//pushs
		void java_bipush();
		void java_sipush();
		//loads
		void java_ldc();
		void java_ldc_w();
		void java_ldc2_w();
		void java_iload();
		void java_lload();
		void java_fload();
		void java_dload();
		void java_aload();
		void java_iload_0();
		void java_iload_1();
		void java_iload_2();
		void java_iload_3();
		void java_lload_0();
		void java_lload_1();
		void java_lload_2();
		void java_lload_3();
		void java_fload_0();
		void java_fload_1();
		void java_fload_2();
		void java_fload_3();
		void java_dload_0();
		void java_dload_1();
		void java_dload_2();
		void java_dload_3();
		void java_aload_0();
		void java_aload_1();
		void java_aload_2();
		void java_aload_3();
		void java_iaload();
		void java_laload();
		void java_faload();
		void java_daload();
		void java_aaload();
		void java_baload();
		void java_caload();
		void java_saload();

	public:
		void SetRuntimeDataArea(RuntimeDataArea *runtimeDataArea);
		void Play(string classComMain);
		ExecutionEngine();

};


#endif

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

		//Implementacao das funcionalidades de cada uma das 250 instrucoes
		void i_nop();
		void i_aconst_null();
		void i_iconst_m1();
		void i_iconst_0();
		void i_iconst_1();
		void i_iconst_2();
		void i_iconst_3();
		void i_iconst_4();
		void i_iconst_5();
		void i_lconst_0();
		void i_lconst_1();
		void i_fconst_0();
		void i_fconst_1();
		void i_fconst_2();
		void i_dconst_0();
		void i_dconst_1();
		void i_bipush();
		void i_sipush();
		void i_ldc();
		void i_ldc_w();
		void i_ldc2_w();
		void i_iload();
		void i_lload();
		void i_fload();
		void i_dload();
		void i_aload();
		void i_iload_0();
		void i_iload_1();
		void i_iload_2();
		void i_iload_3();
		void i_lload_0();
		void i_lload_1();
		void i_lload_2();
		void i_lload_3();
		void i_fload_0();
		void i_fload_1();
		void i_fload_2();
		void i_fload_3();
		void i_dload_0();
		void i_dload_1();
		void i_dload_2();
		void i_dload_3();
		void i_aload_0();
		void i_aload_1();
		void i_aload_2();
		void i_aload_3();
		void i_iaload();
		void i_laload();
		void i_faload();
		void i_daload();
		void i_aaload();
		void i_baload();
		void i_caload();
		void i_saload();
		void i_istore();
		void i_lstore();
		void i_fstore();
		void i_dstore();
		void i_astore();
		void i_istore_0();
		void i_istore_1();
		void i_istore_2();
		void i_istore_3();
		void i_lstore_0();
		void i_lstore_1();
		void i_lstore_2();
		void i_lstore_3();
		void i_fstore_0();
		void i_fstore_1();
		void i_fstore_2();
		void i_fstore_3();
		void i_dstore_0();
		void i_dstore_1();
		void i_dstore_2();
		void i_dstore_3();
		void i_astore_0();
		void i_astore_1();
		void i_astore_2();
		void i_astore_3();
		void i_iastore();
		void i_lastore();
		void i_fastore();
		void i_dastore();
		void i_aastore();
		void i_bastore();
		void i_castore();
		void i_sastore();
		void i_pop();
		void i_pop2();
		void i_dup();
		void i_dup_x1();
		void i_dup_x2();
		void i_dup2();
		void i_dup2_x1();
		void i_dup2_x2();
		void i_swap();
		void i_iadd();
		void i_ladd();
		void i_fadd();
		void i_dadd();
		void i_isub();
		void i_lsub();
		void i_fsub();
		void i_dsub();
		void i_imul();
		void i_lmul();
		void i_fmul();
		void i_dmul();
		void i_idiv();
		void i_ldiv();
		void i_fdiv();
		void i_ddiv();
		void i_irem();
		void i_lrem();
		void i_frem();
		void i_drem();
		void i_ineg();
		void i_lneg();
		void i_fneg();
		void i_dneg();
		void i_ishl();
		void i_lshl();
		void i_ishr();
		void i_lshr();
		void i_iushr();
		void i_lushr();
		void i_iand();
		void i_land();
		void i_ior();
		void i_lor();
		void i_ixor();
		void i_lxor();
		void i_iinc();
		void i_i2l();
		void i_i2f();
		void i_i2d();
		void i_l2i();
		void i_l2f();
		void i_l2d();
		void i_f2i();
		void i_f2l();
		void i_f2d();
		void i_d2i();
		void i_d2l();
		void i_d2f();
		void i_i2b();
		void i_i2c();
		void i_i2s();
		void i_lcmp();
		void i_fcmpl();
		void i_fcmpg();
		void i_dcmpl();
		void i_dcmpg();
		void i_ifeq();
		void i_ifne();
		void i_iflt();
		void i_ifge();
		void i_ifgt();
		void i_ifle();
		void i_if_icmpeq();
		void i_if_icmpne();
		void i_if_icmplt();
		void i_if_icmpge();
		void i_if_icmpgt();
		void i_if_icmple();
		void i_if_acmpeq();
		void i_if_acmpne();
		void i_goto();
		void i_jsr();
		void i_ret();
		void i_tableswitch();
		void i_lookupswitch();
		void i_ireturn();
		void i_lreturn();
		void i_freturn();
		void i_dreturn();
		void i_areturn();
		void i_return();
		void i_getstatic();
		void i_putstatic();
		void i_getfield();
		void i_putfield();
		void i_invokevirtual();
		void i_invokespecial();
		void i_invokestatic();
		void i_invokeinterface();
		void i_new();
		void i_newarray();
		void i_anewarray();
		void i_arraylength();
		void i_athrow();
		void i_checkcast();
		void i_instanceof();
		void i_monitorenter();
		void i_monitorexit();
		void i_wide();
		void i_multianewarray();
		void i_ifnull();
		void i_ifnonnull();
		void i_goto_w();
		void i_jsr_w();

	public:
		void SetRuntimeDataArea(RuntimeDataArea *runtimeDataArea);
		void Play(string classComMain);
		ExecutionEngine();

};


#endif

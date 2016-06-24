#include"ExecutionEngine.hpp"
void ExecutionEngine::Play(string classComMain)
{

    uint8_t *instruction;
    Objeto *obj = new Objeto() ;

    obj->classe = runtimeDataArea->CarregarClasse(classComMain);
    obj->instancia = NULL;

    runtimeDataArea->empilharFrame(new Frame(obj, "main", "([Ljava/lang/String;)V"));
    runtimeDataArea->empilharFrame(new Frame(obj, "<init>"),"()V");

	do
	{

        instruction = runtimeDataArea->topoPilha().getCode()];
		vetorDePonteirosParaFuncao[instrucao];

	}
	while(runtimeDataArea.PilhaJVM.size > 0);
}


void ExecutionEngine::i_nop(){}
void ExecutionEngine::i_aconst_null(){}
void ExecutionEngine::i_iconst_m1(){}
void ExecutionEngine::i_iconst_0(){}
void ExecutionEngine::i_iconst_1(){}
void ExecutionEngine::i_iconst_2(){}
void ExecutionEngine::i_iconst_3(){}  
void ExecutionEngine::i_iconst_4(){}
void ExecutionEngine::i_iconst_5(){}
void ExecutionEngine::i_lconst_0(){}
void ExecutionEngine::i_lconst_1(){}
void ExecutionEngine::i_fconst_0(){}
void ExecutionEngine::i_fconst_1(){}
void ExecutionEngine::i_fconst_2(){}
void ExecutionEngine::i_dconst_0(){}
void ExecutionEngine::i_dconst_1(){}
void ExecutionEngine::i_bipush(){}
void ExecutionEngine::i_sipush(){}
void ExecutionEngine::i_ldc(){}
void ExecutionEngine::i_ldc_w(){}
void ExecutionEngine::i_ldc2_w(){}
void ExecutionEngine::i_iload(){}
void ExecutionEngine::i_lload(){}
void ExecutionEngine::i_fload(){}
void ExecutionEngine::i_dload(){}
void ExecutionEngine::i_aload(){}
void ExecutionEngine::i_iload_0(){}
void ExecutionEngine::i_iload_1(){}
void ExecutionEngine::i_iload_2(){}
void ExecutionEngine::i_iload_3(){}
void ExecutionEngine::i_lload_0(){}
void ExecutionEngine::i_lload_1(){}
void ExecutionEngine::i_lload_2(){}
void ExecutionEngine::i_lload_3(){}
void ExecutionEngine::i_fload_0(){}
void ExecutionEngine::i_fload_1(){}
void ExecutionEngine::i_fload_2(){}
void ExecutionEngine::i_fload_3(){}
void ExecutionEngine::i_dload_0(){}
void ExecutionEngine::i_dload_1(){}
void ExecutionEngine::i_dload_2(){}
void ExecutionEngine::i_dload_3(){}
void ExecutionEngine::i_aload_0(){}
void ExecutionEngine::i_aload_1(){}
void ExecutionEngine::i_aload_2(){}
void ExecutionEngine::i_aload_3(){}
void ExecutionEngine::i_iaload(){}
void ExecutionEngine::i_laload(){}
void ExecutionEngine::i_faload(){}
void ExecutionEngine::i_daload(){}
void ExecutionEngine::i_aaload(){}
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
void ExecutionEngine::i_dstore_0(){}
void ExecutionEngine::i_dstore_1(){}
void ExecutionEngine::i_dstore_2(){}
void ExecutionEngine::i_dstore_3(){}
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
void ExecutionEngine::i_iadd(){}
void ExecutionEngine::i_ladd(){}
void ExecutionEngine::i_fadd(){}
void ExecutionEngine::i_dadd(){}
void ExecutionEngine::i_isub(){}
void ExecutionEngine::i_lsub(){}
void ExecutionEngine::i_fsub(){}
void ExecutionEngine::i_dsub(){}
void ExecutionEngine::i_imul(){}
void ExecutionEngine::i_lmul(){}
void ExecutionEngine::i_fmul(){}
void ExecutionEngine::i_dmul(){}
void ExecutionEngine::i_idiv(){}
void ExecutionEngine::i_ldiv(){}
void ExecutionEngine::i_fdiv(){}
void ExecutionEngine::i_ddiv(){}
void ExecutionEngine::i_irem(){}
void ExecutionEngine::i_lrem(){}
void ExecutionEngine::i_frem(){}
void ExecutionEngine::i_drem(){}
void ExecutionEngine::i_ineg(){}
void ExecutionEngine::i_lneg(){}
void ExecutionEngine::i_fneg(){}
void ExecutionEngine::i_dneg(){}
void ExecutionEngine::i_ishl(){}
void ExecutionEngine::i_lshl(){}
void ExecutionEngine::i_ishr(){}
void ExecutionEngine::i_lshr(){}
void ExecutionEngine::i_iushr(){}
void ExecutionEngine::i_lushr(){}
void ExecutionEngine::i_iand(){}
void ExecutionEngine::i_land(){}
void ExecutionEngine::i_ior(){}
void ExecutionEngine::i_lor(){}
void ExecutionEngine::i_ixor(){}
void ExecutionEngine::i_lxor(){}
void ExecutionEngine::i_iinc(){}
void ExecutionEngine::i_i2l(){}
void ExecutionEngine::i_i2f(){}
void ExecutionEngine::i_i2d(){}
void ExecutionEngine::i_l2i(){}
void ExecutionEngine::i_l2f(){}
void ExecutionEngine::i_l2d(){}
void ExecutionEngine::i_f2i(){}
void ExecutionEngine::i_f2l(){}
void ExecutionEngine::i_f2d(){}
void ExecutionEngine::i_d2i(){}
void ExecutionEngine::i_d2l(){}
void ExecutionEngine::i_d2f(){}
void ExecutionEngine::i_i2b(){}
void ExecutionEngine::i_i2c(){}
void ExecutionEngine::i_i2s(){}
void ExecutionEngine::i_lcmp(){}
void ExecutionEngine::i_fcmpl(){}
void ExecutionEngine::i_fcmpg(){}
void ExecutionEngine::i_dcmpl(){}
void ExecutionEngine::i_dcmpg(){}
void ExecutionEngine::i_ifeq(){}
void ExecutionEngine::i_ifne(){}
void ExecutionEngine::i_iflt(){}
void ExecutionEngine::i_ifge(){}
void ExecutionEngine::i_ifgt(){}
void ExecutionEngine::i_ifle(){}
void ExecutionEngine::i_if_icmpeq(){}
void ExecutionEngine::i_if_icmpne(){}
void ExecutionEngine::i_if_icmplt(){}
void ExecutionEngine::i_if_icmpge(){}
void ExecutionEngine::i_if_icmpgt(){}
void ExecutionEngine::i_if_icmple(){}
void ExecutionEngine::i_if_acmpeq(){}
void ExecutionEngine::i_if_acmpne(){}
void ExecutionEngine::i_goto(){}
void ExecutionEngine::i_jsr(){}
void ExecutionEngine::i_ret(){}
void ExecutionEngine::i_tableswitch(){}
void ExecutionEngine::i_lookupswitch(){}
void ExecutionEngine::i_ireturn(){}
void ExecutionEngine::i_lreturn(){}
void ExecutionEngine::i_freturn(){}
void ExecutionEngine::i_dreturn(){}
void ExecutionEngine::i_areturn(){}
void ExecutionEngine::i_return(){}
void ExecutionEngine::i_getstatic(){}
void ExecutionEngine::i_putstatic(){}
void ExecutionEngine::i_getfield(){}
void ExecutionEngine::i_putfield(){}
void ExecutionEngine::i_invokevirtual(){}
void ExecutionEngine::i_invokespecial(){}
void ExecutionEngine::i_invokestatic(){}
void ExecutionEngine::i_invokeinterface(){}
void ExecutionEngine::i_new(){}
void ExecutionEngine::i_newarray(){}
void ExecutionEngine::i_anewarray(){}
void ExecutionEngine::i_arraylength(){}
void ExecutionEngine::i_athrow(){}
void ExecutionEngine::i_checkcast(){}
void ExecutionEngine::i_instanceof(){}
void ExecutionEngine::i_monitorenter(){}
void ExecutionEngine::i_monitorexit(){}
void ExecutionEngine::i_wide(){}
void ExecutionEngine::i_multianewarray(){}
void ExecutionEngine::i_ifnull(){}
void ExecutionEngine::i_ifnonnull(){}
void ExecutionEngine::i_goto_w(){}
void ExecutionEngine::i_jsr_w(){}
void ExecutionEngine::initInstructions(){}





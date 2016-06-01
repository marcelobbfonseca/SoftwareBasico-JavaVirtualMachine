#include"Opcode.hpp"

OpCode::OpCode(void)
{
	InicializarMapa();
}

OpCode* OpCode::ref=NULL;

OpCode* OpCode::GetReferencia(void)
{
	if(OpCode::ref== NULL)
	{
		OpCode::ref = new OpCode();
	}
	return OpCode::ref;
}

string OpCode::GetMinemonico(uint8_t bytecode)
{
	if(mapa.size() == 0)
	{
		InicializarMapa();
	}
	return OpCode::mapa[bytecode];
}

void OpCode::InicializarMapa(void)
{
	OpCode::mapa[0X00] = "NOP";
	OpCode::mapa[0X01] = "ACONST_NULL";
	OpCode::mapa[0X02] = "ICONST_M1";
	OpCode::mapa[0X03] = "ICONST_0";
	OpCode::mapa[0X04] = "ICONST_1";
	OpCode::mapa[0X05] = "ICONST_2";
	OpCode::mapa[0X06] = "ICONST_3";
	OpCode::mapa[0X07] = "ICONST_4";
	OpCode::mapa[0X08] = "ICONST_5";
	OpCode::mapa[0X09] = "LCONST_0";
	OpCode::mapa[0X0A] = "LCONST_1";
	OpCode::mapa[0X0B] = "FCONST_0";
	OpCode::mapa[0X0C] = "FCONST_1";
	OpCode::mapa[0X0D] = "FCONST_2";
	OpCode::mapa[0X0E] = "DCONST_0";
	OpCode::mapa[0X0F] = "DCONST_1";
	OpCode::mapa[0X10] = "BIPUSH";
	OpCode::mapa[0X11] = "SIPUSH";
	OpCode::mapa[0X12] = "LDC";
	OpCode::mapa[0X13] = "LDC_W";
	OpCode::mapa[0X14] = "LDC2_W";
	OpCode::mapa[0X15] = "ILOAD";
	OpCode::mapa[0X16] = "LLOAD";
	OpCode::mapa[0X17] = "FLOAD";
	OpCode::mapa[0X18] = "DLOAD";
	OpCode::mapa[0X19] = "ALOAD";
	OpCode::mapa[0X1A] = "ILOAD_0";
	OpCode::mapa[0X1B] = "ILOAD_1";
	OpCode::mapa[0X1C] = "ILOAD_2";
	OpCode::mapa[0X1D] = "ILOAD_3";
	OpCode::mapa[0X1E] = "LLOAD_0";
	OpCode::mapa[0X1F] = "LLOAD_1";
	OpCode::mapa[0X20] = "LLOAD_2";
	OpCode::mapa[0X21] = "LLOAD_3";
	OpCode::mapa[0X22] = "FLOAD_0";
	OpCode::mapa[0X23] = "FLOAD_1";
	OpCode::mapa[0X24] = "FLOAD_2";
	OpCode::mapa[0X25] = "FLOAD_3";
	OpCode::mapa[0X26] = "DLOAD_0";
	OpCode::mapa[0X27] = "DLOAD_1";
	OpCode::mapa[0X28] = "DLOAD_2";
	OpCode::mapa[0X29] = "DLOAD_3";
	OpCode::mapa[0X2A] = "ALOAD_0";
	OpCode::mapa[0X2B] = "ALOAD_1";
	OpCode::mapa[0X2C] = "ALOAD_2";
	OpCode::mapa[0X2D] = "ALOAD_3";
	OpCode::mapa[0X2E] = "IALOAD";
	OpCode::mapa[0X2F] = "LALOAD";
	OpCode::mapa[0X30] = "FALOAD";
	OpCode::mapa[0X31] = "DALOAD";
	OpCode::mapa[0X32] = "AALOAD";
	OpCode::mapa[0X33] = "BALOAD";
	OpCode::mapa[0X34] = "CALOAD";
	OpCode::mapa[0X35] = "SALOAD";
	OpCode::mapa[0X36] = "ISTORE";
	OpCode::mapa[0X37] = "LSTORE";
	OpCode::mapa[0X38] = "FSTORE";
	OpCode::mapa[0X39] = "DSTORE";
	OpCode::mapa[0X3A] = "ASTORE";
	OpCode::mapa[0X3B] = "ISTORE_0";
	OpCode::mapa[0X3C] = "ISTORE_1";
	OpCode::mapa[0X3D] = "ISTORE_2";
	OpCode::mapa[0X3E] = "ISTORE_3";
	OpCode::mapa[0X3F] = "LSTORE_0";
	OpCode::mapa[0X40] = "LSTORE_1";
	OpCode::mapa[0X41] = "LSTORE_2";
	OpCode::mapa[0X42] = "LSTORE_3";
	OpCode::mapa[0X43] = "FSTORE_0";
	OpCode::mapa[0X44] = "FSTORE_1";
	OpCode::mapa[0X45] = "FSTORE_2";
	OpCode::mapa[0X46] = "FSTORE_3";
	OpCode::mapa[0X47] = "DSTORE_0";
	OpCode::mapa[0X48] = "DSTORE_1";
	OpCode::mapa[0X49] = "DSTORE_2";
	OpCode::mapa[0X4A] = "DSTORE_3";
	OpCode::mapa[0X4B] = "ASTORE_0";
	OpCode::mapa[0X4C] = "ASTORE_1";
	OpCode::mapa[0X4D] = "ASTORE_2";
	OpCode::mapa[0X4E] = "ASTORE_3";
	OpCode::mapa[0X4F] = "IASTORE";
	OpCode::mapa[0X50] = "LASTORE";
	OpCode::mapa[0X51] = "FASTORE";
	OpCode::mapa[0X52] = "DASTORE";
	OpCode::mapa[0X53] = "AASTORE";
	OpCode::mapa[0X54] = "BASTORE";
	OpCode::mapa[0X55] = "CASTORE";
	OpCode::mapa[0X56] = "SASTORE";
	OpCode::mapa[0X57] = "POP";
	OpCode::mapa[0X58] = "POP2";
	OpCode::mapa[0X59] = "DUP";
	OpCode::mapa[0X5A] = "DUP_X1";
	OpCode::mapa[0X5B] = "DUP_X2";
	OpCode::mapa[0X5C] = "DUP2";
	OpCode::mapa[0X5D] = "DUP2_X1";
	OpCode::mapa[0X5E] = "DUP2_X2";
	OpCode::mapa[0X5F] = "SWAP";
	OpCode::mapa[0X60] = "IADD";
	OpCode::mapa[0X61] = "LADD";
	OpCode::mapa[0X62] = "FADD";
	OpCode::mapa[0X63] = "DADD";
	OpCode::mapa[0X64] = "ISUB";
	OpCode::mapa[0X65] = "LSUB";
	OpCode::mapa[0X66] = "FSUB";
	OpCode::mapa[0X67] = "DSUB";
	OpCode::mapa[0X68] = "IMUL";
	OpCode::mapa[0X69] = "LMUL";
	OpCode::mapa[0X6A] = "FMUL";
	OpCode::mapa[0X6B] = "DMUL";
	OpCode::mapa[0X6C] = "IDIV";
	OpCode::mapa[0X6D] = "LDIV";
	OpCode::mapa[0X6E] = "FDIV";
	OpCode::mapa[0X6F] = "DDIV";
	OpCode::mapa[0X70] = "IREM";
	OpCode::mapa[0X71] = "LREM";
	OpCode::mapa[0X72] = "FREM";
	OpCode::mapa[0X73] = "DREM";
	OpCode::mapa[0X74] = "INEG";
	OpCode::mapa[0X75] = "LNEG";
	OpCode::mapa[0X76] = "FNEG";
	OpCode::mapa[0X77] = "DNEG";
	OpCode::mapa[0X78] = "ISHL";
	OpCode::mapa[0X79] = "LSHL";
	OpCode::mapa[0X7A] = "ISHR";
	OpCode::mapa[0X7B] = "LSHR";
	OpCode::mapa[0X7C] = "IUSHR";
	OpCode::mapa[0X7D] = "LUSHR";
	OpCode::mapa[0X7E] = "IAND";
	OpCode::mapa[0X7F] = "LAND";
	OpCode::mapa[0X80] = "IOR";
	OpCode::mapa[0X81] = "LOR";
	OpCode::mapa[0X82] = "IXOR";
	OpCode::mapa[0X83] = "LXOR";
	OpCode::mapa[0X84] = "IINC";
	OpCode::mapa[0X85] = "I2L";
	OpCode::mapa[0X86] = "I2F";
	OpCode::mapa[0X87] = "I2D";
	OpCode::mapa[0X88] = "L2I";
	OpCode::mapa[0X89] = "L2F";
	OpCode::mapa[0X8A] = "L2D";
	OpCode::mapa[0X8B] = "F2I";
	OpCode::mapa[0X8C] = "F2L";
	OpCode::mapa[0X8D] = "F2D";
	OpCode::mapa[0X8E] = "D2I";
	OpCode::mapa[0X8F] = "D2L";
	OpCode::mapa[0X90] = "D2F";
	OpCode::mapa[0X91] = "I2B";
	OpCode::mapa[0X92] = "I2C";
	OpCode::mapa[0X93] = "I2S";
	OpCode::mapa[0X94] = "LCMP";
	OpCode::mapa[0X95] = "FCMPL";
	OpCode::mapa[0X96] = "FCMPG";
	OpCode::mapa[0X97] = "DCMPL";
	OpCode::mapa[0X98] = "DCMPG";
	OpCode::mapa[0X99] = "IFEQ";
	OpCode::mapa[0X9A] = "IFNE";
	OpCode::mapa[0X9B] = "IFLT";
	OpCode::mapa[0X9C] = "IFGE";
	OpCode::mapa[0X9D] = "IFGT";
	OpCode::mapa[0X9E] = "IFLE";
	OpCode::mapa[0X9F] = "IF_ICMPEQ";
	OpCode::mapa[0XA0] = "IF_ICMPNE";
	OpCode::mapa[0XA1] = "IF_ICMPLT";
	OpCode::mapa[0XA2] = "IF_ICMPGE";
	OpCode::mapa[0XA3] = "IF_ICMPGT";
	OpCode::mapa[0XA4] = "IF_ICMPLE";
	OpCode::mapa[0XA5] = "IF_ACMPEQ";
	OpCode::mapa[0XA6] = "IF_ACMPNE";
	OpCode::mapa[0XA7] = "GOTO";
	OpCode::mapa[0XA8] = "JSR";
	OpCode::mapa[0XA9] = "RET";
	OpCode::mapa[0XAA] = "TABLESWITCH";
	OpCode::mapa[0XAB] = "LOOKUPSWITCH";
	OpCode::mapa[0XAC] = "IRETURN";
	OpCode::mapa[0XAD] = "LRETURN";
	OpCode::mapa[0XAE] = "FRETURN";
	OpCode::mapa[0XAF] = "DRETURN";
	OpCode::mapa[0XB0] = "ARETURN";
	OpCode::mapa[0XB1] = "RETURN";
	OpCode::mapa[0XB2] = "GETSTATIC";
	OpCode::mapa[0XB3] = "PUTSTATIC";
	OpCode::mapa[0XB4] = "GETFIELD";
	OpCode::mapa[0XB5] = "PUTFIELD";
	OpCode::mapa[0XB6] = "INVOKEVIRTUAL";
	OpCode::mapa[0XB7] = "INVOKESPECIAL";
	OpCode::mapa[0XB8] = "INVOKESTATIC";
	OpCode::mapa[0XB9] = "INVOKEINTERFACE";
	OpCode::mapa[0XBA] = "INVOKEDYNAMIC";
	OpCode::mapa[0XBB] = "NEW";
	OpCode::mapa[0XBC] = "NEWARRAY";
	OpCode::mapa[0XBD] = "ANEWARRAY";
	OpCode::mapa[0XBE] = "ARRAYLENGTH";
	OpCode::mapa[0XBF] = "ATHROW";
	OpCode::mapa[0XC0] = "CHECKCAST";
	OpCode::mapa[0XC1] = "INSTANCEOF";
	OpCode::mapa[0XC2] = "MONITORENTER";
	OpCode::mapa[0XC3] = "MONITOREXIT";
	OpCode::mapa[0XC4] = "WIDE";
	OpCode::mapa[0XC5] = "MULTIANEWARRAY";
	OpCode::mapa[0XC6] = "IFNULL";
	OpCode::mapa[0XC7] = "IFNONNULL";
	OpCode::mapa[0XC8] = "GOTO_W";
	OpCode::mapa[0XC9] = "JSR_W";
	OpCode::mapa[0XCA] = "BREAKPOINT";
	OpCode::mapa[0XFE] = "IMPDEP1";
	OpCode::mapa[0XFF] = "IMPDEP2";
}


#define JAVA_OPCODE_NOP 0x00
#define JAVA_OPCODE_ACONST_NULL 0x01
#define JAVA_OPCODE_ICONST_M1 0x02
#define JAVA_OPCODE_ICONST_0 0x03
#define JAVA_OPCODE_ICONST_1 0x04
#define JAVA_OPCODE_ICONST_2 0x05
#define JAVA_OPCODE_ICONST_3 0x06
#define JAVA_OPCODE_ICONST_4 0x07
#define JAVA_OPCODE_ICONST_5 0x08
#define JAVA_OPCODE_LCONST_0 0x09
#define JAVA_OPCODE_LCONST_1 0x0A
#define JAVA_OPCODE_FCONST_0 0x0B
#define JAVA_OPCODE_FCONST_1 0x0C
#define JAVA_OPCODE_FCONST_2 0x0D
#define JAVA_OPCODE_DCONST_0 0x0E
#define JAVA_OPCODE_DCONST_1 0x0F
#define JAVA_OPCODE_BIPUSH 0x10
#define JAVA_OPCODE_SIPUSH 0x11
#define JAVA_OPCODE_LDC 0x12
#define JAVA_OPCODE_LDC_W 0x13
#define JAVA_OPCODE_LDC2_W 0x14
#define JAVA_OPCODE_ILOAD 0x15
#define JAVA_OPCODE_LLOAD 0x16
#define JAVA_OPCODE_FLOAD 0x17
#define JAVA_OPCODE_DLOAD 0x18
#define JAVA_OPCODE_ALOAD 0x19
#define JAVA_OPCODE_ILOAD_0 0x1A
#define JAVA_OPCODE_ILOAD_1 0x1B
#define JAVA_OPCODE_ILOAD_2 0x1C
#define JAVA_OPCODE_ILOAD_3 0x1D
#define JAVA_OPCODE_LLOAD_0 0x1E
#define JAVA_OPCODE_LLOAD_1 0x1F
#define JAVA_OPCODE_LLOAD_2 0x20
#define JAVA_OPCODE_LLOAD_3 0x21
#define JAVA_OPCODE_FLOAD_0 0x22
#define JAVA_OPCODE_FLOAD_1 0x23
#define JAVA_OPCODE_FLOAD_2 0x24
#define JAVA_OPCODE_FLOAD_3 0x25
#define JAVA_OPCODE_DLOAD_0 0x26
#define JAVA_OPCODE_DLOAD_1 0x27
#define JAVA_OPCODE_DLOAD_2 0x28
#define JAVA_OPCODE_DLOAD_3 0x29
#define JAVA_OPCODE_ALOAD_0 0x2A
#define JAVA_OPCODE_ALOAD_1 0x2B
#define JAVA_OPCODE_ALOAD_2 0x2C
#define JAVA_OPCODE_ALOAD_3 0x2D
#define JAVA_OPCODE_IALOAD 0x2E
#define JAVA_OPCODE_LALOAD 0x2F
#define JAVA_OPCODE_FALOAD 0x30
#define JAVA_OPCODE_DALOAD 0x31
#define JAVA_OPCODE_AALOAD 0x32
#define JAVA_OPCODE_BALOAD 0x33
#define JAVA_OPCODE_CALOAD 0x34
#define JAVA_OPCODE_SALOAD 0x35
#define JAVA_OPCODE_ISTORE 0x36
#define JAVA_OPCODE_LSTORE 0x37
#define JAVA_OPCODE_FSTORE 0x38
#define JAVA_OPCODE_DSTORE 0x39
#define JAVA_OPCODE_ASTORE 0x3A
#define JAVA_OPCODE_ISTORE_0 0x3B
#define JAVA_OPCODE_ISTORE_1 0x3C
#define JAVA_OPCODE_ISTORE_2 0x3D
#define JAVA_OPCODE_ISTORE_3 0x3E
#define JAVA_OPCODE_LSTORE_0 0x3F
#define JAVA_OPCODE_LSTORE_1 0x40
#define JAVA_OPCODE_LSTORE_2 0x41
#define JAVA_OPCODE_LSTORE_3 0x42
#define JAVA_OPCODE_FSTORE_0 0x43
#define JAVA_OPCODE_FSTORE_1 0x44
#define JAVA_OPCODE_FSTORE_2 0x45
#define JAVA_OPCODE_FSTORE_3 0x46
#define JAVA_OPCODE_DSTORE_0 0x47
#define JAVA_OPCODE_DSTORE_1 0x48
#define JAVA_OPCODE_DSTORE_2 0x49
#define JAVA_OPCODE_DSTORE_3 0x4A
#define JAVA_OPCODE_ASTORE_0 0x4B
#define JAVA_OPCODE_ASTORE_1 0x4C
#define JAVA_OPCODE_ASTORE_2 0x4D
#define JAVA_OPCODE_ASTORE_3 0x4E
#define JAVA_OPCODE_IASTORE 0x4F
#define JAVA_OPCODE_LASTORE 0x50
#define JAVA_OPCODE_FASTORE 0x51
#define JAVA_OPCODE_DASTORE 0x52
#define JAVA_OPCODE_AASTORE 0x53
#define JAVA_OPCODE_BASTORE 0x54
#define JAVA_OPCODE_CASTORE 0x55
#define JAVA_OPCODE_SASTORE 0x56

string Code_attribute::ObterMinemonicoOpcode(uint8_t bytecode)
{
	string retorno;
	switch(bytecode)
	{
		case(JAVA_OPCODE_NOP):
		{
			retorno = "NOP";
			return retorno;
		}
		case(JAVA_OPCODE_ACONST_NULL):
		{
			retorno = "ACONST_NULL";
			return retorno;
		}
		case(JAVA_OPCODE_ICONST_M1):
		{
			retorno = "ICONST_M1";
			return retorno;
		}
		case(JAVA_OPCODE_ICONST_0):
		{
			retorno = "ICONST_0";
			return retorno;
		}
		case(JAVA_OPCODE_ICONST_1):
		{
			retorno = "ICONST_1";
			return retorno;
		}
		case(JAVA_OPCODE_ICONST_2):
		{
			retorno = "ICONST_2";
			return retorno;
		}
		case(JAVA_OPCODE_ICONST_3):
		{
			retorno = "ICONST_3";
			return retorno;
		}
		case(JAVA_OPCODE_ICONST_4):
		{
			retorno = "ICONST_4";
			return retorno;
		}
		case(JAVA_OPCODE_ICONST_5):
		{
			retorno = "ICONST_5";
			return retorno;
		}
		case(JAVA_OPCODE_LCONST_0):
		{
			retorno = "LCONST_0";
			return retorno;
		}
		case(JAVA_OPCODE_LCONST_1):
		{
			retorno = "LCONST_1";
			return retorno;
		}
		case(JAVA_OPCODE_FCONST_0):
		{
			retorno = "FCONST_0";
			return retorno;
		}
		case(JAVA_OPCODE_FCONST_1):
		{
			retorno = "FCONST_1";
			return retorno;
		}
		case(JAVA_OPCODE_FCONST_2):
		{
			retorno = "FCONST_2";
			return retorno;
		}
		case(JAVA_OPCODE_DCONST_0):
		{
			retorno = "DCONST_0";
			return retorno;
		}
		case(JAVA_OPCODE_DCONST_1):
		{
			retorno = "DCONST_1";
			return retorno;
		}
		case(JAVA_OPCODE_BIPUSH):
		{
			retorno = "BIPUSH";
			return retorno;
		}
		case(JAVA_OPCODE_SIPUSH):
		{
			retorno = "SIPUSH";
			return retorno;
		}
		case(JAVA_OPCODE_LDC):
		{
			retorno = "LDC";
			return retorno;
		}
		case(JAVA_OPCODE_LDC_W):
		{
			retorno = "LDC_W";
			return retorno;
		}
		case(JAVA_OPCODE_LDC2_W):
		{
			retorno = "LDC2_W";
			return retorno;
		}
		case(JAVA_OPCODE_ILOAD):
		{
			retorno = "ILOAD";
			return retorno;
		}
		case(JAVA_OPCODE_LLOAD):
		{
			retorno = "LLOAD";
			return retorno;
		}
		case(JAVA_OPCODE_FLOAD):
		{
			retorno = "FLOAD";
			return retorno;
		}
		case(JAVA_OPCODE_DLOAD):
		{
			retorno = "DLOAD";
			return retorno;
		}
		case(JAVA_OPCODE_ALOAD):
		{
			retorno = "ALOAD";
			return retorno;
		}
		case(JAVA_OPCODE_ILOAD_0):
		{
			retorno = "ILOAD_0";
			return retorno;
		}
		case(JAVA_OPCODE_ILOAD_1):
		{
			retorno = "ILOAD_1";
			return retorno;
		}
		case(JAVA_OPCODE_ILOAD_2):
		{
			retorno = "ILOAD_2";
			return retorno;
		}
		case(JAVA_OPCODE_ILOAD_3):
		{
			retorno = "ILOAD_3";
			return retorno;
		}
		case(JAVA_OPCODE_LLOAD_0):
		{
			retorno = "LLOAD_0";
			return retorno;
		}
		case(JAVA_OPCODE_LLOAD_1):
		{
			retorno = "LLOAD_1";
			return retorno;
		}
		case(JAVA_OPCODE_LLOAD_2):
		{
			retorno = "LLOAD_2";
			return retorno;
		}
		case(JAVA_OPCODE_LLOAD_3):
		{
			retorno="LLOAD_3";
			return retorno;
		}
		case(JAVA_OPCODE_FLOAD_0):
		{
			retorno="FLOAD_0";
			return retorno;
		}
		case(JAVA_OPCODE_FLOAD_1):
		{
			retorno="FLOAD_1";
			return retorno;
		}
		case(JAVA_OPCODE_FLOAD_2):
		{
			retorno="FLOAD_2";
			return retorno;
		}
		case(JAVA_OPCODE_FLOAD_3):
		{
			retorno="FLOAD_3";
			return retorno;
		}
		case(JAVA_OPCODE_DLOAD_0):
		{
			retorno="DLOAD_0";
			return retorno;
		}
		case(JAVA_OPCODE_DLOAD_1):
		{
			retorno="DLOAD_1";
			return retorno;
		}
		case(JAVA_OPCODE_DLOAD_2):
		{
			retorno="DLOAD_2";
			return retorno;
		}
		case(JAVA_OPCODE_DLOAD_3):
		{
			retorno="DLOAD_3";
			return retorno;
		}
		case(JAVA_OPCODE_ALOAD_0):
		{
			retorno="ALOAD_0";
			return retorno;
		}
		case(JAVA_OPCODE_ALOAD_1):
		{
			retorno="ALOAD_1";
			return retorno;
		}
		case(JAVA_OPCODE_ALOAD_2):
		{
			retorno="ALOAD_2";
			return retorno;
		}
		case(JAVA_OPCODE_ALOAD_3):
		{
			retorno="ALOAD_3";
			return retorno;
		}
		case(JAVA_OPCODE_IALOAD):
		{
			retorno="IALOAD";
			return retorno;
		}
		case(JAVA_OPCODE_LALOAD):
		{
			retorno="LALOAD";
			return retorno;
		}
		case(JAVA_OPCODE_FALOAD):
		{
			retorno="FALOAD";
			return retorno;
		}
		case(JAVA_OPCODE_DALOAD):
		{
			retorno="DALOAD";
			return retorno;
		}
		case(JAVA_OPCODE_AALOAD):
		{
			retorno="AALOAD";
			return retorno;
		}
		case(JAVA_OPCODE_BALOAD):
		{
			retorno="BALOAD";
			return retorno;
		}
		case(JAVA_OPCODE_CALOAD):
		{
			retorno="CALOAD";
			return retorno;
		}
		case(JAVA_OPCODE_SALOAD):
		{
			retorno="SALOAD";
			return retorno;
		}
		case(JAVA_OPCODE_ISTORE):
		{
			retorno="ISTORE";
			return retorno;
		}
		case(JAVA_OPCODE_LSTORE):
		{
			retorno="LSTORE";
			return retorno;
		}
		case(JAVA_OPCODE_FSTORE):
		{
			retorno="FSTORE";
			return retorno;
		}
		case(JAVA_OPCODE_DSTORE):
		{
			retorno="DSTORE";
			return retorno;
		}
		case(JAVA_OPCODE_ASTORE):
		{
			retorno="ASTORE";
			return retorno;
		}
		case(JAVA_OPCODE_ISTORE_0):
		{
			retorno="ISTORE_0";
			return retorno;
		}
		case(JAVA_OPCODE_ISTORE_1):
		{
			retorno="ISTORE_1";
			return retorno;
		}
		case(JAVA_OPCODE_ISTORE_2):
		{
			retorno="ISTORE_2";
			return retorno;
		}
		case(JAVA_OPCODE_ISTORE_3):
		{
			retorno="ISTORE_3";
			return retorno;
		}
		case(JAVA_OPCODE_LSTORE_0):
		{
			retorno="LSTORE_0";
			return retorno;
		}
		case(JAVA_OPCODE_LSTORE_1):
		{
			retorno="LSTORE_1";
			return retorno;
		}
		case(JAVA_OPCODE_LSTORE_2):
		{
			retorno="LSTORE_2";
			return retorno;
		}
		case(JAVA_OPCODE_LSTORE_3):
		{
			retorno="LSTORE_3";
			return retorno;
		}
		case(JAVA_OPCODE_FSTORE_0):
		{
			retorno="FSTORE_0";
			return retorno;
		}
		case(JAVA_OPCODE_FSTORE_1):
		{
			retorno="FSTORE_1";
			return retorno;
		}
		case(JAVA_OPCODE_FSTORE_2):
		{
			retorno="FSTORE_2";
			return retorno;
		}
		case(JAVA_OPCODE_FSTORE_3):
		{
			retorno="FSTORE_3";
			return retorno;
		}
		case(JAVA_OPCODE_DSTORE_0):
		{
			retorno="DSTORE_0";
			return retorno;
		}
		case(JAVA_OPCODE_DSTORE_1):
		{
			retorno="DSTORE_1";
			return retorno;
		}
		case(JAVA_OPCODE_DSTORE_2):
		{
			retorno="DSTORE_2";
			return retorno;
		}
		case(JAVA_OPCODE_DSTORE_3):
		{
			retorno="DSTORE_3";
			return retorno;
		}
		case(JAVA_OPCODE_ASTORE_0):
		{
			retorno="ASTORE_0";
			return retorno;
		}
		case(JAVA_OPCODE_ASTORE_1):
		{
			retorno="ASTORE_1";
			return retorno;
		}
		case(JAVA_OPCODE_ASTORE_2):
		{
			retorno="ASTORE_2";
			return retorno;
		}
		case(JAVA_OPCODE_ASTORE_3):
		{
			retorno="ASTORE_3";
			return retorno;
		}
		case(JAVA_OPCODE_IASTORE):
		{
			retorno="IASTORE";
			return retorno;
		}
		case(JAVA_OPCODE_LASTORE):
		{
			retorno="LASTORE";
			return retorno;
		}
		case(JAVA_OPCODE_FASTORE):
		{
			retorno="FASTORE";
			return retorno;
		}
		case(JAVA_OPCODE_DASTORE):
		{
			retorno="DASTORE";
			return retorno;
		}
		case(JAVA_OPCODE_AASTORE):
		{
			retorno="AASTORE";
			return retorno;
		}
		case(JAVA_OPCODE_BASTORE):
		{
			retorno="BASTORE";
			return retorno;
		}
		case(JAVA_OPCODE_CASTORE):
		{
			retorno="CASTORE";
			return retorno;
		}
		case(JAVA_OPCODE_SASTORE):
		{
			retorno="SASTORE";
			return retorno;
		}
		default:
		{
			retorno= "OPCODE DESCONHECIDO";
			return retorno;
		}
	}
}

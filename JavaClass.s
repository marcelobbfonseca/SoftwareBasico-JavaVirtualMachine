	.file	"JavaClass.cpp"
	.section	.rodata
.LC0:
	.string	"[ERRO]"
	.section	.text._ZN4ErroC2EPKc,"axG",@progbits,_ZN4ErroC5EPKc,comdat
	.align 2
	.weak	_ZN4ErroC2EPKc
	.type	_ZN4ErroC2EPKc, @function
_ZN4ErroC2EPKc:
.LFB876:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA876
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$104, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -104(%rbp)
	movq	%rsi, -112(%rbp)
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
.LEHB0:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1Ev
.LEHE0:
	leaq	-49(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev
	leaq	-49(%rbp), %rdx
	leaq	-96(%rbp), %rax
	movl	$.LC0, %esi
	movq	%rax, %rdi
.LEHB1:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_
.LEHE1:
	leaq	-49(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev
	leaq	-48(%rbp), %rax
	movq	-112(%rbp), %rdx
	leaq	-96(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB2:
	call	_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EERKS8_PKS5_
.LEHE2:
	movq	-104(%rbp), %rax
	leaq	-48(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB3:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEaSERKS4_
.LEHE3:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
.LEHB4:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev
.LEHE4:
	leaq	-96(%rbp), %rax
	movq	%rax, %rdi
.LEHB5:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev
.LEHE5:
	jmp	.L10
.L6:
	movq	%rax, %rbx
	leaq	-49(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev
	jmp	.L3
.L9:
	movq	%rax, %rbx
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev
	jmp	.L5
.L8:
	movq	%rax, %rbx
.L5:
	leaq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev
	jmp	.L3
.L7:
	movq	%rax, %rbx
.L3:
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB6:
	call	_Unwind_Resume
.LEHE6:
.L10:
	addq	$104, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE876:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table._ZN4ErroC2EPKc,"aG",@progbits,_ZN4ErroC5EPKc,comdat
.LLSDA876:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE876-.LLSDACSB876
.LLSDACSB876:
	.uleb128 .LEHB0-.LFB876
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB1-.LFB876
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L6-.LFB876
	.uleb128 0
	.uleb128 .LEHB2-.LFB876
	.uleb128 .LEHE2-.LEHB2
	.uleb128 .L8-.LFB876
	.uleb128 0
	.uleb128 .LEHB3-.LFB876
	.uleb128 .LEHE3-.LEHB3
	.uleb128 .L9-.LFB876
	.uleb128 0
	.uleb128 .LEHB4-.LFB876
	.uleb128 .LEHE4-.LEHB4
	.uleb128 .L8-.LFB876
	.uleb128 0
	.uleb128 .LEHB5-.LFB876
	.uleb128 .LEHE5-.LEHB5
	.uleb128 .L7-.LFB876
	.uleb128 0
	.uleb128 .LEHB6-.LFB876
	.uleb128 .LEHE6-.LEHB6
	.uleb128 0
	.uleb128 0
.LLSDACSE876:
	.section	.text._ZN4ErroC2EPKc,"axG",@progbits,_ZN4ErroC5EPKc,comdat
	.size	_ZN4ErroC2EPKc, .-_ZN4ErroC2EPKc
	.weak	_ZN4ErroC1EPKc
	.set	_ZN4ErroC1EPKc,_ZN4ErroC2EPKc
	.section	.rodata
.LC1:
	.string	"Erro na leitura do arquivo!"
	.text
	.globl	_ZN7Leitura11LerAtributoEPviP8_IO_FILE
	.type	_ZN7Leitura11LerAtributoEPviP8_IO_FILE, @function
_ZN7Leitura11LerAtributoEPviP8_IO_FILE:
.LFB878:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA878
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 13, -24
	.cfi_offset 12, -32
	.cfi_offset 3, -40
	movq	%rdi, -40(%rbp)
	movl	%esi, -44(%rbp)
	movq	%rdx, -56(%rbp)
	movl	-44(%rbp), %eax
	movslq	%eax, %rsi
	movq	-56(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %rcx
	movl	$1, %edx
	movq	%rax, %rdi
.LEHB7:
	call	fread
.LEHE7:
	testq	%rax, %rax
	sete	%al
	testb	%al, %al
	je	.L17
	movl	$8, %edi
	call	__cxa_allocate_exception
	movq	%rax, %rbx
	movl	$32, %edi
.LEHB8:
	call	_Znwm
.LEHE8:
	movq	%rax, %r12
	movl	$.LC1, %esi
	movq	%r12, %rdi
.LEHB9:
	call	_ZN4ErroC1EPKc
.LEHE9:
	movq	%r12, (%rbx)
	movl	$0, %edx
	movl	$_ZTIP4Erro, %esi
	movq	%rbx, %rdi
.LEHB10:
	call	__cxa_throw
.L16:
	movq	%rax, %r13
	movq	%r12, %rdi
	call	_ZdlPv
	movq	%r13, %r12
	jmp	.L14
.L15:
	movq	%rax, %r12
.L14:
	movq	%rbx, %rdi
	call	__cxa_free_exception
	movq	%r12, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume
.LEHE10:
.L17:
	nop
	addq	$40, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE878:
	.section	.gcc_except_table,"a",@progbits
.LLSDA878:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE878-.LLSDACSB878
.LLSDACSB878:
	.uleb128 .LEHB7-.LFB878
	.uleb128 .LEHE7-.LEHB7
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB8-.LFB878
	.uleb128 .LEHE8-.LEHB8
	.uleb128 .L15-.LFB878
	.uleb128 0
	.uleb128 .LEHB9-.LFB878
	.uleb128 .LEHE9-.LEHB9
	.uleb128 .L16-.LFB878
	.uleb128 0
	.uleb128 .LEHB10-.LFB878
	.uleb128 .LEHE10-.LEHB10
	.uleb128 0
	.uleb128 0
.LLSDACSE878:
	.text
	.size	_ZN7Leitura11LerAtributoEPviP8_IO_FILE, .-_ZN7Leitura11LerAtributoEPviP8_IO_FILE
	.section	.rodata
.LC2:
	.string	"rb"
.LC3:
	.string	"Falha na abertura do arquivo!"
	.text
	.align 2
	.globl	_ZN9JavaClass10LerArquivoENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
	.type	_ZN9JavaClass10LerArquivoENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE, @function
_ZN9JavaClass10LerArquivoENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE:
.LFB879:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA879
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 13, -24
	.cfi_offset 12, -32
	.cfi_offset 3, -40
	movq	%rdi, -56(%rbp)
	movq	%rsi, -64(%rbp)
	movq	-64(%rbp), %rax
	movq	%rax, %rdi
.LEHB11:
	call	_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE5c_strEv
	movl	$.LC2, %esi
	movq	%rax, %rdi
	call	fopen
.LEHE11:
	movq	%rax, -40(%rbp)
	cmpq	$0, -40(%rbp)
	jne	.L19
	movl	$8, %edi
	call	__cxa_allocate_exception
	movq	%rax, %rbx
	movl	$32, %edi
.LEHB12:
	call	_Znwm
.LEHE12:
	movq	%rax, %r12
	movl	$.LC3, %esi
	movq	%r12, %rdi
.LEHB13:
	call	_ZN4ErroC1EPKc
.LEHE13:
	movq	%r12, (%rbx)
	movl	$0, %edx
	movl	$_ZTIP4Erro, %esi
	movq	%rbx, %rdi
.LEHB14:
	call	__cxa_throw
.L19:
	movq	-56(%rbp), %rsi
	movq	-40(%rbp), %rdx
	movq	-56(%rbp), %rax
	movq	%rdx, %rcx
	movl	$4, %edx
	movq	%rax, %rdi
	call	_ZN9JavaClass11LerAtributoEPviP8_IO_FILE
	movq	-56(%rbp), %rax
	leaq	4(%rax), %rsi
	movq	-40(%rbp), %rdx
	movq	-56(%rbp), %rax
	movq	%rdx, %rcx
	movl	$2, %edx
	movq	%rax, %rdi
	call	_ZN9JavaClass11LerAtributoEPviP8_IO_FILE
	movq	-56(%rbp), %rax
	leaq	6(%rax), %rsi
	movq	-40(%rbp), %rdx
	movq	-56(%rbp), %rax
	movq	%rdx, %rcx
	movl	$2, %edx
	movq	%rax, %rdi
	call	_ZN9JavaClass11LerAtributoEPviP8_IO_FILE
	movq	-56(%rbp), %rax
	leaq	8(%rax), %rsi
	movq	-40(%rbp), %rdx
	movq	-56(%rbp), %rax
	movq	%rdx, %rcx
	movl	$2, %edx
	movq	%rax, %rdi
	call	_ZN9JavaClass11LerAtributoEPviP8_IO_FILE
	movq	-56(%rbp), %rax
	leaq	40(%rax), %rsi
	movq	-40(%rbp), %rdx
	movq	-56(%rbp), %rax
	movq	%rdx, %rcx
	movl	$2, %edx
	movq	%rax, %rdi
	call	_ZN9JavaClass11LerAtributoEPviP8_IO_FILE
	movq	-56(%rbp), %rax
	leaq	42(%rax), %rsi
	movq	-40(%rbp), %rdx
	movq	-56(%rbp), %rax
	movq	%rdx, %rcx
	movl	$2, %edx
	movq	%rax, %rdi
	call	_ZN9JavaClass11LerAtributoEPviP8_IO_FILE
	movq	-56(%rbp), %rax
	leaq	44(%rax), %rsi
	movq	-40(%rbp), %rdx
	movq	-56(%rbp), %rax
	movq	%rdx, %rcx
	movl	$2, %edx
	movq	%rax, %rdi
	call	_ZN9JavaClass11LerAtributoEPviP8_IO_FILE
	jmp	.L24
.L23:
	movq	%rax, %r13
	movq	%r12, %rdi
	call	_ZdlPv
	movq	%r13, %r12
	jmp	.L21
.L22:
	movq	%rax, %r12
.L21:
	movq	%rbx, %rdi
	call	__cxa_free_exception
	movq	%r12, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume
.LEHE14:
.L24:
	addq	$40, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE879:
	.section	.gcc_except_table
.LLSDA879:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE879-.LLSDACSB879
.LLSDACSB879:
	.uleb128 .LEHB11-.LFB879
	.uleb128 .LEHE11-.LEHB11
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB12-.LFB879
	.uleb128 .LEHE12-.LEHB12
	.uleb128 .L22-.LFB879
	.uleb128 0
	.uleb128 .LEHB13-.LFB879
	.uleb128 .LEHE13-.LEHB13
	.uleb128 .L23-.LFB879
	.uleb128 0
	.uleb128 .LEHB14-.LFB879
	.uleb128 .LEHE14-.LEHB14
	.uleb128 0
	.uleb128 0
.LLSDACSE879:
	.text
	.size	_ZN9JavaClass10LerArquivoENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE, .-_ZN9JavaClass10LerArquivoENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
	.section	.text._ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EERKS8_PKS5_,"axG",@progbits,_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EERKS8_PKS5_,comdat
	.weak	_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EERKS8_PKS5_
	.type	_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EERKS8_PKS5_, @function
_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EERKS8_PKS5_:
.LFB911:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA911
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB15:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1ERKS4_
.LEHE15:
	movq	-40(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB16:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE6appendEPKc
.LEHE16:
	jmp	.L29
.L28:
	movq	%rax, %rbx
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB17:
	call	_Unwind_Resume
.LEHE17:
.L29:
	movq	-24(%rbp), %rax
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE911:
	.section	.gcc_except_table
.LLSDA911:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE911-.LLSDACSB911
.LLSDACSB911:
	.uleb128 .LEHB15-.LFB911
	.uleb128 .LEHE15-.LEHB15
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB16-.LFB911
	.uleb128 .LEHE16-.LEHB16
	.uleb128 .L28-.LFB911
	.uleb128 0
	.uleb128 .LEHB17-.LFB911
	.uleb128 .LEHE17-.LEHB17
	.uleb128 0
	.uleb128 0
.LLSDACSE911:
	.section	.text._ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EERKS8_PKS5_,"axG",@progbits,_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EERKS8_PKS5_,comdat
	.size	_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EERKS8_PKS5_, .-_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EERKS8_PKS5_
	.weak	_ZTIP4Erro
	.section	.rodata._ZTIP4Erro,"aG",@progbits,_ZTIP4Erro,comdat
	.align 8
	.type	_ZTIP4Erro, @object
	.size	_ZTIP4Erro, 32
_ZTIP4Erro:
	.quad	_ZTVN10__cxxabiv119__pointer_type_infoE+16
	.quad	_ZTSP4Erro
	.long	0
	.zero	4
	.quad	_ZTI4Erro
	.weak	_ZTSP4Erro
	.section	.rodata._ZTSP4Erro,"aG",@progbits,_ZTSP4Erro,comdat
	.type	_ZTSP4Erro, @object
	.size	_ZTSP4Erro, 7
_ZTSP4Erro:
	.string	"P4Erro"
	.weak	_ZTI4Erro
	.section	.rodata._ZTI4Erro,"aG",@progbits,_ZTI4Erro,comdat
	.align 8
	.type	_ZTI4Erro, @object
	.size	_ZTI4Erro, 16
_ZTI4Erro:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTS4Erro
	.weak	_ZTS4Erro
	.section	.rodata._ZTS4Erro,"aG",@progbits,_ZTS4Erro,comdat
	.type	_ZTS4Erro, @object
	.size	_ZTS4Erro, 6
_ZTS4Erro:
	.string	"4Erro"
	.ident	"GCC: (Debian 5.3.1-14) 5.3.1 20160409"
	.section	.note.GNU-stack,"",@progbits

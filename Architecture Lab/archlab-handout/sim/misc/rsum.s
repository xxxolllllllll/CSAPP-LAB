	.file	"rsum.c"
	.text
	.globl	rsum_arr
	.type	rsum_arr, @function
rsum_arr:
.LFB0:
	.cfi_startproc
	testl	%esi, %esi
	jne	.L8
	movl	$0, %eax
	ret
.L8:
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	(%rdi), %rbx
	subl	$1, %esi
	addq	$8, %rdi
	call	rsum_arr
	addq	%rbx, %rax
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE0:
	.size	rsum_arr, .-rsum_arr
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits

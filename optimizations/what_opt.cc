// Based on:
// https://i.redd.it/lwin56fisdsz.png

// The comment in the image above is:

// "I don't know what I did but it works"
// "Please don't modify it"

// This makes a good example to feed through a compiler and see what the optimizer can do.
// On my mac using

//➜  ~  $ g++ --version
//Configured with: --prefix=/Library/Developer/CommandLineTools/usr --with-gxx-include-dir=/usr/include/c++/4.2.1
//Apple LLVM version 8.0.0 (clang-800.0.42.1)
//Target: x86_64-apple-darwin15.6.0
//Thread model: posix
//InstalledDir: /Library/Developer/CommandLineTools/usr/bin

// At no optimization the body comes out as:

// 	.section	__TEXT,__text,regular,pure_instructions
// 	.macosx_version_min 10, 11
// 	.globl	__Z6squarei
// 	.align	4, 0x90
// __Z6squarei:                            ## @_Z6squarei
// 	.cfi_startproc
// ## BB#0:
// 	pushq	%rbp
// Ltmp0:
// 	.cfi_def_cfa_offset 16
// Ltmp1:
// 	.cfi_offset %rbp, -16
// 	movq	%rsp, %rbp
// Ltmp2:
// 	.cfi_def_cfa_register %rbp
// 	movl	%edi, -4(%rbp)
// 	movl	$0, -8(%rbp)
// LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
// 	movl	-8(%rbp), %eax
// 	movl	-4(%rbp), %ecx
// 	imull	-4(%rbp), %ecx
// 	cmpl	%ecx, %eax
// 	jne	LBB0_3
// ## BB#2:
// 	movl	-8(%rbp), %eax
// 	popq	%rbp
// 	retq
// LBB0_3:                                 ##   in Loop: Header=BB0_1 Depth=1
// 	movl	-8(%rbp), %eax
// 	addl	$1, %eax
// 	movl	%eax, -8(%rbp)
// 	jmp	LBB0_1
// 	.cfi_endproc

// 	.globl	_main
// 	.align	4, 0x90
// _main:                                  ## @main
// 	.cfi_startproc
// ## BB#0:
// 	pushq	%rbp
// Ltmp3:
// 	.cfi_def_cfa_offset 16
// Ltmp4:
// 	.cfi_offset %rbp, -16
// 	movq	%rsp, %rbp
// Ltmp5:
// 	.cfi_def_cfa_register %rbp
// 	subq	$16, %rsp
// 	movl	$32, %edi
// 	movl	$0, -4(%rbp)
// 	callq	__Z6squarei
// 	movl	%eax, -8(%rbp)
// 	movl	-8(%rbp), %eax
// 	addq	$16, %rsp
// 	popq	%rbp
// 	retq
// 	.cfi_endproc


// .subsections_via_symbols


// When optimized (-O)

// 	.section	__TEXT,__text,regular,pure_instructions
// 	.macosx_version_min 10, 11
// 	.globl	__Z6squarei
// 	.align	4, 0x90
// __Z6squarei:                            ## @_Z6squarei
// 	.cfi_startproc
// ## BB#0:
// 	pushq	%rbp
// Ltmp0:
// 	.cfi_def_cfa_offset 16
// Ltmp1:
// 	.cfi_offset %rbp, -16
// 	movq	%rsp, %rbp
// Ltmp2:
// 	.cfi_def_cfa_register %rbp
// 	imull	%edi, %edi
// 	movl	%edi, %eax
// 	popq	%rbp
// 	retq
// 	.cfi_endproc

// 	.globl	_main
// 	.align	4, 0x90
// _main:                                  ## @main
// 	.cfi_startproc
// ## BB#0:
// 	pushq	%rbp
// Ltmp3:
// 	.cfi_def_cfa_offset 16
// Ltmp4:
// 	.cfi_offset %rbp, -16
// 	movq	%rsp, %rbp
// Ltmp5:
// 	.cfi_def_cfa_register %rbp
// 	movl	$1024, %eax             ## imm = 0x400
// 	popq	%rbp
// 	retq
// 	.cfi_endproc


// .subsections_via_symbols


int square(int n) {
  int k = 0;
  while(true) {
    if(k == n*n) {
      return k;
    }
    k++;
  }
}

int main(void) {

  int x = square(32);

  return x;

}

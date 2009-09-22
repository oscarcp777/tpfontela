	.file	1 "TP0.c"
	.section .mdebug.abi32
	.previous
	.abicalls
	.rdata
	.align	2
$LC0:
	.ascii	"Organizacion de Computadoras - 6620\n"
	.ascii	"\tTP0 - Version 1.0.0 \n"
	.ascii	" Donikian Santiago, Dubini Richard \n\000"
	.globl	version
	.data
	.align	2
	.type	version, @object
	.size	version, 4
version:
	.word	$LC0
	.rdata
	.align	2
$LC1:
	.ascii	"Vhd:b:f:s\000"
	.globl	modifiers
	.data
	.align	2
	.type	modifiers, @object
	.size	modifiers, 4
modifiers:
	.word	$LC1
	.rdata
	.align	2
$LC2:
	.ascii	"Version\000"
	.align	2
$LC3:
	.ascii	"help\000"
	.align	2
$LC4:
	.ascii	"delimiter\000"
	.align	2
$LC5:
	.ascii	"bytes\000"
	.align	2
$LC6:
	.ascii	"field\000"
	.align	2
$LC7:
	.ascii	"ignore\000"
	.data
	.align	2
	.type	long_options, @object
	.size	long_options, 112
long_options:
	.word	$LC2
	.word	0
	.word	0
	.word	86
	.word	$LC3
	.word	0
	.word	0
	.word	104
	.word	$LC4
	.word	1
	.word	0
	.word	100
	.word	$LC5
	.word	1
	.word	0
	.word	98
	.word	$LC6
	.word	1
	.word	0
	.word	102
	.word	$LC7
	.word	0
	.word	0
	.word	115
	.word	0
	.word	0
	.word	0
	.word	0
	.globl	posicionesArchivos
	.align	2
	.type	posicionesArchivos, @object
	.size	posicionesArchivos, 40
posicionesArchivos:
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.globl	rango
	.align	2
	.type	rango, @object
	.size	rango, 40
rango:
	.word	-5
	.word	-5
	.word	-5
	.word	-5
	.word	-5
	.word	-5
	.word	-5
	.word	-5
	.word	-5
	.word	-5
	.rdata
	.align	2
$LC8:
	.ascii	"\000"
	.globl	filename
	.data
	.align	2
	.type	filename, @object
	.size	filename, 4
filename:
	.word	$LC8
	.globl	numParameters
	.globl	numParameters
	.section	.bss
	.align	2
	.type	numParameters, @object
	.size	numParameters, 4
numParameters:
	.space	4
	.rdata
	.align	2
$LC9:
	.ascii	"\t\000"
	.space	8
	.align	2
$LC10:
	.ascii	"r\000"
	.align	2
$LC11:
	.ascii	"No se puede abrir el archivo!! %s!\n\000"
	.text
	.align	2
	.globl	main
	.ent	main
main:
	.frame	$fp,160,$ra		# vars= 120, regs= 3/0, args= 16, extra= 8
	.mask	0xd0000000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$t9
	.set	reorder
	subu	$sp,$sp,160
	.cprestore 16
	sw	$ra,152($sp)
	sw	$fp,148($sp)
	sw	$gp,144($sp)
	move	$fp,$sp
	sw	$a0,160($fp)
	sw	$a1,164($fp)
	sw	$zero,112($fp)
	lhu	$v0,$LC9
	sh	$v0,120($fp)
	sh	$zero,122($fp)
	sh	$zero,124($fp)
	sh	$zero,126($fp)
	sh	$zero,128($fp)
	addu	$v0,$fp,120
	la	$a0,oflags+4
	move	$a1,$v0
	li	$a2,10			# 0xa
	la	$t9,memcpy
	jal	$ra,$t9
	lw	$a0,160($fp)
	lw	$a1,164($fp)
	addu	$a2,$fp,24
	la	$t9,getOptions
	jal	$ra,$t9
	beq	$v0,$zero,$L18
	li	$v0,-1			# 0xffffffffffffffff
	sw	$v0,136($fp)
	b	$L17
$L18:
	la	$t9,validateCommand
	jal	$ra,$t9
	beq	$v0,$zero,$L19
	li	$v0,-1			# 0xffffffffffffffff
	sw	$v0,136($fp)
	b	$L17
$L19:
	lw	$v0,oflags+132
	bne	$v0,$zero,$L20
	addu	$v0,$fp,32
	move	$a0,$v0
	li	$a1,80			# 0x50
	la	$a2,__sF
	la	$t9,fgets
	jal	$ra,$t9
	lw	$v0,oflags+72
	beq	$v0,$zero,$L21
	la	$a0,oflags+76
	la	$t9,validateRange
	jal	$ra,$t9
	bne	$v0,$zero,$L22
	la	$t9,help
	jal	$ra,$t9
	li	$v0,-1			# 0xffffffffffffffff
	sw	$v0,136($fp)
	b	$L17
$L22:
	addu	$v0,$fp,32
	move	$a0,$v0
	la	$t9,listFields
	jal	$ra,$t9
	b	$L28
$L21:
	lw	$v1,oflags+16
	li	$v0,1			# 0x1
	bne	$v1,$v0,$L28
	la	$a0,oflags+20
	la	$t9,validateRange
	jal	$ra,$t9
	bne	$v0,$zero,$L26
	la	$t9,help
	jal	$ra,$t9
	li	$v0,-1			# 0xffffffffffffffff
	sw	$v0,136($fp)
	b	$L17
$L26:
	addu	$v0,$fp,32
	move	$a0,$v0
	la	$t9,listBytes
	jal	$ra,$t9
	b	$L28
$L20:
	sw	$zero,112($fp)
$L29:
	lw	$v0,112($fp)
	slt	$v0,$v0,10
	bne	$v0,$zero,$L32
	b	$L28
$L32:
	lw	$v0,112($fp)
	sll	$v1,$v0,2
	la	$v0,posicionesArchivos
	addu	$v0,$v1,$v0
	lw	$v1,0($v0)
	li	$v0,-1			# 0xffffffffffffffff
	beq	$v1,$v0,$L31
	lw	$v0,112($fp)
	sll	$v1,$v0,2
	la	$v0,posicionesArchivos
	addu	$v0,$v1,$v0
	lw	$v0,0($v0)
	sll	$v1,$v0,2
	lw	$v0,164($fp)
	addu	$v0,$v1,$v0
	lw	$v0,0($v0)
	sw	$v0,filename
	lw	$a0,filename
	la	$a1,$LC10
	la	$t9,fopen
	jal	$ra,$t9
	sw	$v0,116($fp)
	lw	$v0,116($fp)
	bne	$v0,$zero,$L34
	la	$a0,__sF+176
	la	$a1,$LC11
	lw	$a2,filename
	la	$t9,fprintf
	jal	$ra,$t9
	li	$v0,-1			# 0xffffffffffffffff
	sw	$v0,136($fp)
	b	$L17
$L34:
	.set	noreorder
	nop
	.set	reorder
$L35:
	addu	$v0,$fp,32
	move	$a0,$v0
	li	$a1,80			# 0x50
	lw	$a2,116($fp)
	la	$t9,fgets
	jal	$ra,$t9
	bne	$v0,$zero,$L37
	b	$L36
$L37:
	lw	$v0,oflags+72
	beq	$v0,$zero,$L38
	la	$a0,oflags+76
	la	$t9,validateRange
	jal	$ra,$t9
	bne	$v0,$zero,$L39
	la	$t9,help
	jal	$ra,$t9
	li	$v0,-1			# 0xffffffffffffffff
	sw	$v0,136($fp)
	b	$L17
$L39:
	addu	$v0,$fp,32
	move	$a0,$v0
	la	$t9,listFields
	jal	$ra,$t9
	b	$L35
$L38:
	lw	$v1,oflags+16
	li	$v0,1			# 0x1
	bne	$v1,$v0,$L35
	la	$a0,oflags+20
	la	$t9,validateRange
	jal	$ra,$t9
	bne	$v0,$zero,$L43
	la	$t9,help
	jal	$ra,$t9
	li	$v0,-1			# 0xffffffffffffffff
	sw	$v0,136($fp)
	b	$L17
$L43:
	addu	$v0,$fp,32
	move	$a0,$v0
	la	$t9,listBytes
	jal	$ra,$t9
	b	$L35
$L36:
	lw	$a0,116($fp)
	la	$t9,fclose
	jal	$ra,$t9
$L31:
	lw	$v0,112($fp)
	addu	$v0,$v0,1
	sw	$v0,112($fp)
	b	$L29
$L28:
	sw	$zero,136($fp)
$L17:
	lw	$v0,136($fp)
	move	$sp,$fp
	lw	$ra,152($sp)
	lw	$fp,148($sp)
	addu	$sp,$sp,160
	j	$ra
	.end	main
	.size	main, .-main
	.align	2
	.globl	validateCommand
	.ent	validateCommand
validateCommand:
	.frame	$fp,48,$ra		# vars= 8, regs= 3/0, args= 16, extra= 8
	.mask	0xd0000000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$t9
	.set	reorder
	subu	$sp,$sp,48
	.cprestore 16
	sw	$ra,40($sp)
	sw	$fp,36($sp)
	sw	$gp,32($sp)
	move	$fp,$sp
	lw	$v1,oflags
	li	$v0,1			# 0x1
	bne	$v1,$v0,$L46
	lw	$v0,oflags+72
	bne	$v0,$zero,$L46
	la	$t9,help
	jal	$ra,$t9
	li	$v0,-1			# 0xffffffffffffffff
	sw	$v0,24($fp)
	b	$L45
$L46:
	lw	$v1,oflags+16
	li	$v0,1			# 0x1
	bne	$v1,$v0,$L47
	lw	$v1,oflags+72
	li	$v0,1			# 0x1
	bne	$v1,$v0,$L47
	la	$t9,help
	jal	$ra,$t9
	li	$v0,-1			# 0xffffffffffffffff
	sw	$v0,24($fp)
	b	$L45
$L47:
	sw	$zero,24($fp)
$L45:
	lw	$v0,24($fp)
	move	$sp,$fp
	lw	$ra,40($sp)
	lw	$fp,36($sp)
	addu	$sp,$sp,48
	j	$ra
	.end	validateCommand
	.size	validateCommand, .-validateCommand
	.rdata
	.align	2
$LC12:
	.ascii	"\n"
	.ascii	"The tp0 utility is used to extract sections from each li"
	.ascii	"ne of input (usually from a file)\n\000"
	.align	2
$LC13:
	.ascii	"Usage:  tp0 [-h] [-V] [-f LIST] [-d CHARACTER] [-b LIST]"
	.ascii	" [-s] [files]\n\n\000"
	.align	2
$LC14:
	.ascii	"-V, --version \t\tPrint version and quit.\n\000"
	.align	2
$LC15:
	.ascii	"-h, --help \t\tPrint this information and quit.\n\000"
	.align	2
$LC16:
	.ascii	"-d, --delimiter \tUse as field delimiter instead of tab "
	.ascii	"character.\n\000"
	.align	2
$LC17:
	.ascii	"-b, --bytes \t\tSpecifies bytes positions to be extracte"
	.ascii	"d. \n"
	.ascii	" \000"
	.align	2
$LC18:
	.ascii	"\tLIST [n,] \tBytes position to be extracted, separated "
	.ascii	"by points\n\000"
	.align	2
$LC19:
	.ascii	"\tLIST [n-n] \tExtract bytes in this range\n\000"
	.align	2
$LC20:
	.ascii	"\tLIST [n-] \tExtract bytes from this position to the en"
	.ascii	"d\n\000"
	.align	2
$LC21:
	.ascii	"\tLIST [-n] \tExtract bytes from the beginning to this p"
	.ascii	"osition\n\000"
	.align	2
$LC22:
	.ascii	"-f, --field \t\tSpecifies fields positions to be extract"
	.ascii	"ed.\n\000"
	.align	2
$LC23:
	.ascii	"\tLIST [n,] \tFields to be extracted, separated by point"
	.ascii	"s\n\000"
	.align	2
$LC24:
	.ascii	"\tLIST [n-n] \tExtract fields in this range\n\000"
	.align	2
$LC25:
	.ascii	"\tLIST [n-] \tExtract from this field to the end\n\000"
	.align	2
$LC26:
	.ascii	"\tLIST [-n] \tExtract from the beginning to this field\n"
	.ascii	"\000"
	.align	2
$LC27:
	.ascii	"-s, --ignore \t\tIgnore lines not containing delimiters\n"
	.ascii	"\000"
	.align	2
$LC28:
	.ascii	"files \t\t\tFiles to be cutted\n\n\000"
	.align	2
$LC29:
	.ascii	"Examples: \n"
	.ascii	"\t tp0 -b -3 inputl.in \n"
	.ascii	"\t tp0 -f 1-5 -d . tes.txt\000"
	.text
	.align	2
	.globl	help
	.ent	help
help:
	.frame	$fp,40,$ra		# vars= 0, regs= 3/0, args= 16, extra= 8
	.mask	0xd0000000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$t9
	.set	reorder
	subu	$sp,$sp,40
	.cprestore 16
	sw	$ra,32($sp)
	sw	$fp,28($sp)
	sw	$gp,24($sp)
	move	$fp,$sp
	la	$a0,$LC12
	la	$t9,printf
	jal	$ra,$t9
	la	$a0,$LC13
	la	$t9,printf
	jal	$ra,$t9
	la	$a0,$LC14
	la	$t9,printf
	jal	$ra,$t9
	la	$a0,$LC15
	la	$t9,printf
	jal	$ra,$t9
	la	$a0,$LC16
	la	$t9,printf
	jal	$ra,$t9
	la	$a0,$LC17
	la	$t9,printf
	jal	$ra,$t9
	la	$a0,$LC18
	la	$t9,printf
	jal	$ra,$t9
	la	$a0,$LC19
	la	$t9,printf
	jal	$ra,$t9
	la	$a0,$LC20
	la	$t9,printf
	jal	$ra,$t9
	la	$a0,$LC21
	la	$t9,printf
	jal	$ra,$t9
	la	$a0,$LC22
	la	$t9,printf
	jal	$ra,$t9
	la	$a0,$LC23
	la	$t9,printf
	jal	$ra,$t9
	la	$a0,$LC24
	la	$t9,printf
	jal	$ra,$t9
	la	$a0,$LC25
	la	$t9,printf
	jal	$ra,$t9
	la	$a0,$LC26
	la	$t9,printf
	jal	$ra,$t9
	la	$a0,$LC27
	la	$t9,printf
	jal	$ra,$t9
	la	$a0,$LC28
	la	$t9,printf
	jal	$ra,$t9
	la	$a0,$LC29
	la	$t9,printf
	jal	$ra,$t9
	move	$sp,$fp
	lw	$ra,32($sp)
	lw	$fp,28($sp)
	addu	$sp,$sp,40
	j	$ra
	.end	help
	.size	help, .-help
	.rdata
	.align	2
$LC30:
	.ascii	"%s\000"
	.text
	.align	2
	.globl	getVersion
	.ent	getVersion
getVersion:
	.frame	$fp,40,$ra		# vars= 0, regs= 3/0, args= 16, extra= 8
	.mask	0xd0000000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$t9
	.set	reorder
	subu	$sp,$sp,40
	.cprestore 16
	sw	$ra,32($sp)
	sw	$fp,28($sp)
	sw	$gp,24($sp)
	move	$fp,$sp
	la	$a0,$LC30
	lw	$a1,version
	la	$t9,printf
	jal	$ra,$t9
	move	$sp,$fp
	lw	$ra,32($sp)
	lw	$fp,28($sp)
	addu	$sp,$sp,40
	j	$ra
	.end	getVersion
	.size	getVersion, .-getVersion
	.align	2
	.globl	getOptions
	.ent	getOptions
getOptions:
	.frame	$fp,72,$ra		# vars= 24, regs= 3/0, args= 24, extra= 8
	.mask	0xd0000000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$t9
	.set	reorder
	subu	$sp,$sp,72
	.cprestore 24
	sw	$ra,64($sp)
	sw	$fp,60($sp)
	sw	$gp,56($sp)
	move	$fp,$sp
	sw	$a0,72($fp)
	sw	$a1,76($fp)
	sw	$a2,80($fp)
	sw	$zero,32($fp)
	sw	$zero,opterr
$L51:
	addu	$v0,$fp,32
	sw	$v0,16($sp)
	lw	$a0,72($fp)
	lw	$a1,76($fp)
	lw	$a2,modifiers
	la	$a3,long_options
	la	$t9,getopt_long
	jal	$ra,$t9
	sw	$v0,36($fp)
	lw	$v1,36($fp)
	li	$v0,-1			# 0xffffffffffffffff
	bne	$v1,$v0,$L53
	b	$L52
$L53:
	lw	$v0,36($fp)
	addu	$v0,$v0,-86
	sw	$v0,52($fp)
	lw	$v1,52($fp)
	sltu	$v0,$v1,30
	beq	$v0,$zero,$L67
	lw	$v0,52($fp)
	sll	$v1,$v0,2
	la	$v0,$L68
	addu	$v0,$v1,$v0
	lw	$v0,0($v0)
	.cpadd	$v0
	j	$v0
	.rdata
	.align	2
$L68:
	.gpword	$L55
	.gpword	$L67
	.gpword	$L67
	.gpword	$L67
	.gpword	$L67
	.gpword	$L67
	.gpword	$L67
	.gpword	$L67
	.gpword	$L67
	.gpword	$L67
	.gpword	$L67
	.gpword	$L67
	.gpword	$L60
	.gpword	$L67
	.gpword	$L57
	.gpword	$L67
	.gpword	$L63
	.gpword	$L67
	.gpword	$L56
	.gpword	$L67
	.gpword	$L67
	.gpword	$L67
	.gpword	$L67
	.gpword	$L67
	.gpword	$L67
	.gpword	$L67
	.gpword	$L67
	.gpword	$L67
	.gpword	$L67
	.gpword	$L66
	.text
$L55:
	la	$t9,getVersion
	jal	$ra,$t9
	li	$v0,-1			# 0xffffffffffffffff
	sw	$v0,48($fp)
	b	$L50
$L56:
	la	$t9,help
	jal	$ra,$t9
	li	$v1,-1			# 0xffffffffffffffff
	sw	$v1,48($fp)
	b	$L50
$L57:
	li	$v0,1			# 0x1
	sw	$v0,oflags
	la	$v0,oflags+4
	sw	$v0,40($fp)
	lw	$v0,optarg
	beq	$v0,$zero,$L58
	lw	$a0,40($fp)
	lw	$a1,optarg
	li	$a2,10			# 0xa
	la	$t9,memcpy
	jal	$ra,$t9
	b	$L51
$L58:
	la	$t9,help
	jal	$ra,$t9
	li	$v0,-1			# 0xffffffffffffffff
	sw	$v0,48($fp)
	b	$L50
$L60:
	li	$v0,1			# 0x1
	sw	$v0,oflags+16
	la	$v0,oflags+20
	sw	$v0,40($fp)
	lw	$v0,optarg
	beq	$v0,$zero,$L61
	lw	$a0,40($fp)
	lw	$a1,optarg
	li	$a2,50			# 0x32
	la	$t9,memcpy
	jal	$ra,$t9
	b	$L51
$L61:
	la	$t9,help
	jal	$ra,$t9
	li	$v1,-1			# 0xffffffffffffffff
	sw	$v1,48($fp)
	b	$L50
$L63:
	li	$v0,1			# 0x1
	sw	$v0,oflags+72
	la	$v0,oflags+76
	sw	$v0,40($fp)
	lw	$v0,optarg
	beq	$v0,$zero,$L64
	lw	$a0,40($fp)
	lw	$a1,optarg
	li	$a2,50			# 0x32
	la	$t9,memcpy
	jal	$ra,$t9
	b	$L51
$L64:
	la	$t9,help
	jal	$ra,$t9
	li	$v0,-1			# 0xffffffffffffffff
	sw	$v0,48($fp)
	b	$L50
$L66:
	li	$v0,1			# 0x1
	sw	$v0,oflags+128
	b	$L51
$L67:
	la	$t9,help
	jal	$ra,$t9
	la	$t9,abort
	jal	$ra,$t9
$L52:
	lw	$v0,optind
	lw	$v1,72($fp)
	slt	$v0,$v0,$v1
	beq	$v0,$zero,$L69
	sw	$zero,44($fp)
$L70:
	lw	$v0,optind
	lw	$v1,72($fp)
	slt	$v0,$v0,$v1
	beq	$v0,$zero,$L71
	lw	$v0,44($fp)
	slt	$v0,$v0,10
	bne	$v0,$zero,$L72
	b	$L71
$L72:
	li	$v0,1			# 0x1
	sw	$v0,oflags+132
	lw	$v0,44($fp)
	sll	$v1,$v0,2
	la	$v0,posicionesArchivos
	addu	$a1,$v1,$v0
	la	$a0,optind
	lw	$v0,0($a0)
	move	$v1,$v0
	sw	$v1,0($a1)
	addu	$v0,$v0,1
	sw	$v0,0($a0)
	lw	$v0,44($fp)
	addu	$v0,$v0,1
	sw	$v0,44($fp)
	b	$L70
$L71:
	lw	$v0,44($fp)
	sw	$v0,numParameters
$L69:
	sw	$zero,48($fp)
$L50:
	lw	$v0,48($fp)
	move	$sp,$fp
	lw	$ra,64($sp)
	lw	$fp,60($sp)
	addu	$sp,$sp,72
	j	$ra
	.end	getOptions
	.size	getOptions, .-getOptions
	.rdata
	.align	2
$LC31:
	.ascii	"%s\n\000"
	.align	2
$LC32:
	.ascii	"%c\n\000"
	.text
	.align	2
	.globl	listBytes
	.ent	listBytes
listBytes:
	.frame	$fp,112,$ra		# vars= 72, regs= 4/0, args= 16, extra= 8
	.mask	0xd0010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$t9
	.set	reorder
	subu	$sp,$sp,112
	.cprestore 16
	sw	$ra,108($sp)
	sw	$fp,104($sp)
	sw	$gp,100($sp)
	sw	$s0,96($sp)
	move	$fp,$sp
	sw	$a0,112($fp)
	sw	$zero,24($fp)
	sw	$zero,28($fp)
	addu	$v0,$fp,40
	move	$a0,$v0
	move	$a1,$zero
	li	$a2,50			# 0x32
	la	$t9,memset
	jal	$ra,$t9
	lw	$v0,112($fp)
	sw	$v0,32($fp)
$L75:
	lw	$v0,24($fp)
	sll	$v1,$v0,2
	la	$v0,rango
	addu	$v0,$v1,$v0
	lw	$v1,0($v0)
	li	$v0,-5			# 0xfffffffffffffffb
	bne	$v1,$v0,$L77
	b	$L76
$L77:
	lw	$v0,24($fp)
	sll	$v1,$v0,2
	la	$v0,rango+4
	addu	$v0,$v1,$v0
	lw	$v1,0($v0)
	li	$v0,-1			# 0xffffffffffffffff
	bne	$v1,$v0,$L78
	lw	$v0,24($fp)
	sll	$v1,$v0,2
	la	$v0,rango+4
	addu	$v1,$v1,$v0
	li	$v0,-5			# 0xfffffffffffffffb
	sw	$v0,0($v1)
	lw	$v0,24($fp)
	sll	$v1,$v0,2
	la	$v0,rango
	addu	$s0,$v1,$v0
	lw	$a0,112($fp)
	la	$t9,strlen
	jal	$ra,$t9
	move	$v1,$v0
	lw	$v0,0($s0)
	sltu	$v0,$v0,$v1
	beq	$v0,$zero,$L83
$L80:
	lw	$v0,24($fp)
	sll	$v1,$v0,2
	la	$v0,rango
	addu	$v0,$v1,$v0
	lw	$v1,28($fp)
	lw	$v0,0($v0)
	slt	$v0,$v1,$v0
	bne	$v0,$zero,$L82
	b	$L81
$L82:
	lw	$v0,28($fp)
	addu	$v0,$v0,1
	sw	$v0,28($fp)
	lw	$v0,32($fp)
	addu	$v0,$v0,1
	sw	$v0,32($fp)
	b	$L80
$L81:
	lw	$v0,32($fp)
	addu	$v0,$v0,-1
	sw	$v0,32($fp)
	addu	$v0,$fp,40
	move	$a0,$v0
	lw	$a1,32($fp)
	la	$t9,strcpy
	jal	$ra,$t9
	addu	$v0,$fp,40
	la	$a0,$LC30
	move	$a1,$v0
	la	$t9,printf
	jal	$ra,$t9
	b	$L83
$L78:
	lw	$v0,24($fp)
	sll	$v1,$v0,2
	la	$v0,rango+4
	addu	$v0,$v1,$v0
	lw	$v1,0($v0)
	li	$v0,-2			# 0xfffffffffffffffe
	bne	$v1,$v0,$L84
	lw	$v0,24($fp)
	sll	$v1,$v0,2
	la	$v0,rango+4
	addu	$v1,$v1,$v0
	li	$v0,-5			# 0xfffffffffffffffb
	sw	$v0,0($v1)
$L85:
	lw	$v0,24($fp)
	sll	$v1,$v0,2
	la	$v0,rango
	addu	$v0,$v1,$v0
	lw	$v1,28($fp)
	lw	$v0,0($v0)
	slt	$v0,$v1,$v0
	bne	$v0,$zero,$L87
	b	$L86
$L87:
	lw	$v0,28($fp)
	addu	$v0,$v0,1
	sw	$v0,28($fp)
	lw	$v0,32($fp)
	addu	$v0,$v0,1
	sw	$v0,32($fp)
	b	$L85
$L86:
	lw	$v0,24($fp)
	sll	$v1,$v0,2
	la	$v0,rango
	addu	$s0,$v1,$v0
	lw	$a0,112($fp)
	la	$t9,strlen
	jal	$ra,$t9
	move	$v1,$v0
	lw	$v0,0($s0)
	sltu	$v0,$v0,$v1
	beq	$v0,$zero,$L88
	addu	$a0,$fp,40
	lw	$v1,32($fp)
	lw	$v0,112($fp)
	subu	$v0,$v1,$v0
	lw	$a1,112($fp)
	move	$a2,$v0
	la	$t9,strncpy
	jal	$ra,$t9
	addu	$v0,$fp,40
	la	$a0,$LC31
	move	$a1,$v0
	la	$t9,printf
	jal	$ra,$t9
	b	$L83
$L88:
	addu	$v0,$fp,40
	move	$a0,$v0
	lw	$a1,32($fp)
	la	$t9,strcpy
	jal	$ra,$t9
	la	$a0,$LC30
	lw	$a1,112($fp)
	la	$t9,printf
	jal	$ra,$t9
	b	$L83
$L84:
	lw	$v0,24($fp)
	sll	$v1,$v0,2
	la	$v0,rango
	addu	$s0,$v1,$v0
	lw	$a0,112($fp)
	la	$t9,strlen
	jal	$ra,$t9
	move	$v1,$v0
	lw	$v0,0($s0)
	sltu	$v0,$v0,$v1
	beq	$v0,$zero,$L83
$L92:
	lw	$v0,24($fp)
	sll	$v1,$v0,2
	la	$v0,rango
	addu	$v0,$v1,$v0
	lw	$v1,28($fp)
	lw	$v0,0($v0)
	slt	$v0,$v1,$v0
	bne	$v0,$zero,$L94
	b	$L93
$L94:
	lw	$v0,28($fp)
	addu	$v0,$v0,1
	sw	$v0,28($fp)
	lw	$v0,32($fp)
	addu	$v0,$v0,1
	sw	$v0,32($fp)
	b	$L92
$L93:
	lw	$v0,32($fp)
	addu	$v0,$v0,-1
	sw	$v0,32($fp)
	lw	$v0,32($fp)
	lb	$v0,0($v0)
	la	$a0,$LC32
	move	$a1,$v0
	la	$t9,printf
	jal	$ra,$t9
$L83:
	sw	$zero,28($fp)
	lw	$v0,112($fp)
	sw	$v0,32($fp)
	lw	$v0,24($fp)
	addu	$v0,$v0,1
	sw	$v0,24($fp)
	b	$L75
$L76:
	move	$v0,$zero
	move	$sp,$fp
	lw	$ra,108($sp)
	lw	$fp,104($sp)
	lw	$s0,96($sp)
	addu	$sp,$sp,112
	j	$ra
	.end	listBytes
	.size	listBytes, .-listBytes
	.align	2
	.globl	listFields
	.ent	listFields
listFields:
	.frame	$fp,152,$ra		# vars= 112, regs= 3/0, args= 16, extra= 8
	.mask	0xd0000000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$t9
	.set	reorder
	subu	$sp,$sp,152
	.cprestore 16
	sw	$ra,144($sp)
	sw	$fp,140($sp)
	sw	$gp,136($sp)
	move	$fp,$sp
	sw	$a0,152($fp)
	sw	$zero,24($fp)
	sw	$zero,28($fp)
	sw	$zero,32($fp)
	addu	$v0,$fp,48
	move	$a0,$v0
	move	$a1,$zero
	li	$a2,80			# 0x50
	la	$t9,memset
	jal	$ra,$t9
	lb	$v0,oflags+4
	lw	$a0,152($fp)
	move	$a1,$v0
	la	$t9,totalFields
	jal	$ra,$t9
	sw	$v0,36($fp)
	lw	$v1,36($fp)
	li	$v0,1			# 0x1
	bne	$v1,$v0,$L96
	lw	$v0,oflags+128
	beq	$v0,$zero,$L96
	sw	$zero,128($fp)
	b	$L95
$L96:
	.set	noreorder
	nop
	.set	reorder
$L97:
	lw	$v0,24($fp)
	sll	$v1,$v0,2
	la	$v0,rango
	addu	$v0,$v1,$v0
	lw	$v1,0($v0)
	li	$v0,-5			# 0xfffffffffffffffb
	bne	$v1,$v0,$L99
	b	$L98
$L99:
	lw	$v0,24($fp)
	sll	$v1,$v0,2
	la	$v0,rango+4
	addu	$v0,$v1,$v0
	lw	$v1,0($v0)
	li	$v0,-2			# 0xfffffffffffffffe
	bne	$v1,$v0,$L100
	lw	$v0,24($fp)
	sll	$v1,$v0,2
	la	$v0,rango
	addu	$v0,$v1,$v0
	lw	$v0,0($v0)
	sw	$v0,40($fp)
	lw	$v0,24($fp)
	sll	$v1,$v0,2
	la	$v0,rango+4
	addu	$v1,$v1,$v0
	li	$v0,-5			# 0xfffffffffffffffb
	sw	$v0,0($v1)
	li	$v0,1			# 0x1
	sw	$v0,28($fp)
	b	$L101
$L100:
	lw	$v0,24($fp)
	sll	$v1,$v0,2
	la	$v0,rango+4
	addu	$v0,$v1,$v0
	lw	$v1,0($v0)
	li	$v0,-1			# 0xffffffffffffffff
	bne	$v1,$v0,$L102
	lw	$v0,24($fp)
	sll	$v1,$v0,2
	la	$v0,rango+4
	addu	$v1,$v1,$v0
	li	$v0,-5			# 0xfffffffffffffffb
	sw	$v0,0($v1)
	lw	$v0,24($fp)
	sll	$v1,$v0,2
	la	$v0,rango
	addu	$v0,$v1,$v0
	lw	$v0,0($v0)
	sw	$v0,40($fp)
	li	$v0,1			# 0x1
	sw	$v0,32($fp)
	b	$L101
$L102:
	lw	$v0,24($fp)
	sll	$v1,$v0,2
	la	$v0,rango
	addu	$v0,$v1,$v0
	lb	$v1,oflags+4
	addu	$a3,$fp,48
	lw	$a0,152($fp)
	lw	$a1,0($v0)
	move	$a2,$v1
	la	$t9,getField
	jal	$ra,$t9
$L101:
	lw	$v0,24($fp)
	addu	$v0,$v0,1
	sw	$v0,24($fp)
	b	$L97
$L98:
	lw	$v0,28($fp)
	beq	$v0,$zero,$L104
	li	$v0,1			# 0x1
	sw	$v0,24($fp)
$L105:
	lw	$v0,24($fp)
	lw	$v1,40($fp)
	slt	$v0,$v1,$v0
	beq	$v0,$zero,$L108
	b	$L104
$L108:
	addu	$v0,$fp,48
	move	$a0,$v0
	move	$a1,$zero
	li	$a2,80			# 0x50
	la	$t9,memset
	jal	$ra,$t9
	lb	$v0,oflags+4
	addu	$v1,$fp,48
	lw	$a0,152($fp)
	lw	$a1,24($fp)
	move	$a2,$v0
	move	$a3,$v1
	la	$t9,getField
	jal	$ra,$t9
	lw	$v0,24($fp)
	addu	$v0,$v0,1
	sw	$v0,24($fp)
	b	$L105
$L104:
	lw	$v0,32($fp)
	beq	$v0,$zero,$L109
	lw	$v0,40($fp)
	sw	$v0,24($fp)
$L110:
	lw	$v0,24($fp)
	lw	$v1,36($fp)
	slt	$v0,$v1,$v0
	beq	$v0,$zero,$L113
	b	$L109
$L113:
	addu	$v0,$fp,48
	move	$a0,$v0
	move	$a1,$zero
	li	$a2,80			# 0x50
	la	$t9,memset
	jal	$ra,$t9
	lb	$v0,oflags+4
	addu	$v1,$fp,48
	lw	$a0,152($fp)
	lw	$a1,24($fp)
	move	$a2,$v0
	move	$a3,$v1
	la	$t9,getField
	jal	$ra,$t9
	lw	$v0,24($fp)
	addu	$v0,$v0,1
	sw	$v0,24($fp)
	b	$L110
$L109:
	sw	$zero,128($fp)
$L95:
	lw	$v0,128($fp)
	move	$sp,$fp
	lw	$ra,144($sp)
	lw	$fp,140($sp)
	addu	$sp,$sp,152
	j	$ra
	.end	listFields
	.size	listFields, .-listFields
	.align	2
	.globl	totalFields
	.ent	totalFields
totalFields:
	.frame	$fp,56,$ra		# vars= 16, regs= 3/0, args= 16, extra= 8
	.mask	0xd0000000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$t9
	.set	reorder
	subu	$sp,$sp,56
	.cprestore 16
	sw	$ra,48($sp)
	sw	$fp,44($sp)
	sw	$gp,40($sp)
	move	$fp,$sp
	sw	$a0,56($fp)
	move	$v0,$a1
	sb	$v0,24($fp)
	sw	$zero,32($fp)
	lw	$v0,56($fp)
	sw	$v0,28($fp)
$L115:
	lw	$v0,28($fp)
	bne	$v0,$zero,$L117
	b	$L116
$L117:
	lw	$v0,28($fp)
	addu	$v0,$v0,1
	sw	$v0,28($fp)
	lb	$v1,24($fp)
	move	$a0,$v0
	move	$a1,$v1
	la	$t9,strchr
	jal	$ra,$t9
	sw	$v0,28($fp)
	lw	$v0,28($fp)
	beq	$v0,$zero,$L115
	lw	$v0,32($fp)
	addu	$v0,$v0,1
	sw	$v0,32($fp)
	b	$L115
$L116:
	lw	$v0,32($fp)
	addu	$v0,$v0,1
	sw	$v0,32($fp)
	lw	$v0,32($fp)
	move	$sp,$fp
	lw	$ra,48($sp)
	lw	$fp,44($sp)
	addu	$sp,$sp,56
	j	$ra
	.end	totalFields
	.size	totalFields, .-totalFields
	.rdata
	.align	2
$LC33:
	.ascii	"%c\000"
	.text
	.align	2
	.globl	getField
	.ent	getField
getField:
	.frame	$fp,64,$ra		# vars= 24, regs= 3/0, args= 16, extra= 8
	.mask	0xd0000000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$t9
	.set	reorder
	subu	$sp,$sp,64
	.cprestore 16
	sw	$ra,56($sp)
	sw	$fp,52($sp)
	sw	$gp,48($sp)
	move	$fp,$sp
	sw	$a0,64($fp)
	sw	$a1,68($fp)
	move	$v0,$a2
	sw	$a3,76($fp)
	sb	$v0,24($fp)
	lbu	$v0,24($fp)
	sb	$v0,25($fp)
	sw	$zero,28($fp)
	lw	$v0,64($fp)
	sw	$v0,44($fp)
	sw	$v0,40($fp)
	lb	$v0,24($fp)
	lw	$a0,64($fp)
	move	$a1,$v0
	la	$t9,totalFields
	jal	$ra,$t9
	sw	$v0,28($fp)
	lw	$v1,28($fp)
	li	$v0,1			# 0x1
	bne	$v1,$v0,$L120
	lw	$a0,76($fp)
	lw	$a1,40($fp)
	la	$t9,strcpy
	jal	$ra,$t9
	b	$L121
$L120:
	lw	$v0,68($fp)
	lw	$v1,28($fp)
	slt	$v0,$v1,$v0
	beq	$v0,$zero,$L122
	lw	$a0,76($fp)
	move	$a1,$zero
	li	$a2,10			# 0xa
	la	$t9,memset
	jal	$ra,$t9
	b	$L121
$L122:
	sw	$zero,32($fp)
$L124:
	lw	$v0,32($fp)
	lw	$v1,68($fp)
	slt	$v0,$v0,$v1
	bne	$v0,$zero,$L127
	b	$L125
$L127:
	lw	$v0,44($fp)
	sw	$v0,40($fp)
	lb	$v0,25($fp)
	lw	$a0,44($fp)
	move	$a1,$v0
	la	$t9,strchr
	jal	$ra,$t9
	sw	$v0,44($fp)
	lw	$v0,44($fp)
	beq	$v0,$zero,$L126
	lw	$v0,44($fp)
	addu	$v0,$v0,1
	sw	$v0,44($fp)
$L126:
	lw	$v0,32($fp)
	addu	$v0,$v0,1
	sw	$v0,32($fp)
	b	$L124
$L125:
	lw	$v1,68($fp)
	lw	$v0,28($fp)
	bne	$v1,$v0,$L129
	lw	$a0,76($fp)
	lw	$a1,40($fp)
	la	$t9,strcpy
	jal	$ra,$t9
	b	$L121
$L129:
	lw	$v0,44($fp)
	addu	$v0,$v0,-1
	sw	$v0,44($fp)
	lw	$v1,44($fp)
	lw	$v0,40($fp)
	subu	$v0,$v1,$v0
	sw	$v0,36($fp)
	lw	$a0,76($fp)
	lw	$a1,40($fp)
	lw	$a2,36($fp)
	la	$t9,strncpy
	jal	$ra,$t9
$L121:
	la	$a0,$LC30
	lw	$a1,76($fp)
	la	$t9,printf
	jal	$ra,$t9
	lw	$v0,68($fp)
	lw	$v1,28($fp)
	slt	$v0,$v0,$v1
	beq	$v0,$zero,$L119
	lb	$v0,24($fp)
	la	$a0,$LC33
	move	$a1,$v0
	la	$t9,printf
	jal	$ra,$t9
$L119:
	move	$sp,$fp
	lw	$ra,56($sp)
	lw	$fp,52($sp)
	addu	$sp,$sp,64
	j	$ra
	.end	getField
	.size	getField, .-getField
	.align	2
	.globl	numDigitos
	.ent	numDigitos
numDigitos:
	.frame	$fp,24,$ra		# vars= 8, regs= 2/0, args= 0, extra= 8
	.mask	0x50000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$t9
	.set	reorder
	subu	$sp,$sp,24
	.cprestore 0
	sw	$fp,20($sp)
	sw	$gp,16($sp)
	move	$fp,$sp
	sw	$a0,24($fp)
	sw	$zero,8($fp)
$L133:
	lw	$v0,24($fp)
	bne	$v0,$zero,$L135
	b	$L134
$L135:
	lw	$v0,8($fp)
	addu	$v0,$v0,1
	sw	$v0,8($fp)
	lw	$a0,24($fp)
	li	$v0,1717960704			# 0x66660000
	ori	$v0,$v0,0x6667
	mult	$a0,$v0
	mfhi	$v0
	sra	$v1,$v0,2
	sra	$v0,$a0,31
	subu	$v0,$v1,$v0
	sw	$v0,24($fp)
	b	$L133
$L134:
	lw	$v0,8($fp)
	move	$sp,$fp
	lw	$fp,20($sp)
	addu	$sp,$sp,24
	j	$ra
	.end	numDigitos
	.size	numDigitos, .-numDigitos
	.rdata
	.align	2
$LC34:
	.ascii	"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.:;!"
	.ascii	"\357\277\275\357\277\275?_+*[]{}\357\277\275\357\277\275"
	.ascii	"\357\277\275\357\277\275#$%&^/=`~\000"
	.align	2
$LC35:
	.ascii	"tiene caracteres incorrectos \n\000"
	.text
	.align	2
	.globl	validateRange
	.ent	validateRange
validateRange:
	.frame	$fp,72,$ra		# vars= 32, regs= 4/0, args= 16, extra= 8
	.mask	0xd0010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$t9
	.set	reorder
	subu	$sp,$sp,72
	.cprestore 16
	sw	$ra,68($sp)
	sw	$fp,64($sp)
	sw	$gp,60($sp)
	sw	$s0,56($sp)
	move	$fp,$sp
	sw	$a0,72($fp)
	sw	$zero,28($fp)
	lw	$a0,72($fp)
	la	$a1,$LC34
	la	$t9,strpbrk
	jal	$ra,$t9
	beq	$v0,$zero,$L137
	la	$a0,$LC35
	la	$t9,printf
	jal	$ra,$t9
	sw	$zero,52($fp)
	b	$L136
$L137:
	lw	$v0,72($fp)
	sw	$v0,24($fp)
$L139:
	lw	$v0,24($fp)
	lb	$v0,0($v0)
	bne	$v0,$zero,$L141
	b	$L140
$L141:
	lw	$v0,28($fp)
	bne	$v0,$zero,$L142
	lw	$v0,24($fp)
	lb	$v1,0($v0)
	li	$v0,45			# 0x2d
	bne	$v1,$v0,$L143
	lw	$v0,28($fp)
	sll	$v1,$v0,2
	la	$v0,rango+4
	addu	$v1,$v1,$v0
	li	$v0,-2			# 0xfffffffffffffffe
	sw	$v0,0($v1)
	lw	$v0,24($fp)
	addu	$v0,$v0,1
	sw	$v0,24($fp)
	lw	$v0,28($fp)
	sll	$v1,$v0,2
	la	$v0,rango
	addu	$s0,$v1,$v0
	lw	$a0,24($fp)
	la	$t9,atoi
	jal	$ra,$t9
	sw	$v0,0($s0)
	lw	$v0,28($fp)
	sll	$v1,$v0,2
	la	$v0,rango
	addu	$v0,$v1,$v0
	lw	$a0,0($v0)
	la	$t9,numDigitos
	jal	$ra,$t9
	sw	$v0,48($fp)
$L144:
	lw	$v0,48($fp)
	bne	$v0,$zero,$L146
	b	$L145
$L146:
	lw	$v0,24($fp)
	addu	$v0,$v0,1
	sw	$v0,24($fp)
	lw	$v0,48($fp)
	addu	$v0,$v0,-1
	sw	$v0,48($fp)
	b	$L144
$L145:
	lw	$v0,28($fp)
	addu	$v0,$v0,2
	sw	$v0,28($fp)
	b	$L139
$L143:
	lw	$v0,24($fp)
	lb	$v1,0($v0)
	li	$v0,44			# 0x2c
	bne	$v1,$v0,$L148
	sw	$zero,52($fp)
	b	$L136
$L148:
	lw	$v0,28($fp)
	sll	$v1,$v0,2
	la	$v0,rango
	addu	$s0,$v1,$v0
	lw	$a0,24($fp)
	la	$t9,atoi
	jal	$ra,$t9
	sw	$v0,0($s0)
	lw	$v0,28($fp)
	sll	$v1,$v0,2
	la	$v0,rango
	addu	$v0,$v1,$v0
	lw	$a0,0($v0)
	la	$t9,numDigitos
	jal	$ra,$t9
	sw	$v0,48($fp)
$L150:
	lw	$v0,48($fp)
	bne	$v0,$zero,$L152
	b	$L151
$L152:
	lw	$v0,24($fp)
	addu	$v0,$v0,1
	sw	$v0,24($fp)
	lw	$v0,48($fp)
	addu	$v0,$v0,-1
	sw	$v0,48($fp)
	b	$L150
$L151:
	lw	$v0,28($fp)
	addu	$v0,$v0,1
	sw	$v0,28($fp)
	b	$L139
$L142:
	lw	$v0,24($fp)
	lb	$v1,0($v0)
	li	$v0,45			# 0x2d
	bne	$v1,$v0,$L154
	lw	$v0,24($fp)
	addu	$v0,$v0,1
	sw	$v0,24($fp)
	lw	$v0,24($fp)
	lb	$v0,0($v0)
	bne	$v0,$zero,$L155
	lw	$v0,28($fp)
	sll	$v1,$v0,2
	la	$v0,rango
	addu	$v1,$v1,$v0
	li	$v0,-1			# 0xffffffffffffffff
	sw	$v0,0($v1)
	lw	$v0,28($fp)
	addu	$v0,$v0,1
	sw	$v0,28($fp)
	b	$L139
$L155:
	lw	$v0,24($fp)
	lb	$v1,0($v0)
	li	$v0,44			# 0x2c
	bne	$v1,$v0,$L157
	sw	$zero,52($fp)
	b	$L136
$L157:
	lw	$v0,28($fp)
	sll	$v1,$v0,2
	la	$v0,rango-4
	addu	$v0,$v1,$v0
	lw	$v0,0($v0)
	sw	$v0,32($fp)
	lw	$a0,24($fp)
	la	$t9,atoi
	jal	$ra,$t9
	sw	$v0,36($fp)
	lw	$v1,36($fp)
	lw	$v0,32($fp)
	slt	$v0,$v0,$v1
	bne	$v0,$zero,$L159
	sw	$zero,52($fp)
	b	$L136
$L159:
	lw	$v0,28($fp)
	sw	$v0,40($fp)
	lw	$v1,36($fp)
	lw	$v0,32($fp)
	subu	$v0,$v1,$v0
	sw	$v0,44($fp)
$L161:
	lw	$v1,40($fp)
	lw	$v0,44($fp)
	addu	$v1,$v1,$v0
	lw	$v0,28($fp)
	slt	$v0,$v0,$v1
	bne	$v0,$zero,$L163
	b	$L162
$L163:
	lw	$v0,32($fp)
	addu	$v0,$v0,1
	sw	$v0,32($fp)
	lw	$v0,28($fp)
	sll	$v1,$v0,2
	la	$v0,rango
	addu	$v1,$v1,$v0
	lw	$v0,32($fp)
	sw	$v0,0($v1)
	lw	$v0,28($fp)
	addu	$v0,$v0,1
	sw	$v0,28($fp)
	b	$L161
$L162:
	lw	$a0,32($fp)
	la	$t9,numDigitos
	jal	$ra,$t9
	sw	$v0,48($fp)
$L164:
	lw	$v0,48($fp)
	bne	$v0,$zero,$L166
	b	$L139
$L166:
	lw	$v0,24($fp)
	addu	$v0,$v0,1
	sw	$v0,24($fp)
	lw	$v0,48($fp)
	addu	$v0,$v0,-1
	sw	$v0,48($fp)
	b	$L164
$L154:
	lw	$v0,24($fp)
	lb	$v1,0($v0)
	li	$v0,44			# 0x2c
	bne	$v1,$v0,$L168
	lw	$v0,24($fp)
	addu	$v0,$v0,1
	sw	$v0,24($fp)
	lw	$v0,24($fp)
	lb	$v1,0($v0)
	li	$v0,44			# 0x2c
	beq	$v1,$v0,$L170
	lw	$v0,24($fp)
	lb	$v1,0($v0)
	li	$v0,32			# 0x20
	beq	$v1,$v0,$L170
	lw	$v0,24($fp)
	lb	$v1,0($v0)
	li	$v0,45			# 0x2d
	beq	$v1,$v0,$L170
	b	$L169
$L170:
	sw	$zero,52($fp)
	b	$L136
$L169:
	lw	$v0,28($fp)
	sll	$v1,$v0,2
	la	$v0,rango
	addu	$s0,$v1,$v0
	lw	$a0,24($fp)
	la	$t9,atoi
	jal	$ra,$t9
	sw	$v0,0($s0)
	lw	$v0,28($fp)
	sll	$v1,$v0,2
	la	$v0,rango
	addu	$v0,$v1,$v0
	lw	$a0,0($v0)
	la	$t9,numDigitos
	jal	$ra,$t9
	sw	$v0,48($fp)
$L172:
	lw	$v0,48($fp)
	bne	$v0,$zero,$L174
	b	$L173
$L174:
	lw	$v0,24($fp)
	addu	$v0,$v0,1
	sw	$v0,24($fp)
	lw	$v0,48($fp)
	addu	$v0,$v0,-1
	sw	$v0,48($fp)
	b	$L172
$L173:
	lw	$v0,28($fp)
	addu	$v0,$v0,1
	sw	$v0,28($fp)
	b	$L139
$L168:
	lw	$v0,28($fp)
	sll	$v1,$v0,2
	la	$v0,rango
	addu	$s0,$v1,$v0
	lw	$a0,24($fp)
	la	$t9,atoi
	jal	$ra,$t9
	sw	$v0,0($s0)
	lw	$v0,28($fp)
	sll	$v1,$v0,2
	la	$v0,rango
	addu	$v0,$v1,$v0
	lw	$a0,0($v0)
	la	$t9,numDigitos
	jal	$ra,$t9
	sw	$v0,48($fp)
$L176:
	lw	$v0,48($fp)
	bne	$v0,$zero,$L178
	b	$L177
$L178:
	lw	$v0,24($fp)
	addu	$v0,$v0,1
	sw	$v0,24($fp)
	lw	$v0,48($fp)
	addu	$v0,$v0,-1
	sw	$v0,48($fp)
	b	$L176
$L177:
	lw	$v0,28($fp)
	addu	$v0,$v0,1
	sw	$v0,28($fp)
	b	$L139
$L140:
	la	$v0,rango
	sw	$v0,52($fp)
$L136:
	lw	$v0,52($fp)
	move	$sp,$fp
	lw	$ra,68($sp)
	lw	$fp,64($sp)
	lw	$s0,56($sp)
	addu	$sp,$sp,72
	j	$ra
	.end	validateRange
	.size	validateRange, .-validateRange

	.comm	oflags,136
	.ident	"GCC: (GNU) 3.3.3 (NetBSD nb3 20040520)"

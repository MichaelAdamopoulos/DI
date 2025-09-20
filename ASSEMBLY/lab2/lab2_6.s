#################################################
# 						#
# 		lab2_6.s			#
# 						#
#################################################
#################################################
# 						#
# 		text segment 			#
# 						#
#################################################
 .text
 .globl __start
__start:

 lw $t1, A1
 lw $t2, A2
 lw $t3, B1
 lw $t4, B2

 # from lab2_5.s
 
 addu $t5, $t1, $t3	# t5 has the lower sum
 nor $s0, $t5, $zero
 srl $s0, $s0, 31
 srl $s1, $t1, 31
 srl $s2, $t3, 31
 and $s3, $s0, $s1
 and $s4, $s0, $s2
 and $s5, $s1, $s2
 or $s6, $s3, $s4	
 or $s7, $s6, $s5	# s7 has the extra bit

 addu $t6, $t2, $t4	# t6 has the higher sum

 addu $t6, $t6, $s7

 la $k0, B2

 sw $t5, 4($k0)
 sw $t6, 8($k0)

 li $v0,10
 syscall 		# au revoir...
#################################################
# 						#
# 		data segment 			#
# 						#
#################################################
.data
A1: .word 0xffffffff
A2: .word 0x00000001
B1: .word 0x00000001
B2: .word 0x00000000

endl: .asciiz "\n"
#################################################
# 						#
# 		End of File	 		#
# 						#
#################################################
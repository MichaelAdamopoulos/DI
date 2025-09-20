#################################################
# 						#
# 		lab1_6.s			#
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

 li $v0, 5
 syscall
 move $a0, $v0
 li $v0, 1
 syscall
 move $a1, $a0

 li $v0, 4
 la $a0, endl
 syscall	

 li $v0, 5
 syscall
 move $a0, $v0
 li $v0, 1
 syscall
 move $a2, $a0

 li $v0, 4
 la $a0, endl
 syscall

 add $a0, $a1, $a2

 li $v0, 1
 syscall

 li $v0, 4
 la $a0, endl
 syscall

 sub $a0, $a1, $a2

 li $v0, 1
 syscall 

 li $v0,10
 syscall 		# au revoir...
#################################################
# 						#
# 		data segment 			#
# 						#
#################################################
.data
endl: .asciiz "\n"
#################################################
# 						#
# 		End of File	 		#
# 						#
#################################################
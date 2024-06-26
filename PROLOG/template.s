#################################################
#												#
#				text segment					#
#												#
#################################################

	.text
	.globl __start	
												#read first int and move it to a temp reg
__start:



Exit:				li 		$v0, 10
					syscall				#au revoir...

#################################################
#			 									#
#     	 	data segment						#
#												#
#################################################

	.data
endl: 					.asciiz 	"\n"


#################################################
#			 									#
#     	 	Useful code						#
#												#
#################################################

#print_endl:		la		$a0,endl 			# system call to print
#					li		$v0, 4 				# out a newline
#					syscall
#					jr $ra

#read_str:			li $v0, 8					# code to read a string
#					la $a0, ???					# ??? --> label with string
#					li $a1, ?n?					# n chars --> $a1=n+1 eg: (20+1)--> li $a1, 21
#					syscall
#					jr $ra

#print_str:			li $v0, 4
#					la $a0, ???					# ??? --> label with string
#					syscall
#					jr $ra

#read_int:			li		$v0, 5				# $v0 <--- integer
#					syscall
#					jr $ra

#print_int_from_reg:	move	$a0, ???			# ???  --> register with integer
#					li $v0, 1
#					syscall
#					jr $ra

#print_immidiate:	li $v0, 1
#					li $a0, ???					# ???  --> immediate
#					syscall
#					jr $ra

#leaf_proc_not_using_stack: ........... 	
#							...........
#							jr $ra
					
leaf_proc_using_stack:  #.....              // NOT $ra
			     		#addi $sp, $sp, -16 # 4 words or 4 registers (xx, xy, yy & yz) --> 4*n=4*4=16
						#...........
						#sw $xx, 0 ($sp)
						#...........
						#sw $xy, 4 ($sp)
						#...........
						#sw $yy, 8 ($sp)
						#...........
						#sw $yz, 12 ($sp)
						
						#...........
						#...........
						
						#lw $xx, 0 ($sp)
						#...........
						#lw $xy, 4 ($sp)
						#...........
						#lw $yy, 8 ($sp)
						#...........
						#lw $yz, 12 ($sp)
						#...........
						addi $sp, $sp, 16
						#...........
						jr $ra
						
node_proc_using_stack:  #...........
			     		#addi $sp, $sp, -16 # 3 words or 3 registers (xx, xy, zz & ra) --> 4*n=4*4=16
						#...........
						#sw $ra, 12 ($sp)
						#...........
						#sw $xx, 8 ($sp)
						#...........
						#sw $yy, 4 ($sp)
						#...........
						#sw $zz, 0 ($sp)
						
						#...........
						#...........
						
						#jal any_procedure # leaf_proc_non_using_stack or leaf_proc_using_stack or node_proc_using_stack
						
						#...........
						#...........
						
						#lw $zz, 0 ($sp)
						#...........
						#lw $yy, 4 ($sp)
						#...........
						#lw $xx, 8 ($sp)
						#...........
						#lw $ra, 12 ($sp)
						#...........
						#addi $sp, $sp, 16
						#...........
						#jr $ra
						
switch_case_no_break:   #...........
						#move $XY, $zero     	# initialize flag register $XY
		case01:			#bXX $YY,$ZZ, case02 	# this condition/case is not valid, check next case 	
		if_case01:		#...........
						#addi $XY, $XY, 1
						
		case02:			#bXX $YY,$ZZ, case?? 	# this condition/case is not valid, check next case 	
		if_case02:		#...........
						#addi $XY, $XY, 1						

						#...........
						
		case0n:			#bXX $YY,$ZZ, case03 	# this condition/case is not valid, check next case 	
		if_case0n:		#...........
						#addi $XY, $XY, 1
						
		else_case:		#bne $XY,$zero, Exit	# non of previous conditions/cases exit, exit 	
		if_non_case:	#...........
						
switch_case_with_break: #...........
		case001:		#bXX $YY,$ZZ, case02 	# this condition/case is not valid, check next case 	
		if_case001:		#...........
						#j Exit_switch_case
						
		case002:		#bXX $YY,$ZZ, case?? 	# this condition/case is not valid, check next case 	
		if_case002:		#...........
						#j Exit_switch_case						

						#...........
						
		case00n:		#bXX $YY,$ZZ, else_case 	# this condition/case is not valid, check next case 	
		if_case00n:		#...........
						#j Exit_switch_case
						
		else_case_:		#...........	 		# non of previous conditions/cases exit 	
		if_non_case_:	#...........
		
while_do_1_condition:   #...........
						#bXX $YY,$ZZ, exit_while

						#...........
						#addi #counter, #counter, 1  #possible approach
						
						j while_do_1_condition
		
while_do_a_AND_b:   	#...........				# when !a OR !b, exit while
						#bXX $RR,$ZZ, exit_while    # if a is not valid exit while
						#bYY $WW,$TT, exit_while    # if b is not valid exit while

						#...........
						#addi #counter, #counter, 1  #possible approach
						
						j while_do_a_AND_b
		
while_do_a_OR_b_1:   	#...........				# when !a AND !b, exit while
						#bXX $RR,$ZZ, exit_while    # if !a is not valid exit while
						#bYY $WW,$TT, exit_while    # if !b is not valid exit while

						#...........
						#addi #counter, #counter, 1  #possible approach
						
						j while_do_a_AND_b
		
while_do_a_OR_b_2:   	#...........				# when !a AND !b exit wile
			check_a:	#bXX $RR,$ZZ, check_b    	# if a is not valid check b
						
			do:			#...........
						#addi #counter, #counter, 1  #possible approach
						#j while_do_a_OR_b_2
			
			check_b:	#bYY $WW,$TT, exit_while    # if b is not valid exit while
						
						j do























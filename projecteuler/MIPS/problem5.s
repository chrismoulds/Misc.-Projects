#------------------------------------------------------------------------------
# Project Euler Problem #5:
# 2520 is the smallest number that can be divided by each of the numbers 
# from 1 to 10 without any remainder.
#
# What is the smallest positive number that is evenly divisible by all of 
# the numbers from 1 to 20?
# 
# Author: Chris Moulds
#------------------------------------------------------------------------------

.data

list: .word 0

.text

main:

	li $a0 20
	jal Sieve


Sieve:
	addi $sp $sp -4
	sw $ra 4($sp)

	li $t1 2 				# counter variable

	li $v0 9				#sbrk memory for array
	syscall

	sw $v0 list 			# memory allocated

Outer:


Inner:	




	lw $ra 4($sp)	
	addi $sp $sp 4
	jr $ra



finish:							# print the final value
	li $v0 1
	syscall

	jr $ra					# return to calling program





#------------------------------------------------------------------------------
# Project Euler Problem #1:
# If we list all the natural numbers below 10 that are multiples of 3 or 5, 
# we get 3, 5, 6 and 9. The sum of these multiples is 23. Find the sum of all 
# the multiples of 3 or 5 below 1000.
# 
# Author: Chris Moulds
#------------------------------------------------------------------------------
.data
.text

main:

li $a0 0	# register to hold the sum variable
li $t1 3	# counter that will start at 3 and end at 999
li $t2 1000	# value the counter can compare with for loop breaking.
li $t3 3	# for the modulo
li $t4 5	# for the modulo

loop:							# Check if the value is divisible by 5 or 3
		div $t1 $t3				# If so, that value will be added to the
		mfhi $t5				# sum variable.
		beq $t5 $0 addvalue

		div $t1 $t4
		mfhi $t5
		bgtz $t5 inc 			

addvalue:						# value is ok ... add it to sum
		add $a0 $a0 $t1
	
inc:							# increment the counter and check for loop break
		addi $t1 $t1 1
		beq $t1 $t2 finish
		j loop

finish:							# print the final value
		li $v0 1
		syscall

		jr $ra					# return to calling program

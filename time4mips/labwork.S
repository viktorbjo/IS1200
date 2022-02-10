  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.
.global hexasc
.global delay
.global time2string
  #
  # Please keep the two macros PUSH and POP unchanged
  #
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  #
  .data
  .text
  
  hexasc:
	andi $t0, $a0, 0xf			# För att spara de 4 LSB genom att "maska" de med en andi 
	
	ble $t0, 0x9, nummer			# Vi kollar om vårat värde är mindre eller lika med 9, om så är fallet så kör vi nummer
	nop
	
	ble $t0, 0xf, bokstav			# Samma sak som ovan fast om det är mindre eller lika med 15, kör bokstav
	nop
	
	nummer: 
		addi $v0, $t0, 0x30		# Eftersom siffran 0 i ASCII börjar på 0x30, adderar vi vårt värde på det. 
		jr $ra 
		nop
	
	bokstav:
	addi $v0, $t0, 0x37			# Eftersom det är 7 steg emellan 9 och A så hoppar vi 7 steg. 
	jr $ra 
	nop

delay: 
	PUSH	$ra
	move 	$t1, $a0			# Store argument in temp so we can use it
	
	while:
		ble	$t1, $zero, exit_delay	# Check if ms > 0
		nop
		sub	$t1, $t1, 1 		# ms--;
		
	li	$t2, 0				# int i	= 0		
	for:
		bge	$t2, 4711, while		# Check if i < parameter (Can be changed for speed), then jump or continue
		nop
		addi	$t2, $t2, 1		# i++;
		j	for			# Go to next iteration of for loop
		nop
			
	exit_delay:				# End of subroutine
		POP	$ra			# Restore the return adress
		jr	$ra			# Jump back to caller
		nop

time2string:
	PUSH	$s0
	PUSH	$s1				# Save contents of s1 to restore it after the function ends
	PUSH	$ra				# Save the return adress on the stack
	move	$s1, $a1			# Move contents of $a0 to $s1 so we can work with it
	move	$s0,$a0

	# First digit
	andi 	$t1, $s1, 0xf000		# Sparar bittarna mellan index 15 till 12 genom maskining andi med ettor där vi ska maska
	srl 	$a0, $t1, 12			# shiftar bitsen to minsta positionen och lägger de i a0 
	jal	hexasc				# kallar på funktionen hexasc som kommer göra om värdet till hexa
	nop
	sb 	$v0, 0($s0)		 	# Sparar värdet som returneras från hexasc i första "byte location i s1				

	# Second digit
	andi 	$t1, $s1, 0x0f00		# Sparar bittarna mellan index 11 till 8 genom maskining andi med ettor där vi ska maska
	srl 	$a0, $t1, 8			# shiftar bitsen to minsta positionen och lägger de i a0 
	jal	hexasc				# kallar på funktionen hexasc som kommer göra om värdet till hexa
	nop
	sb 	$v0, 1($s0)		 	# Sparar värdet som returneras från hexasc i andra "byte location i s1	
											

	# Adding the colon
	li 	$t1, 0x3a			# hämtar ASCII värdet för kolon tecknet
	sb 	$t1, 2($s0)		 	# Sparar värdet i tredje byte location 
					
	
	# Third digit
	andi 	$t1, $s1, 0x00f0		#Sparar bittarna mellan index 7 till 4 genom maskining andi med ettor där vi ska maska
	srl 	$a0, $t1, 4			# shiftar bitsen to minsta positionen och lägger de i a0 
	jal	hexasc				# kallar på funktionen hexasc som kommer göra om värdet till hexa
	nop
	sb 	$v0, 3($s0)		 	# Sparar värdet som returneras från hexasc i fjärde "byte location i s1	
						
										
	# Forth digit
	andi 	$t1, $s1, 0x000f		# Sparar bittarna mellan index 3 till 0 genom maskining andi med ettor där vi ska maska
	move 	$a0, $t1			# flyttar direkt toll a0 eftersom de redan ligger på rätt plats.
	jal	hexasc				# kallar på funktionen hexasc som kommer göra om värdet till hexa
	nop
	sb 	$v0, 4($s0)		 	# Sparar värdet som returneras från hexasc i femte "byte location i s1	
						
						


	# Adding the NUL byte
	li	$t1, 0x00			# Loading the ASCII code for NUL
	sb 	$t1, 5($s0)		 	# Save the return value from hexasc in the sixth byte location $s1 
	j	exit_time2string		# points to

	# End of subroutine. Restoring registers and jumping back to caller.
	exit_time2string:																																																																																										
		POP	$ra
		POP	$s1
		POP	$s0	
 		jr 	$ra
 		nop	
 		
 

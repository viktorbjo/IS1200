  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

	.data
	.align 2
mytime:	.word 0x5957
timstr:	.ascii "text more text lots of text\0"
	.text
main:
	# print timstr
	la	$a0,timstr
	li	$v0,4
	syscall
	nop
	# wait a little
	li	$a0,2
	jal	delay
	nop
	# call tick
	la	$a0,mytime
	jal	tick
	nop
	# call your function time2string
	la	$a0,timstr
	la	$t0,mytime
	lw	$a1,0($t0)
	jal	time2string
	nop
	# print a newline
	li	$a0,10
	li	$v0,11
	syscall
	nop
	# go back and do it all again
	j	main
	nop
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)	# get time
	addiu	$t0,$t0,1	# increase
	andi	$t1,$t0,0xf	# check lowest digit
	sltiu	$t2,$t1,0xa	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x6	# adjust lowest digit
	andi	$t1,$t0,0xf0	# check next digit
	sltiu	$t2,$t1,0x60	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa0	# adjust digit
	andi	$t1,$t0,0xf00	# check minute digit
	sltiu	$t2,$t1,0xa00	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x600	# adjust digit
	andi	$t1,$t0,0xf000	# check last digit
	sltiu	$t2,$t1,0x6000	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa000	# adjust last digit
tiend:	sw	$t0,0($a0)	# save updated result
	jr	$ra		# return
	nop

  # you can write your code for subroutine "hexasc" below this line
  #
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

	#jr $ra
	#nop
	
	PUSH	($ra)
	move 	$t1, $a0			# Sparar vårt argument i temp så vi sedan kan använda det 
	
	while:
		ble	$t1, $zero, exit_delay	# kollar ms > 0
		nop
		sub	$t1, $t1, 1 		# ms--;
		
	li	$t2, 0				# int i	= 0		
	for:
		bge	$t2, 4711, while	# kollar om i < konstaten isåfall gå till while eller gå vidare
		nop
		addi	$t2, $t2, 1		# i++;
		j	for			# Kör om loopen i nästa iteration
		nop
			
	exit_delay:				# Slut på subroutine 
		POP	($ra)			# "resettar" return register 
		jr	$ra			#hopppar tillbaka
		nop

time2string:
	PUSH	($s0)
	PUSH	($s1)				# Save contents of s1 to restore it after the function ends
	PUSH	($ra)				# Save the return adress on the stack
	move	$s1, $a1			# Move contents of $a0 to $s1 so we can work with it
	move	$s0,$a0

	# Första siffran
	andi 	$t1, $s1, 0xf000		# Sparar bittarna mellan index 15 till 12 genom maskining andi med ettor där vi ska maska
	srl 	$a0, $t1, 12			# shiftar bitsen to minsta positionen och lägger de i a0 
	jal	hexasc				# kallar på funktionen hexasc som kommer göra om värdet till hexa
	nop
	sb 	$v0, 0($s0)		 	# Sparar värdet som returneras från hexasc i första "byte location i s1				

	# Andra siffran
	andi 	$t1, $s1, 0x0f00		# Sparar bittarna mellan index 11 till 8 genom maskining andi med ettor där vi ska maska
	srl 	$a0, $t1, 8			# shiftar bitsen to minsta positionen och lägger de i a0 
	jal	hexasc				# kallar på funktionen hexasc som kommer göra om värdet till hexa
	nop
	sb 	$v0, 1($s0)		 	# Sparar värdet som returneras från hexasc i andra "byte location i s1	
											

	# Kolonn tecken
	li 	$t1, 0x3a			# hämtar ASCII värdet för kolon tecknet
	sb 	$t1, 2($s0)		 	# Sparar värdet i tredje byte location 
					
	
	# Tredje siffra
	andi 	$t1, $s1, 0x00f0		#Sparar bittarna mellan index 7 till 4 genom maskining andi med ettor där vi ska maska
	srl 	$a0, $t1, 4			# shiftar bitsen to minsta positionen och lägger de i a0 
	jal	hexasc				# kallar på funktionen hexasc som kommer göra om värdet till hexa
	nop
	sb 	$v0, 3($s0)		 	# Sparar värdet som returneras från hexasc i fjärde "byte location i s1	
						
										
	# Fjärde siffra
	andi 	$t1, $s1, 0x000f		# Sparar bittarna mellan index 3 till 0 genom maskining andi med ettor där vi ska maska
	move 	$a0, $t1			# flyttar direkt toll a0 eftersom de redan ligger på rätt plats.
	jal	hexasc				# kallar på funktionen hexasc som kommer göra om värdet till hexa
	nop
	sb 	$v0, 4($s0)		 	# Sparar värdet som returneras från hexasc i femte "byte location i s1	
						
						


	# NUL byte
	li	$t1, 0x00			# hämtar ASCII kod för NUL värde
	sb 	$t1, 5($s0)		 	# Sparar värdet som returneras från hexasc i 6te byte location i s1
	j	exit_time2string

	#slut på subroutinen, resettar alla register och hoppar tillbaka tillbaka
	exit_time2string:																																																																																										
		POP	($ra)
		POP	($s1)
		POP	($s0)	
 		jr 	$ra
 		nop	

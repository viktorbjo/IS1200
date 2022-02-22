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

	#jr $ra
	#nop
	
	PUSH	$ra
	move 	$t1, $a0			# Sparar vårt argument i temp så vi sedan kan använda det 
	
	while:
		ble	$t1, $zero, exit_delay	# kollar ms > 0
		nop
		sub	$t1, $t1, 1 		# ms--;
		
	li	$t2, 0				# int i	= 0		
	for:
		bge	$t2, 4000, while	# kollar om i < konstaten isåfall gå till while eller gå vidare
		nop
		addi	$t2, $t2, 1		# i++;
		j	for			# Kör om loopen i nästa iteration
		nop
			
	exit_delay:				# Slut på subroutine 
		POP	$ra			# "resettar" return register 
		jr	$ra			#hopppar tillbaka
		nop

time2string:
	PUSH	$s0
	PUSH	$s1				# skicka dessa register till stacken
	PUSH	$ra				# samma med return adressen
	move	$s1, $a1			#  Flyttar a0 till s1
	move	$s0,$a0

	# Första Siffran
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
					
	
	# Tredje siffran
	andi 	$t1, $s1, 0x00f0		#Sparar bittarna mellan index 7 till 4 genom maskining andi med ettor där vi ska maska
	srl 	$a0, $t1, 4			# shiftar bitsen to minsta positionen och lägger de i a0 
	jal	hexasc				# kallar på funktionen hexasc som kommer göra om värdet till hexa
	nop
	sb 	$v0, 3($s0)		 	# Sparar värdet som returneras från hexasc i fjärde "byte location i s1	
						
										
	# Fjärde siffran
	andi 	$t1, $s1, 0x000f		# Sparar bittarna mellan index 3 till 0 genom maskining andi med ettor där vi ska maska
	move 	$a0, $t1			# flyttar direkt toll a0 eftersom de redan ligger på rätt plats.
	jal	hexasc				# kallar på funktionen hexasc som kommer göra om värdet till hexa
	nop
	sb 	$v0, 4($s0)		 	# Sparar värdet som returneras från hexasc i femte "byte location i s1	
						
	# Addera D eller E 
#	andi $t1, $s1, 0x000f 
#	beq $t1, 0x0000, addE 
#	beq $t1, 0x0002, addE 
#	beq $t1, 0x0003, addD 
#	beq $t1, 0x0004, addE 
#	beq $t1, 0x0005, addD 
#	beq $t1, 0x0006, addE 
#	beq $t1, 0x0007, addD 
#	beq $t1, 0x0008, addE 
#	beq $t1, 0x0009, addD 					


	# NUL byte
	li	$t1, 0x00			# hämtar ASCII kod för NUL värde
	sb 	$t1, 5($s0)		 	# Sparar värdet som returneras från hexasc i 6te byte location i s1
	j	exit_time2string		

	#slut på subroutinen, resettar alla register och hoppar tillbaka tillbaka
	exit_time2string:																																																																																										
		POP	$ra
		POP	$s1
		POP	$s0	
 		jr 	$ra
 		nop	
 	
 #addE: 
 #	li $t1, 0x45 # Lägg in ASCII nummret för E i t1 
 #	sb $t1, 5($s0) # Spara i 6te byte location i s0
 #	li $t1, 0x00 # laddar in ASCII för NUL
 #	sb $t1, 6($s0) # Sparar NUL i 7de byte location
 #	j exit_time2string 
 #	nop 
 #addD: 
 #	li $t1, 0x44 # Lägg in ASCII nummret för D i t1
 #	sb $t1, 5($s0) #  Spara i 6te byte location i s0
 #	li $t1, 0x00 # laddar in ASCII för NUL 
 #	sb $t1, 6($s0) # Sparar NUL i 7de byte location
 #	j exit_time2string 
 #	nop 		
 

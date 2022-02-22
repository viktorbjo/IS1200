
   # hexmain.asm
  # Written 2015-09-04 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

	.text
main:
	li	$a0,17		# change this to test different values

	jal	hexasc		# call hexasc
	nop			# delay slot filler (just in case)	

	move	$a0,$v0		# copy return value to argument register

	li	$v0,11		# syscall with v0 = 11 will print out
	syscall			# one byte from a0 to the Run I/O window
	
stop:	j	stop		# stop after one run
	nop			# delay slot filler (just in case)

  # You can write your own code for hexasc here
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

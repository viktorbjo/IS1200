# Initiate 
	addi 	$a0, $zero, 1		# Ändra på immidiate för att ändra värdet
	addi $a3, $a3, 1
# Kollar om in värdet är 0 
	beq 	$a0, $zero, noll
	beq $a0, $a3, noll	

	
# Main factorial function
	add	$v0, $a0, $zero		# Värdet på det initierade värdet. 
	add	$a1, $a0, $zero
	
While:
	addi	$a1, $a1, -1 # Sänker initerade värdet med 1 
	beq	$a1, 1,	end # Hoppar till done om tillräckligt många minus har adderats till initierade värdet 
	mul	$v0, $v0, $a1 # Multiplicerar nuvarande värde 
	beq	$zero, $zero, While # Återgår till loopen. 

noll: 
	addi 	$v0, $zero, 1 # adderar 1 om in värdet är 0! 


# Stopploop
end:
	beq	$0, $0, end # Klar
	nop 

# Initiate 
	addi 	$a0, $zero, 1		# �ndra p� immidiate f�r att �ndra v�rdet
	addi $a3, $a3, 1
# Kollar om in v�rdet �r 0 
	beq 	$a0, $zero, noll
	beq $a0, $a3, noll	

	
# Main factorial function
	add	$v0, $a0, $zero		# V�rdet p� det initierade v�rdet. 
	add	$a1, $a0, $zero
	
While:
	addi	$a1, $a1, -1 # S�nker initerade v�rdet med 1 
	beq	$a1, 1,	end # Hoppar till done om tillr�ckligt m�nga minus har adderats till initierade v�rdet 
	mul	$v0, $v0, $a1 # Multiplicerar nuvarande v�rde 
	beq	$zero, $zero, While # �terg�r till loopen. 

noll: 
	addi 	$v0, $zero, 1 # adderar 1 om in v�rdet �r 0! 


# Stopploop
end:
	beq	$0, $0, end # Klar
	nop 

# Initiate 
	addi 	$a0, $zero, 5		# �ndra p� immidiate f�r att �ndra v�rdet
	
	
# Main factorial function
	add	$v0, $a0, $zero		# V�rdet p� det initierade v�rdet. 
	add	$a1, $a0, $zero
	
While:
	addi	$a1, $a1, -1 # S�nker initerade v�rdet med 1 
	beq	$a1, 1,	end # Hoppar till done om tillr�ckligt m�nga minus har adderats till initierade v�rdet 
	mul	$v0, $v0, $a1 # Multiplicerar nuvarande v�rde 
	beq	$zero, $zero, While # �terg�r till loopen. 
	
# Stopploop
end:
	beq	$0, $0, end # Klar
	nop 

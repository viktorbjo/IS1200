addi $a0, $0, 0		# a0 register där vi börjar med vårat n värde
addi $v0, $0, 1		# return värdet = 1 som startvärde (!0 == 1)
addi $v1, $a0, 1	# lägger på 1 på vårat n värde och lägger det ett annat register v1 (k)
addi $a2, $0, 1		# sätter vårt i värde till 1 för den första loopen  

while:
	beq $a2, $v1, end	# om i inte är lika med k och om i(a2) == k(v1) så är vi klara
	addi $a2, $a2, 1	# ökar värdet på i, (som i++)
	addi $a1, $0, 0		# initsierar produkten till 0
	
	addi $a3,$0, 1		# sätter j värdet till 1 så typ samma som med i fast nu för inre loopen
	
mul:
	beq $a3, $a2, check	#  om j(a3) är lika med i(a2) så är vi klara (multiadding)
	addi $a3, $a3, 1	# ökar värdet på j (som j++)
	add $a1, $a1, $v0	# product == product + return
	beq $0, $0, mul		# hoppar tillbaks till multi loopen
	
check:
	addi $v0, $a1, 0	# sätter return värdet till produkten av multiadding
	beq $0, $0, while	# hoppar tillbaka till den yttre loopen
	
end:
	beq $0, $0, end		# oändlig unconditional branch loop




	.global net2hostl_asm


net2hostl_asm:	
		push %ebp
		movl %esp, %ebp
		movl 8(%esp), %eax
		xchg %ah, %al
		ror $16, %eax
		xchg %ah, %al
		pop %ebp
		ret
		

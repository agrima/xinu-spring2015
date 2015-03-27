


	.global host2netl_asm


host2netl_asm:	
		push %ebp
		mov %esp, %ebp
		mov 8(%esp), %eax
		xchg %ah, %al
		rol $16, %eax
		xchg %ah, %al
		pop %ebp
		ret

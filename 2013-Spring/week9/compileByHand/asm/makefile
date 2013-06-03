all: assemble link

assemble:
	nasm -f elf *.s
link:
	gcc -m32 *.o 
clean:
	rm a.out
	rm *.o
all: compile suid aslr
compile:
	gcc -fno-stack-protector -z execstack bufferOverflow.c -o bufferOverflow  -std=c99 -m32
suid:
	sudo chown root:root bufferOverflow
	sudo chmod 4777 bufferOverflow

aslr:
	sudo sysctl -w kernel.randomize_va_space=0
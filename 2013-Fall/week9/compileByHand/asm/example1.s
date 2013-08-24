BITS 32
	global main
	extern fread
	extern fopen
	extern printf

	
readInts:             ;readInts(FILE* file, int* buffer){
	push ebp
	mov ebp,esp
	pusha
	mov eax, [ebp+8]    ;file
	mov ebx, [ebp+12]   ;buffer
	;fread(buffer, sizeof(int), BUFSIZE, file);
	push eax
	push 1024
	push 4
	push ebx
	call fread
	add esp,4*4
	popa
	leave
	ret

	
	
printInts: ;void printInts(int * buffer, int number){
	push ebp
	mov ebp,esp
	sub esp,4
	pusha
	mov esi, [ebp+8]    ;buffer
	mov ebx, [ebp+12]   ;number
	mov edi,0
.top:
	mov eax, [esi+edi*4+4]
	push eax
	mov eax,[esi+edi*4]
	push eax
	push format
	call printf
	add esp,4*3
	add edi,2 ;i
	cmp edi, [ebp+12] ;if(i<number) 
	jl printInts.top   ;      goto top
	
	popa
	add esp,4
	leave
	ret
	
main:
	push ebp
	mov ebp,esp
	pusha
	sub esp, 4*1024
		
	push read
	push things
	call fopen
	add esp, 8
	mov ebx,eax
	mov eax, esp
	
	push eax
	push ebx
	call readInts ;int readInts(FILE* file, int* buffer){
	add esp,8

	mov eax,esp
	
	push 1024
	push eax
	call printInts ;void printInts(int * buffer, int number){
	add esp,8
	add esp, 4*1024
	popa
	leave
	ret


section .data
format: db "%d, %d",0xa,0
points: dd things
things:	db "points",0
read: db "r",0

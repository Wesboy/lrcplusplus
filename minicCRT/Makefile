#entry.o: entry.c minicrt.h
#	gcc -m32 -c -fno-builtin -nostdlib -fno-stack-protector entry.c -o entry.o
#malloc.o: malloc.c minicrt.h
#	gcc -m32 -c -fno-builtin -nostdlib -fno-stack-protector malloc.c -o malloc.o
#string.o: string.c minicrt.h
#	gcc -m32 -c -fno-builtin -nostdlib -fno-stack-protector string.c -o string.o
#stdio.o: stdio.c minicrt.h
#	gcc -m32 -c -fno-builtin -nostdlib -fno-stack-protector stdio.c -o stdio.o
#printf.o: printf.c minicrt.h
#	gcc i-m32 -c -fno-builtin -nostdlib -fno-stack-protector printf.c -o printf.o

target:
	gcc -m32 -c -fno-builtin -nostdlib -fno-stack-protector entry.c malloc.c string.c stdio.c printf.c
	ar -rs minicrt.a malloc.o printf.o stdio.o string.o

test:
	gcc -c -ggdb -fno-builtin -nostdlib -fno-stack-protector test.c -m32 -g
	ld -static -e mini_crt_entry entry.o test.o minicrt.a -o test -m elf_i386

clean:
	rm *.o *.a test

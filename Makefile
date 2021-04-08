CC=gcc 
CFLAGS= -std=c11 -Wall -g -lm 

make-boyer-moore: main.c Boyer-Moore.c Boyer-Moore.h helpers.c helpers.h 
	$(CC) $(CFLAGS) *.c -o boyermoore

clean:
	rm -rf -v boyermoore

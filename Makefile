CFLAGS = -Wall -g

all: main.o names.o operators.o sexpr.o tokenizer.o
	gcc $(CFLAGS) -o sexpr-repl main.o names.o operators.o sexpr.o tokenizer.o

main.o: main.c
	gcc $(CFLAGS) -c main.c

names.o: names.c
	gcc $(CFLAGS) -c names.c

operators.o: operators.c
	gcc $(CFLAGS) -c operators.c

sexpr.o: sexpr.c
	gcc $(CFLAGS) -c sexpr.c

tokenizer.o: tokenizer.c
	gcc $(CFLAGS) -c tokenizer.c

clean:
	rm -f *.o sexpr-repl

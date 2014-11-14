CFLAGS = -Wall -g

all: arithmetic.o comparison.o main.o names.o operators.o procedures.o sexpr.o tokenizer.o
	gcc $(CFLAGS) -o hero-scheme arithmetic.o comparison.o main.o names.o procedures.o operators.o sexpr.o tokenizer.o

arithmetic.o: arithmetic.c
	gcc $(CFLAGS) -c arithmetic.c

comparison.o: comparison.c
	gcc $(CFLAGS) -c comparison.c

main.o: main.c
	gcc $(CFLAGS) -c main.c

names.o: names.c
	gcc $(CFLAGS) -c names.c

operators.o: operators.c
	gcc $(CFLAGS) -c operators.c

procedures.o: procedures.c
	gcc  $(CFLAGS) -c procedures.c

sexpr.o: sexpr.c
	gcc $(CFLAGS) -c sexpr.c

tokenizer.o: tokenizer.c
	gcc $(CFLAGS) -c tokenizer.c

clean:
	rm -f *.o hero-scheme 

CFLAGS=-Wall -Werror -std=gnu99 -pedantic -ggdb3
SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c, %.o, $(SRCS))
PROGRAM1=test_c4

$(PROGRAM1): $(OBJS)
	gcc $(CFLAGS) -o $@ $(OBJS)

%.o: %.c 
	gcc -c $(CFLAGS) $<

clean:
	rm -f $(OBJS) $(PROGRAM1) *~


cards.o: cards.h
deck.o: deck.h
eval.c: eval.h
future.c: future.h
input.c: input.h
main.o: %.h

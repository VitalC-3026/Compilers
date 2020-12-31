CC := g++ -g
CFLAGS := -Wall -Wextra -std=c++11 # without debug
TARGET := ./bin/main

all: run
main.lex.yy.c: main.l
	flex --noyywrap -o main.lex.yy.cpp main.l

main.tab.c: main.y
	bison -o main.tab.cpp --defines=main.tab.h -v main.y


lex: main.lex.yy.c

yacc: main.tab.c

main:
	$(CC) $(CFLAGS) $(shell ls ./*.cpp) -o ./bin/main

.PHONY: all clean main run lex yacc test 

run: lex yacc main

clean:
	rm -f main.lex.yy.cpp main.tab.cpp  main.tab.h $(TARGET) *.o ./bin/*

test:
	./bin/main tests/test_main.cpp results/test.res.txt
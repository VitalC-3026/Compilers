CC := g++
CFLAGS := -Wall -Wextra -std=c++11 # without debug
TARGET := ./bin/main

all: run

main.lex.yy.c: main.l
	flex --noyywrap -o main.lex.yy.cpp main.l

main.tab.c: main.y
	bison -o main.tab.cpp --defines=main.tab.h -v main.y

pch.h.gch: pch.h
	g++ -x c++-header -o pch.h.gch -c pch.h

lex: main.lex.yy.c

yacc: main.tab.c

main: pch.h.gch
	$(CC) $(CFLAGS) $(shell ls ./*.cpp) -o ./bin/main

.PHONY: all clean main run lex yacc test 

run: lex yacc main

clean:
	rm -f main.lex.yy.cpp main.tab.cpp  main.tab.h pch.h.gch $(TARGET) *.o ./bin/*

test:
	./bin/main tests/test.c result/test.res.txt
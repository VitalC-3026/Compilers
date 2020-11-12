.PHONY: lc, lcc, clean
lc:
	flex hw4.l
	gcc lex.yy.c -o lc.out
	./lc.out
lcc:
	flex -+ hw4.l
	g++ lex.yy.cc -o lcc.out
	./lcc.out
clean:
	rm *.out
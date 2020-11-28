.PHONY: all clean run main test debug
all: run
main: 
	g++ $(shell ls *.cpp) -o main.out
run: main
test: run
	for file in $(basename $(shell find files/*.c)); \
	do \
		./main.out <$$file.c >$$file.res.txt; \
	done
clean:
	rm -f *.out files/*.res.txt
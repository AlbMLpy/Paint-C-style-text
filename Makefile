all : analyzer
analyzer : analyzer.o main.o
	gcc main.o analyzer.o -o analyzer
main.o : analyzer.c analyzer.h main.c
	gcc -c -Wall -Werror -g  main.c
analyzer.o : analyzer.c analyzer.h
	gcc -c -Wall -Werror -g analyzer.c
clean:
	rm -f *.o

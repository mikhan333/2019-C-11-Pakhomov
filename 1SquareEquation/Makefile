
test: test_square
	./test_square
test_square: ./src/test_square.c libsquare.a
	cc -c ./src/test_square.c
	cc -o test_square test_square.o -L. -lsquare -lm
	rm test_square.o

start: main
	./main
main: ./src/main.c libsquare.a
	cc -c ./src/main.c
	cc -o main main.o -L. -lsquare -lm
	rm main.o

libsquare.a: square.o
	ar cr libsquare.a square.o
square.o: ./src/square.c
	cc -c ./src/square.c

clean:
	rm -f square.o libsquare.a main.o main
	rm -f test_square.o test_square

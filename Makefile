all: Tape.o Record.o PolyphaseSort.o
	g++ -std=c++17 main.cpp Tape.o Record.o PolyphaseSort.o -o main.out
Tape.o:
	g++ -c -std=c++17  database/Tape.cpp -o Tape.o
Record.o:
	g++ -c -std=c++17  database/Record.cpp -o Record.o
PolyphaseSort.o:
	g++ -c -std=c++17  sort/PolyphaseSort.cpp -o PolyphaseSort.o
clean:
	rm -f *.out *.o
run: clean all
	./main.out
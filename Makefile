all: Logger.o Tape.o Record.o PolyphaseSort.o
	g++ -std=c++17 main.cpp Logger.o Tape.o Record.o PolyphaseSort.o -o main.out
Logger.o:
	g++ -c -std=c++17  utils/Logger.cpp -o Logger.o
Tape.o:
	g++ -c -std=c++17  database/Tape.cpp -o Tape.o
Record.o:
	g++ -c -std=c++17  database/Record.cpp -o Record.o
PolyphaseSort.o:
	g++ -c -std=c++17  sort/PolyphaseSort.cpp -o PolyphaseSort.o
clean:
	rm -f *.out *.o database/tapes/tape1 database/tapes/tape2 database/tapes/tape3
# output in generate is input in run_main
generate:
	python3 utils/generate_input.py --output $(input) --records $(records)
# input - input path, output - sorted result path, records - number to generate and calc, block - size of buffer
run_main: clean all
	./main.out $(input) $(output) $(records) $(block)
# EXAMPLE: make run input='database/input_examples/input_records' output='database/input_examples/input_records_o' records=10000 block=8
run: generate run_main
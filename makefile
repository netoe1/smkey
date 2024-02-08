FLAGS = -Wall
LIBS = -levdev


all:
	gcc -o ./bin/main.o ./src/main.c ${FLAGS} ${LIBS}
run:
	./bin/main.o
clean:
	rm -rf ./bin/*.o
FLAGS=-lncurses -lpthread

all: barbeiro

barbeiro:
	gcc barbeiro.c -o barbeiro $(FLAGS)

queue_test:
	gcc queue_test.c queue.c -o queue_test $(FLAGS)

clean:
	rm -f barbeiro queue_test

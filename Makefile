prog3: prog3.c node0.c node1.c node2.c node3.c
	gcc -g -pthread prog3.c node0.c node1.c node2.c node3.c -o prog



.PHONY: clean

clean:
	rm -f prog*.o

all: clean prog3 clean

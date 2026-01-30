all: build clean

build: main.o queue.o pcb.o clock.o scheduler.o cpu.o io.o lista.o stats.o
	gcc main.o queue.o pcb.o clock.o cpu.o io.o scheduler.o lista.o stats.o -Wall -std=c99 -o peixe 

main.o:
	gcc -c main.c -o main.o

queue.o:
	gcc -c queue/queue.c -o queue.o

pcb.o:
	gcc -c pcb/pcb.c -o pcb.o

clock.o:
	gcc -c clock/clock.c -o clock.o

scheduler.o:
	gcc -c scheduler/scheduler.c -o scheduler.o

cpu.o:
	gcc -c cpu/cpu.c -o cpu.o

io.o:
	gcc -c io/io.c -o io.o

lista.o:
	gcc -c Lista/lista.c -o lista.o

stats.o:
	gcc -c stats/stats.c -o stats.o

clean:
	rm *.o

clear:
	rm peixe

run:
	./peixe
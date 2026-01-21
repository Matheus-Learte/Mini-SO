all: main.o queue.o pcb.o clock.o scheduler.o cpu.o io.o
	gcc main.o queue.o pcb.o clock.o cpu.o io.o scheduler.o -Wall -std=c99 -o peixe

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

clean:
	rm *.o peixe

run:
	./peixe
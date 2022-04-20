CC = g++
CFLAGS = -c -Wall

target: run

run: graphs.exe
	./graphs.exe

graphs.exe: main.o graph_list.o graph_list.hh
	${CC} main.o graph_list.o -o graphs.exe

main.o: main.cpp graph_list.hh
	${CC} ${CFLAGS} main.cpp

graph_list.o: graph_list.cpp graph_list.hh
	${CC} ${CFLAGS} graph_list.cpp

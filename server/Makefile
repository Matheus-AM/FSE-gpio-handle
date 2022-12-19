COMP = ./components/
LIBS = -lpthread -lncurses
all: server

server: server.o $(COMP)menu.o
	g++ -o server server.o $(COMP)menu.o $(LIBS)

menu.o: $(COMP)menu.cpp $(COMP)menu.h
	g++ -c $(COMP)menu.cpp $(LIBS)

server.o: server.cpp server.h
	g++ -c server.cpp $(LIBS)

run:
	./server
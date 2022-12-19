COMP = ./components/
all: client

client: client.o $(COMP)gpio.o
	g++ -o client client.o $(COMP)gpio.o -lbcm2835 -lpthread

gpio.o: $(COMP)gpio.cpp $(COMP)gpio.h
	g++ -c $(COMP)gpio.cpp -lbcm2835 

client.o: client.cpp client.h
	g++ -c client.cpp -lpthread 

run:
	./client
test: main.o
	g++ main.o -o test
	rm *.o

main.o: main.cpp
	g++ -c main.cpp 

all: test ;

clean:
	rm -rf main main.o

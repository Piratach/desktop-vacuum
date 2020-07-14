all: main 

main: main.o cleanuptools.o directory.o circbutton.o rectbutton.o
	g++ -std=c++17 main.o cleanuptools.o directory.o circbutton.o rectbutton.o -o main -lstdc++ -lsfml-graphics -lsfml-window -lsfml-system
	rm -r *.o

main.o: main.cpp
	g++ -std=c++17 -c main.cpp

cleanuptools.o: cleanuptools.hpp cleanuptools.cpp
	g++ -std=c++17 -c cleanuptools.cpp

directory.o: directory.cpp directory.hpp
	g++ -std=c++17 -c directory.cpp

rectbutton.o: rectbutton.cpp rectbutton.hpp
	g++ -std=c++17 -c rectbutton.cpp

circbutton.o: circbutton.hpp circbutton.cpp
	g++ -std=c++17 -c circbutton.cpp

clean:
	rm -rf main *.o

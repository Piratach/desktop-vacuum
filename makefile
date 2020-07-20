all: main 

main: main.o scene.o cleanuptools.o directory.o circbutton.o rectbutton.o tab.o
	g++ -std=c++17 main.o scene.o cleanuptools.o directory.o circbutton.o rectbutton.o tab.o -o main -lstdc++ -lsfml-graphics -lsfml-window -lsfml-system
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

tab.o: tab.hpp tab.cpp
	g++ -std=c++17 -c tab.cpp

scene.o: scene.hpp scene.cpp
	g++ -std=c++17 -c scene.cpp

makeXML: makeXML.o
	g++ -std=c++17 makeXML.o -o makeXML -lstdc++ -ltinyxml2
	rm -r *.o

makeXML.o: makeXML.cpp
	g++ -std=c++17 -c makeXML.cpp

clean:
	rm -rf main *.o

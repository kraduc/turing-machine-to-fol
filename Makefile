all: tm-to-fol

rebuild: clean all

tm-to-fol: main.o tape.o transition.o 
	g++ -o tm-to-fol transition.o tape.o main.o

transition.o: transition.cpp transition.h
	g++ -c transition.cpp 

tape.o: tape.cpp tape.h
	g++ -c tape.cpp

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o tm-to-fol
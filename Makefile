all: tm-to-fol

rebuild: clean all

tm-to-fol: main.o tape.o transition.o state.o
	g++ -o tm-to-fol transition.o tape.o main.o state.o

transition.o: transition.cpp transition.h
	g++ -c transition.cpp 

tape.o: tape.cpp tape.h
	g++ -c tape.cpp

state.o: state.cpp state.h
	g++ -c state.cpp

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o tm-to-fol
#include<iostream>
#include"tape.h"


void Tape::print_tape() {
	int count = 0;

	while (count < len) {
		for (int i = 0; i < 50; i++) {
			std::cout << tape[count];
			count++;
		}
		std::cout << std::endl;
	}


}

void initialize_tape(char* t, int l, int s) {
	
	tape = t;
	len = l;
	start_index = s;

}

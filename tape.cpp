#include<iostream>
#include"tape.h"


void Tape::print_tape() const {
	int count = 0;

	while (count < len) {
		for (int i = 0; i < 50; i++) {
			std::cout << tape[count];
			count++;
		}
		std::cout << std::endl;
	}


}

void Tape::initialize_tape(char* t, int l, int s) {
	
	tape = t;
	len = l;
	start_index = s;

}

std::vector<int> Tape::marked_cells() const {

	std::vector<int> marked;

	for (int i = 0; i < len; i++) {
		if (tape[i] != '0') marked.push_back(i-start_index);
	}

	return marked;

}

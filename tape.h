#ifndef TAPE_H
#define TAPE_H

#include<vector>

class Tape {

	public:
		// Constructors
		Tape() {}
		Tape(const std::string& t, int l, int s): tape(t), len(l), start_index(s) {}
		
		// Getters
		int length() const { return len; }
		int get_start_index() const { return start_index; }
		int get_char(int index) const { return tape[index]; }
		std::vector<int> marked_cells() const;

		//Setters
		void initialize_tape(const std::string& t, int l, int s);
		void set_start_index(int index) { start_index = index;}
		void set_char(int index, char c) { tape[index] = c; } 

		//Print
		void print_tape() const;

	private:

		std::string tape;
		int len;
		int start_index;

};

#endif

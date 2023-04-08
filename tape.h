#ifndef TAPE_H
#define TAPE_H

class Tape {

	public:
		// Constructors
		Tape() {}
		Tape(char* t, int l, int s): tape(t), len(l), start_index(s) {}

		// Destructor
		~Tape() { delete[] tape; }
		
		// Getters
		int length() const { return len; }
		int get_start_index() const { return start_index; }
		int get_char(int index) const { return tape[index]; }

		//Setters
		void initialize_tape(char* t, int l, int s);
		void set_start_index(int index) { start_index = index;}
		void set_char(int index, char c) { tape[index] = c; } 

		//Print
		void print_tape();

	private:

		char* tape;
		int len;
		int start_index;

};

#endif

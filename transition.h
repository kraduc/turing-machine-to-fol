#ifndef TRANSITION_H
#define TRANSITION_H

class Transition {

	public:

		// Constructor
		Transition(int i, int f, int t, char o, char n, char d): \
			id(i), from_state(f), to_state(t), old_char(o), new_char(n),\
			direction(d) {}
		
		// Getters
		int get_id() const { return id; }
		int get_from_state_index() const { return from_state; }
		int get_to_state_index() const { return to_state; }
		char get_old_char() const { return old_char; }
		char get_new_char() const { return new_char; }
		char get_direction() const { return direction; }

	private:

		int id;
		int from_state;
		int to_state;
		char old_char;
		char new_char;
		char direction;

};

#endif

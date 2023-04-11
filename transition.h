#ifndef TRANSITION_H
#define TRANSITION_H

#include<iostream>

class Transition {

	public:

		// Constructor
		Transition(int i, const std::string& f, const std::string& t, char o, char n, char d): \
			id(i), from_state(f), to_state(t), old_char(o), new_char(n),\
			direction(d) {}
		
		// Getters
		int get_id() const { return id; }
		const std::string& get_from_state() const { return from_state; }
		const std::string& get_to_state() const { return to_state; }
		char get_old_char() const { return old_char; }
		char get_new_char() const { return new_char; }
		char get_direction() const { return direction; }
		bool write() const { return old_char != new_char; }

	private:

		int id;
		std::string from_state;
		std::string to_state;
		char old_char;
		char new_char;
		char direction;

};

std::string int_to_successor(int num);
std::string transition_to_fol(const Transition& tr_data);

#endif

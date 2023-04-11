#ifndef STATE_H
#define STATE_H

#include <string>

class State {

	public:
		// Constructor
		State(const std::string& i, bool f, bool s): id(i), final_state(f), start_state(s) {}
		
		// Getters
		const std::string& get_id() const { return id; }
		bool is_final_state() const { return final_state; }
		bool is_start_state() const { return start_state; }


	private:

		std::string id;
		bool final_state;
		bool start_state;

};

bool operator<(const State& s1, const State& s2);

#endif

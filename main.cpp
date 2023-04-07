#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<sstream>
#include<vector>
#include"state.h"
#include"transition.h"


// TODO: add error checking
bool parse_xml(std::ifstream& istr, std::vector<State>& states, \
		std::vector<Transition>& transitions) {

	std::string str = "";
	while (istr >> str) {
		if (str.compare("<States>") == 0) {

			while (istr >> str && (str.compare("</States>") != 0)) {
			// read <State_#> and store #
			int id = -1;
			char cstr[str.length()+1];
			std::strcpy(cstr, str.c_str());
			char buf[6];
			sscanf(cstr, "<%5s_%d>",buf, &id);
			
			// skip <x> and <y>
			istr >> str >> str;

			// determine if final state or start state
			istr >> str;
			bool final_state = (str[12] == 't');
			std::cout << str[12] << std::endl;
			istr >> str;
			bool start_state = (str[12] == 't');

			std::cout << "id: " << id << std::endl;
			std::cout << "final state: " << final_state << std::endl;
			std::cout << "start state: " << start_state << std::endl;

			states.push_back(State(id, final_state, start_state));

			istr >> str;

			}
			
		}

		if (str.compare("<Transitions>") == 0) {

			while (istr >> str && (str.compare("</Transitions>") != 0)) {
			// read <Transition_#> and store #
			int id = -1;
			char cstr[str.length()+1];
			std::strcpy(cstr, str.c_str());
			char buf[11];
			sscanf(cstr, "<%10s_%d>",buf, &id);

			// read <fromstate>#</fromstate> and store #
			istr >> str;
			int from_state = -1;
			cstr[str.length()+1];
			std::strcpy(cstr, str.c_str());
			char buf2[11];
			sscanf(cstr, "<%9s>%d<%10s>",buf, &from_state, buf2);

			// read <tostate>#</tostate> and store #
			istr >> str;
			int to_state = -1;
			cstr[str.length()+1];
			std::strcpy(cstr, str.c_str());
			sscanf(cstr, "<%7s>%d<%8s>",buf, &to_state, buf2);

			// read <oldchar>#</oldchar> and store #
			istr >> str;
			char old_char = 0;
			cstr[str.length()+1];
			std::strcpy(cstr, str.c_str());
			sscanf(cstr, "<%7s>%c<%8s>",buf, &old_char, buf2);
			
			// read <newchar>#</newchar> and store #
			istr >> str;
			char new_char = 0;
			cstr[str.length()+1];
			std::strcpy(cstr, str.c_str());
			sscanf(cstr, "<%7s>%c<%8s>",buf, &new_char, buf2);
			
			// read <direction>#</direction> and store direction as L, R, or 0
			istr >> str;
			char direction = 0;
			cstr[str.length()+1];
			std::strcpy(cstr, str.c_str());
			sscanf(cstr, "<%9s>%c<%10s>",buf, &direction, buf2);
			if (direction == '1') direction = 'L';
			else if (direction == '2') direction = 'R';

			std::cout << "id: " << id << std::endl;
			std::cout << "from state: " << from_state << std::endl;
			std::cout << "to state: " << to_state << std::endl;
			std::cout << "old char: " << old_char << std::endl;
			std::cout << "new char: " << new_char << std::endl;
			std::cout << "direction: " << direction << std::endl;

			transitions.push_back(Transition(id, from_state, to_state, old_char,\
						new_char, direction));

			istr >> str;

			}
			
		}
	}
	return true;
}

void print_states(std::vector<State>& states) {
	
	for (unsigned int i = 0; i < states.size(); i++) {
		std::cout << states[i].get_id() << std::endl;
	}

}

void print_transitions(std::vector<Transition>& transitions) {
	
	for (unsigned int i = 0; i < transitions.size(); i++) {
		std::cout << transitions[i].get_direction() << std::endl;
	}

}

void usage() {
	std::cerr << "usage: tm-to-xml input_xml\n"; 
}


int main(int argc, char* argv []) {

	if (argc != 2) {
		usage();
		exit(1);
	}

	std::ifstream istr(argv[1]);

	// tbh should probably check that it's an xml file

	if (!istr.good()) {
		std::cerr << "Can't open " << argv[1] << " to read.\n";	
		exit(1);
	}

	std::vector<State> states;
	std::vector<Transition> transitions;

	parse_xml(istr, states, transitions);

}

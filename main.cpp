#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<sstream>
#include<vector>
#include<cassert>
#include"state.h"
#include"transition.h"
#include"tape.h"

// assumes there is only one starting state
int starting_state(const std::vector<State>& states) {
	
	for (unsigned int i = 0; i < states.size(); i++) {
		if (states[i].is_start_state()) return i;
	}
	return -1;
}

// currently using integers instead of successor function
std::string starting_state_to_fol(const std::vector<State>& states, const Tape& tape) {

	std::string fol = "S(0,";
	fol += std::to_string(starting_state(states));
	fol += ")∧C(0,";
	fol += std::to_string(tape.get_start_index());
	fol += ")";

	std::vector<int> marked_cells = tape.marked_cells();

	for (unsigned int i = 0; i < marked_cells.size(); i++) {
		fol += "∧M(0,";
		if (marked_cells[i] < 0) fol += "¬";
		fol += std::to_string(abs(marked_cells[i]));
		fol += ")";
	}

	if (marked_cells.size() != 0) {
		fol += "∧∀y,(¬(";

		for (unsigned int i = 0; i < marked_cells.size(); i++) {
			if (i != 0) fol += "∨";
			fol += "(y≡";
			if (marked_cells[i] < 0) fol += "¬";
			fol += std::to_string(abs(marked_cells[i]));
			fol += ")";
		}

		fol += ")→¬M(0,y))";
	} else {
		fol += "∧∀y,(¬M(0,y))";
	}
	
	return fol;

}

void generate_dot_bram(std::ofstream& ostr, const std::vector<Transition>& transitions,\
		const std::vector<State>& states, const Tape& tape) {
	ostr << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n"\
		 << "<bram>\n"\
		 << "  <program>turing-machine-to-fol</program>\n"\
		 << "  <Version>1.0</Version>\n"\
		 << "  <metadata>\n"\
		 << "      <author>ahh</author>\n"\
		 << "      <created>ahh</created>\n"\
		 << "      <modified>ahh</modified>\n"\
		 << "  </metadata>\n\n"\
		 << "  <proof id=\"0\">\n";

	ostr << "    <assumption linenum=\"0\">\n"\
		 << "      <raw>";

	ostr << starting_state_to_fol(states, tape);	

	ostr << "</raw>\n"\
		 << "    </assumption>\n";

	for (unsigned int i = 0; i < transitions.size(); i++) {
		// std::cout << "HELLO" << std::endl;
		ostr << "    <assumption linenum=\"" << i + 1 << "\">\n"\
			<< "      <raw>";

		ostr << transition_to_fol(transitions[i]);	

		ostr << "</raw>\n"\
			<< "    </assumption>\n";

	}

	ostr << "  </proof>\n"\
		 << "</bram>\n"\
		 << std::endl;
}


// TODO: add error checking
bool parse_xml(std::ifstream& istr, std::vector<State>& states, \
		std::vector<Transition>& transitions) {

	std::string str = "";
	while (istr >> str) {
		if (str.compare("<States>") == 0) {

			while (istr >> str && (str.compare("</States>") != 0)) {
				// read <State_#> and store #
				std::string id;
				id = str.substr(7);
				id.pop_back();

				// skip <x> and <y>
				istr >> str >> str;

				// determine if final state or start state
				istr >> str;
				bool final_state = (str[12] == 't');
				istr >> str;
				bool start_state = (str[12] == 't');

				states.push_back(State(id, final_state, start_state));

				istr >> str;

			}
			
		}

		if (str.compare("<Transitions>") == 0) {

			while (istr >> str && (str.compare("</Transitions>") != 0)) {
				// read <Transition_#> and store #
				int id = -1;
				str = str.substr(12);
				str.pop_back();
				id = std::stoi(str);

				// read <fromstate>#</fromstate> and store #
				istr >> str;
				std::string from_state = str.substr(11);
				int ankle_pos = from_state.find('<');
				from_state = from_state.substr(0, ankle_pos);

				// read <tostate>#</tostate> and store #
				istr >> str;
				std::string to_state;
				to_state = str.substr(9);
				ankle_pos = to_state.find('<');
				to_state = to_state.substr(0, ankle_pos);

				// read <oldchar>#</oldchar> and store #
				istr >> str;
				char old_char = str[9];
				
				// read <newchar>#</newchar> and store #
				istr >> str;
				char new_char = str[9];
				if (new_char == 'n') new_char = old_char;
					
				// read <direction>#</direction> and store direction as L, R, or 0
				istr >> str;
				char direction = str[11];
				if (direction == '1') direction = 'L';
				else if (direction == '2') direction = 'R';

				transitions.push_back(Transition(id, from_state, to_state, old_char,\
							new_char, direction));

				istr >> str;

			}
			
		}
	}
	return true;
}

void parse_tape(std::ifstream& istr, Tape& tape) {
	
	std::string str;
	istr >> str;
	assert (str == "Tape");
	int length = 0;
	istr >> length;
	std::string tape_str;
	char c;

	for (int i = 0; i < length; i++) {
		istr >> c;
		tape_str += c;
	}

	int start_index = 0;
	istr >> str;
	start_index = stoi(str);

	tape.initialize_tape(tape_str, length, start_index);
	
}

// debugging
void print_tape(const Tape& tape) {
	std::cout << "length: " << tape.length() << std::endl;
	std::cout << "starting index: " << tape.get_start_index() << std::endl;
	std::cout << "val at starting index: " << tape.get_char(tape.get_start_index()) << std::endl;
	std::cout << "tape: " << std::endl;
	tape.print_tape();
}

// debugging
void print_states(const std::vector<State>& states) {
	
	for (unsigned int i = 0; i < states.size(); i++) {
		std::cout << states[i].get_id() << std::endl;
	}

}

// debugging
void print_transitions(const std::vector<Transition>& transitions) {
	
	for (unsigned int i = 0; i < transitions.size(); i++) {
		std::cout << transitions[i].get_direction() << std::endl;
	}

}

void usage() {
	std::cerr << "usage: tm-to-fol input_xml tape_txt\n"; 
}


int main(int argc, char* argv []) {

	if (argc != 3) {
		usage();
		exit(1);
	}

	std::ifstream istr(argv[1]);

	// TODO: tbh should probably check that it's an xml file
	
	std::string filename = std::string(argv[1]);

	if (filename.substr(filename.size()-4) != ".xml") {
		std::cerr << "Turing machine file must be an xml file.\n";	
		usage();
		exit(1);
	}

	if (!istr.good()) {
		std::cerr << "Can't open " << argv[1] << " to read.\n";	
		exit(1);
	}

	std::ifstream istr2(argv[2]);

	if (!istr2.good()) {
		std::cerr << "Can't open " << argv[2] << " to read.\n";	
		exit(1);
	}

	std::vector<State> states;
	std::vector<Transition> transitions;
	Tape tape;

	parse_xml(istr, states, transitions);

	parse_tape(istr2, tape);

	std::string outfilename = filename.substr(0, filename.size()-4) + ".bram"; 
	std::ofstream ostr(outfilename);
	if (!ostr.good()) {
		std::cerr << "Can't open " << outfilename << " to write.\n";
		exit(1);
	}

	generate_dot_bram(ostr, transitions, states, tape);

}

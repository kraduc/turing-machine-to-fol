#include<iostream>
#include<string>
#include"transition.h"


std::string int_to_successor(int num) {

	std::string output = "";
	for (int i = 1; i <= num; i++) {
		output += "s(";
	}
	output += '0';

	for (int i = 1; i <= num; i++) {
		output += ")";
	}
	return output;
}

std::string transition_to_fol(Transition& tr_data) {
	
	std::string from_state = int_to_successor(tr_data.get_from_state_index());
	std::string to_state = int_to_successor(tr_data.get_to_state_index());

	std::string from_cell;
	std::string to_cell;

	if (tr_data.get_direction() == 'L') {
		to_cell = "x";
		from_cell = "s(x)";
	} else if (tr_data.get_direction() == 'R') {
		to_cell = "s(x)";
		from_cell = "x";
	} else {
		to_cell = from_cell = "x";
	}

	std::string fol = "∀t,∀x,((S(t," + from_state + ")∧C(t," + from_cell + ")∧";

	if (tr_data.get_old_char() - '0' == 0) fol += "¬";

	fol += "M(t," + from_cell + "))→(S(s(t)," + to_state + ")∧C(s(t)," + to_cell + ")∧∀y,(";

	if (tr_data.write()) fol += "¬(y≡x)→(";

	std::cout << tr_data.write() << std::endl;

	fol += "M(s(t),y)↔M(t,y))))";

	if (tr_data.write()) fol += ")";
	
	return fol;

}


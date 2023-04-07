

class State {

	public:
		// Constructor
		State(int i, bool f, bool s): id(i), final_state(f), start_state(s) {}
		
		// Getters
		int get_id() const { return id; }
		bool is_final_state() const { return final_state; }
		bool is_start_state() const { return start_state; }


	private:

		int id;
		bool final_state;
		bool start_state;

};

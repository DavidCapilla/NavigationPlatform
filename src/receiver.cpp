#include "receiver.hpp"

void receiver::read_signal (string signal_filename) {
	signal.open(signal_filename);
	
	retrieve_platform_size_from_signal();
	retrieve_rovers_initial_information_from_signal();

	signal.close();
}

void receiver::retrieve_platform_size_from_signal(void) {
	int x, y;

	signal >> x;
	signal >> y;

	platform_size.push_back(x);
	platform_size.push_back(y);
}

receiver::receiver(void) {
	number_of_rovers = 0;
}

void receiver::retrieve_rovers_initial_information_from_signal(void) {
	int x, y;
	char att;
	string ord;
	vector<int> i_pos(2);
	
	while (signal.good()){
		// Get the initial position of the rover
		signal >> x;
		// This check is in order to know if the reading is finished already.
		if(signal.eof()){
			break;
		}
		signal >> y;
		i_pos[0] = x;
		i_pos[1] = y;
		initial_position.push_back(i_pos);
		
		// Get the attitude of the rover
		signal >> att;
		attitude.push_back(att);
		
		// Get the order of the rover
		signal >> ord;
		order.push_back(ord);
		
		// Increase the number of rovers.
		number_of_rovers++;
	}
}

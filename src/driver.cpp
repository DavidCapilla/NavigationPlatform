#include <fstream>
#include "driver.hpp"

using namespace std;

void driver::execute_mission (string filename) {
	try {
		the_receiver.read_signal(filename);
	} catch (string & err) {
		throw string("Something went wrong while getting the signal. ") + err;	
	};
	
	try	{
		initialization();
	} catch (string & err) {
		throw string("Error during the initialization. ") + err;
	}
	
	try	{
		move_rovers();
	} catch (string & err) {
		throw string("Error during the movement of rovers. ") + err;
	}
}

void driver::initialization (void) {
	int rover_index;

	check_number_of_rovers();
	check_platform_size();

	for (rover_index = 0; rover_index < the_receiver.number_of_rovers; rover_index++) {
		check_initial_position_inside_platform(rover_index);
		check_initial_attitude(rover_index);
		check_initial_position_free_of_other_rover(rover_index);
		check_rover_order_correctness(rover_index);

		configure_rover(rover_index);
	}
}

void driver::move_rovers(void) {
	int i, j;
	char step_order;

	for (i = 0; i < the_receiver.number_of_rovers; i++) {
		for (j = 0; j < the_receiver.order[i].length(); j++) {
			step_order = the_receiver.order[i][j];

			if (is_allowed_movement(i, step_order))
				rover_vector[i].run_step(step_order);
			else
				throw string ("Not allowed to perform next move from rover ") + to_string(i+1) +
				string(": Step order ") + string(1, the_receiver.order[i][j]) +
				string(" while rover was at position ") + to_string(rover_vector[i].current_position[0]) +
				string(" ") + to_string(rover_vector[i].current_position[1]) +string(" ") +
				string(1, rover_vector[i].current_heading) +
				string(". Either the rover is going to collide with another rover or it is going to fall out the plateau. ");
		}
	}
}

void driver::check_number_of_rovers(void) {
	if (the_receiver.number_of_rovers < 0)
		throw string("The receiver has read a negative number of rovers. ");
}

void driver::check_platform_size(void) {
	if (the_receiver.platform_size[0] < 0 || the_receiver.platform_size[1] < 0)
		throw string("Invalid reading upper-right coordinates of the plateau. ");
}

void driver::check_initial_position_inside_platform(int rover_index) {
	if (!is_position_inside_platform(the_receiver.initial_position[rover_index]))
		throw string("Invalid reading of the coordinates of rover ") + to_string(rover_index+1) +
		string(". Rover outside the plateau. ");
}

void driver::check_initial_attitude(int rover_index) {
	char heading = the_receiver.attitude[rover_index];
	if (heading != 'N' && heading != 'E' && heading != 'S' && heading != 'W')
		throw string("Invalid reading of the attitude of rover ") + to_string(rover_index+1) + string(". ");

}

void driver::check_initial_position_free_of_other_rover(int rover_index) {
	if(!is_position_free_of_other_rover(rover_index, the_receiver.initial_position[rover_index]))
		throw string("Invalid reading of the position of rover ") + to_string(rover_index+1) +
		      string(". Its position is already busy by other rover. ");
}

void driver::check_rover_order_correctness(int rover_index) {
	int i;
	char step_order;

	for (i = 0; i < the_receiver.order[rover_index].length(); i++) {
		step_order = the_receiver.order[rover_index][i];
		if (step_order != 'M' && step_order != 'R' && step_order != 'L')
			throw string("Invalid reading of the order of rover ") + to_string(rover_index+1) +
			string(". Only allowed step orders: M, R or L. ");
	}
}

void driver::configure_rover(int rover_index) {
	rover rover_i;
	rover_i.current_position = the_receiver.initial_position[rover_index];
	rover_i.current_heading = the_receiver.attitude[rover_index];
	rover_vector.push_back(rover_i);
}

bool driver::is_allowed_movement (int rover_index, char step_order) {
	bool result;
	vector<int> predicted_position;
	
	if (step_order == 'M'){
		predicted_position = predict_position(rover_index, step_order);
		
		if (is_position_inside_platform(predicted_position))
		    result = is_position_free_of_other_rover(rover_index, predicted_position);
		else
			result = false;
	}
	else
		// Rotations are always allowed.
		result = true;

	return result;
}

bool driver::is_position_inside_platform(const vector<int> &position) {
	if(position[0] >= 0 &&
	   position[0] <= the_receiver.platform_size[0] &&
	   position[1] >= 0 &&
	   position[1] <= the_receiver.platform_size[1])
		return true;
	else
		return false;
}

bool driver::is_position_free_of_other_rover(int rover_index, const vector<int> &position) {
	bool result;
	int i;

	result = true;
    for (i = 0; i < rover_vector.size(); i++)
    {
        if (i != rover_index &&
            position[0] == rover_vector[i].current_position[0] &&
		    position[1] == rover_vector[i].current_position[1])
        	// There is another rover in its way!
	        result = false;
    }
    return result;
}

vector<int> driver::predict_position(int rover_index, char step_order) {
	char current_heading = rover_vector[rover_index].current_heading;
	vector<int> predicted_position(rover_vector[rover_index].current_position);

	if (current_heading == 'N')
		predicted_position[1]++;
	else if (current_heading == 'E')
		predicted_position[0]++;
	else if (current_heading == 'S')
		predicted_position[1]--;
	else if (current_heading == 'W')
		predicted_position[0]--;

	return predicted_position;
}

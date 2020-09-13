#include "rover.hpp"

// Empty constructor
rover::rover()
{
    // Intentionally left in blank
}

// Copy constructor
rover::rover(const rover &r) 
{
    current_position.push_back(r.current_position[0]); 
    current_position.push_back(r.current_position[1]); 
    current_heading = r.current_heading;
}

void rover::run_step (char step_order){
	if (step_order == 'M')
		move_forward();
	else if (step_order == 'R')
		turn_right();
	else if (step_order == 'L')
		turn_left();
}

void rover::move_forward(void) {
	// If the step order is to move forward we need to know to which direction move in order to store the position of the rover.
	if (current_heading == 'N')
		current_position[1]++;
	else if (current_heading == 'E')
		current_position[0]++;
	else if (current_heading == 'S')
		current_position[1]--;
	else if (current_heading == 'W')
		current_position[0]--;
}

void rover::turn_right(void) {
	// The position keeps the same.
	if (current_heading == 'N')
		current_heading = 'E';
	else if (current_heading == 'E')
		current_heading = 'S';
	else if (current_heading == 'S')
		current_heading = 'W';
	else if (current_heading == 'W')
		current_heading = 'N';
}

void rover::turn_left(void) {
	// The position keeps the same.
	if (current_heading == 'N')
		current_heading = 'W';
	else if (current_heading == 'E')
		current_heading = 'N';
	else if (current_heading == 'S')
		current_heading = 'E';
	else if (current_heading == 'W')
		current_heading = 'S';
}

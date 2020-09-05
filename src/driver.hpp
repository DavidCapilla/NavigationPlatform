#ifndef DRIVER_HPP_
#define DRIVER_HPP_

#include <vector>
#include <iostream>

#include "receiver.hpp"
#include "rover.hpp"

// This class is the conductor of the mission.
class driver
{
	public:
		// Main method that makes all the necessary movements of the rovers.
		void execute_mission (string filename);

		// This method allows to know if the rover move is to a valid position of the platform (check if it is inside the platform and it is not busy).
		bool is_allowed(int rover_index, char step_order);

		// Initialize the positions of the rovers and check the correctness of the signal.
		void initialization (void);

		// Attributes
		vector<rover> rover_vector;
		receiver the_receiver;
};



#endif /* DRIVER_HPP_ */

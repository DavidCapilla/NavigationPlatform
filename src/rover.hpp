#ifndef ROVER_HPP_
#define ROVER_HPP_

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// This class represents the rovers and have information about itself and how to perform actions.
class rover
{
	public:
	    // Empty constructor
	    rover();
	    // Copy constructor
	    rover(const rover &r);

		// The method that makes the rover perform an action.
		void run_step (char step_order);

		// Attributes
		vector<int> current_position;
		char current_heading;
};



#endif /* ROVER_HPP_ */

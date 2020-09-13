#ifndef DRIVER_HPP_
#define DRIVER_HPP_

#include <vector>
#include <iostream>

#include "receiver.hpp"
#include "rover.hpp"

class driver
{
	public:
		void execute_mission (string filename);

		void initialization (void);
		void move_rovers (void);

		void check_number_of_rovers (void);
		void check_platform_size (void);
		void check_initial_position_inside_platform (int rover_index);
		void check_initial_attitude (int rover_index);
		void check_initial_position_free_of_other_rover (int rover_index);
		void check_rover_order_correctness (int rover_index);

		void configure_rover (int rover_index);

		bool is_allowed_movement(int rover_index, char step_order);
		bool is_position_inside_platform (const vector<int> & position);
		bool is_position_free_of_other_rover (int rover_index, const vector<int> & position);
		vector<int> predict_position (int rover_index, char step_order);


		vector<rover> rover_vector;
		receiver the_receiver;
};



#endif /* DRIVER_HPP_ */

#include "receiver.hpp"

void
receiver::
get_signal
(string filename)
{
	int x, y;
	char att;
	string ord;
	vector<int> i_pos;
	ifstream my_file;
	
	my_file.open(filename);
	
	//
	// We will assume certain correctness in the input file, that is, that the order is correct, and the inputs are the allowed ones in order to reduce scope.
	//
	
	// Get the plateau size
	my_file >> x;
	my_file >> y;
	
	platform_size.push_back(x);
	platform_size.push_back(y);
	

	// Initialize the vector of positions.
	i_pos.resize(2);
	// initialize the number of rovers to 0.
	number_of_rovers = 0;
	while (my_file.good())
	{
		// Get the initial position of the rover
		my_file >> x;
		// This check is in order to know if the reading is finished already.
		if(my_file.eof())
		{
			break;
		}
		my_file >> y;
		i_pos[0] = x;
		i_pos[1] = y;
		initial_position.push_back(i_pos);
		
		// Get the attitude of the rover
		my_file >> att;
		attitude.push_back(att);
		
		// Get the order of the rover
		my_file >> ord;
		order.push_back(ord);
		
		// Increase the number of rovers.
		number_of_rovers++;
	}
	
	my_file.close();
}

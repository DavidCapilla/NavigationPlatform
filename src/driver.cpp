#include <fstream>
#include "driver.hpp"

using namespace std;

void
driver::
initialization
(void)
{
	int i, j;
	int x, y;
	char heading;
	char step_order;
	rover rover_i;
	
	if (the_receiver.number_of_rovers < 0)
	{
		throw string("The receiver has read a negative number of rovers. ");
	}
	
	if (the_receiver.platform_size[0] < 0 || the_receiver.platform_size[1] < 0)
	{
		throw string("Invalid reading upper-right coordinates of the plateau. ");
	}
	
	// Initialize rover vector. We get the information from the receiver.
	rover_i.current_position.resize(2);
	for (i = 0; i < the_receiver.number_of_rovers; i++)
	{
		
		x = the_receiver.initial_position[i][0];
		y = the_receiver.initial_position[i][1] ;
		heading = the_receiver.attitude[i];
		
		// Check that the initial position of the rover is the correct one.
		// First let's check that it is inside the plateau:
		if (x < 0 || x > the_receiver.platform_size[0])
		{
			throw string("Invalid reading of the first coordinate of rover ") + to_string(i+1) + string(". Rover outside the plateau. ");
		}
		if (y < 0 || y > the_receiver.platform_size[1])
		{
			throw string("Invalid reading of the second coordinate of rover ") + to_string(i+1) + string(". Rover outside the plateau. ");
		}
		if (heading != 'N' && heading != 'E' && heading != 'S' && heading != 'W')
		{
			throw string("Invalid reading of the attitude of rover ") + to_string(i+1) + string(". ");
		}
		
		//Before to assign the position let's check that no two rovers are in the same initial position.
		for (j = i-1; j >= 0; j--)
		{
			if ((x == rover_vector[j].current_position[0]) && (y == rover_vector[j].current_position[1]))
			{
				throw string("Invalid reading of the position of rover ") + to_string(i+1) + string(". Its position is already busy by rover ") + to_string(j+1) + string(". ");
			}
		}
		
		// Assign initial positon
		rover_i.current_position[0] = x;
		rover_i.current_position[1] = y;
		rover_i.current_heading = heading;
		rover_vector.push_back(rover_i);
		
		// Check for the correctness of the order, only allowed M, L and R.
		for (j = 0; j < the_receiver.order[i].length(); j++)
		{
			step_order = the_receiver.order[i][j];
			if (step_order != 'M' && step_order != 'R' && step_order != 'L')
			{
				throw string("Invalid reading of the order of rover ") + to_string(i+1) + string(". Only allowed step orders: M, R or L. ");
			}
		}
	}
}

void 
driver::
execute_mission
(string filename)
{
	int i, j;
	char step_order;
	
	try
	{
		the_receiver.get_signal(filename);
	}
	catch (string err)
	{
		// In case error controll of the reading is implemented.
		throw string("Something went wrong while getting the signal. ") + err;	
	};
	
	try
	{
		initialization();
	}
	catch (string err)
	{
		// Error in the correctness of the signal information.
		throw string("Error during the initialization. ") + err;
	}
	
	
	// For each rover perform the corresponding actions.
	for (i = 0; i < the_receiver.number_of_rovers; i++)
	{		
		for (j = 0; j < the_receiver.order[i].length(); j++)
		{
			step_order = the_receiver.order[i][j];
			
			// If the movement is allowed perform it, otherwise stop the mission and throw an error.
			if (is_allowed(i, step_order))
			{
				rover_vector[i].run_step(step_order);
			}
			else
			{
				throw string ("Not allowed to perform next move from rover ") + to_string(i+1)  + string(": Step order ") + string(1, the_receiver.order[i][j]) + string(" while rover was at position ") + 
				to_string(rover_vector[i].current_position[0]) + string(" ") + to_string(rover_vector[i].current_position[1]) +string(" ") +string(1, rover_vector[i].current_heading) + 
				string(". Either the rover is going to collide with another rover or it is going to fall out the plateau. ");
			}
		}
	}
	
}

bool
driver::
is_allowed 
(int rover_index, char step_order)
{
	bool result;
	int i;
	vector<int> predicted_position;
	
	//Let's first predict the end position and attitude.
	if (step_order == 'M')
	{
		predicted_position = rover_vector[rover_index].current_position;
		
		switch (rover_vector[rover_index].current_heading)
		{
			case 'N' : 
			{
				predicted_position[1]++;
				break;
			}		
			case 'E' : 
			{
				predicted_position[0]++;
				break;
			}		
			case 'S' : 
			{
				predicted_position[1]--;
				break;
			}		
			case 'W' : 
			{
				predicted_position[0]--;
				break;
			}					
		}
		
		// Let's check that the rover prediction is inside the plateau.
		if((predicted_position[0] >= 0 && predicted_position[0] <= the_receiver.platform_size[0])
			&& (predicted_position[1] >= 0 && predicted_position[1] <= the_receiver.platform_size[1]))
		{
		    result = true;
			
			// Now let's check that there is no other rover on the way to collide.
		    for (i = 0; i < rover_vector.size(); i++)
		    {
		        if((i != rover_index) && (predicted_position[0] == rover_vector[i].current_position[0])
			       && (predicted_position[1] == rover_vector[i].current_position[1]))
			    {			
					// There is another rover in its way!
			        result = false;
			    }
		    }
			
		}
		else
		{
			// The rover is going to fall outside the plateau.
			result = false;
		}
	}
	else
	{
		// Rotations are always allowed.
		result = true;
	}
	return result;
}

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

void
rover::
run_step
(char step_order)
{
	if (step_order == 'M')
	{
		// If the step order is to move forward we need to know to which direction move in order to store the position of the rover.
		switch (current_heading)
		{
			case 'N' : 
			{
				current_position[1]++;
				break;
			}		
			case 'E' : 
			{
				current_position[0]++;
				break;
			}		
			case 'S' : 
			{
				current_position[1]--;
				break;
			}		
			case 'W' : 
			{
				current_position[0]--;
				break;
			}					
		}
		
	}
	else
	{
		// In case of rotation to one or other side the heading will vary whereas the position keeps the same.
		if (step_order == 'R')
		{
			switch (current_heading)
			{
				case 'N' : 
				{
					current_heading = 'E';
					break;
				}		
				case 'E' : 
				{
					current_heading = 'S';
					break;
				}		
				case 'S' : 
				{
					current_heading = 'W';
					break;
				}		
				case 'W' : 
				{
					current_heading = 'N';
					break;
				}					
			}
		}
		
		if (step_order == 'L')
		{
			switch (current_heading)
			{
				case 'N' : 
				{
					current_heading = 'W';
					break;
				}		
				case 'E' : 
				{
					current_heading = 'N';
					break;
				}		
				case 'S' : 
				{
					current_heading = 'E';
					break;
				}		
				case 'W' : 
				{
					current_heading = 'S';
					break;
				}					
			}
		}
	}
	
}

/*
void
rover::
 operator=
 (const rover &r ) 
 { 
        current_position = r.current_position;
        current_heading = r.current_heading;
  }
*/

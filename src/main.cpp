#include <iostream>
#include <fstream> 
#include <vector>
#include "driver.hpp"


int
main
(int argc, char *argv[])
{
	//
	// Variables
	//
	int i;
	// The output file.
	ofstream output_file;
	// Intance the driver object.
	driver the_driver;
	
	//
	// Main
	//
	
	if (argc != 3)
	{
		cout << "Usage: ./NavigationPlatform full_path_to_signal full_path_to_output" << endl;
		return 0;
	}

	// We will produce an output of the mission in the file "mission_report.txt".
	output_file.open(argv[2]);
		
	// We will assume that the information necessary for the mission is in a file name "signal.txt" and that is located in the same directory that the executable.
	try
	{
		// Execution of the mission via the driver.
		the_driver.execute_mission(argv[1]);
		
		cout << "The mission was successful, the mission report can be found at " << argv[2] << "." << endl;
		
		// Reporting of the mission.
		output_file << "Successful mission!" << endl; 
		output_file << "Number of rovers: " << the_driver.the_receiver.number_of_rovers << endl;
		for(i = 0; i < the_driver.the_receiver.number_of_rovers; i++)
		{
			output_file << "Final location of rover " << i + 1 << ": " << the_driver.rover_vector[i].current_position[0] << " " << the_driver.rover_vector[i].current_position[1] << " " 
							<< the_driver.rover_vector[i].current_heading << endl;			
		}
	}
	catch(string err)
	{
		// Some error occurred, reporting of the error.
		cout << "Something went wrong during the mission, review the mission_report.txt at this same directory to find out why." << endl;
		
		output_file << "The mission stopped while trying to figure out what is wrong. The current status, that might be wrong or incomplete, is:" << endl;
		output_file << err << endl;
		output_file << "Number of rovers: " << the_driver.the_receiver.number_of_rovers << endl;
		
		
		for(i = 0; i < the_driver.rover_vector.size(); i++)
		{
			if(the_driver.rover_vector[i].current_position.size() == 2)
			{
				output_file << "Current location of rover " << i + 1 << ": " << the_driver.rover_vector[i].current_position[0] << " " << the_driver.rover_vector[i].current_position[1] << " " 
								<< the_driver.rover_vector[i].current_heading << endl;			
			}
		}
	}
	
	output_file.close();
	
	return 0;
}

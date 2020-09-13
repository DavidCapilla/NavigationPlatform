#include <iostream>
#include <fstream> 
#include <vector>
#include "driver.hpp"


int main (int argc, char *argv[]) {
	int i;
	ofstream report_file;
	driver the_driver;

	if (argc != 3) {
		cout << "Usage: ./NavigationPlatform full_path_to_signal full_path_to_output" << endl;
		return 0;
	}

	// We will produce an output of the mission in the selected file.
	report_file.open(argv[2]);
		
	try {
		the_driver.execute_mission(argv[1]);
		
		cout << "The mission was successful, the mission report can be found at " << argv[2] << "." << endl;
		
		// Reporting of the mission.
		report_file << "Successful mission!" << endl; 
		report_file << "Number of rovers: " << the_driver.the_receiver.number_of_rovers << endl;
		for(i = 0; i < the_driver.the_receiver.number_of_rovers; i++) {
			report_file << "Final location of rover " << i + 1 << ": " <<
					the_driver.rover_vector[i].current_position[0] << " " <<
					the_driver.rover_vector[i].current_position[1] << " " <<
					the_driver.rover_vector[i].current_heading << endl;
		}
	} catch(string & err) {
		// Some error occurred, reporting of the error.
		cout << "Something went wrong during the mission, review the file " << argv[2] << endl;
		
		report_file << "The mission stopped while trying to figure out what is wrong. "
						"The current status, that might be wrong or incomplete, is:" << endl;
		report_file << err << endl;
		report_file << "Number of rovers: " << the_driver.the_receiver.number_of_rovers << endl;
		
		for(i = 0; i < the_driver.rover_vector.size(); i++) {
			if(the_driver.rover_vector[i].current_position.size() == 2) {
				report_file << "Current location of rover " << i + 1 << ": " <<
								the_driver.rover_vector[i].current_position[0] << " " <<
								the_driver.rover_vector[i].current_position[1] << " " <<
								the_driver.rover_vector[i].current_heading << endl;
			}
		}
	}
	
	report_file.close();
	
	return 0;
}

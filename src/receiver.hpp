#ifndef RECEIVER_HPP_
#define RECEIVER_HPP_

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// This class is in charge of read the mission information and stores it.
class receiver
{
	public:
		receiver (void);

		// Read and store the mission information. No correctness of the file is checked,
	    // it is assumed that the order of the inputs are the correct ones and
		// that the data type is also correct.
		void read_signal(string signal_filename);
		void retrieve_platform_size_from_signal (void);
		void retrieve_rovers_initial_information_from_signal (void);

		// Attributes.
		vector<int> platform_size;
		int number_of_rovers;
		vector<vector<int>> initial_position;
		vector<char> attitude;
		vector<string> order;

	private:
		ifstream signal;
};


#endif /* RECEIVER_HPP_ */

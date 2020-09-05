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
		// Read and store the mission information. No correctness of the file is checked, it is assumed that the order of the inputs are the correct ones and
		// that the data type is also correct.
		void get_signal(string filename);

		// Attributes.
		vector<int> platform_size;
		int number_of_rovers;
		vector<vector<int>> initial_position;
		vector<char> attitude;
		vector<string> order;
};


#endif /* RECEIVER_HPP_ */

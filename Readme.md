# Problem

Whith this program we try to navigate serveral rovers in a grid platform. Each of the rovers position is represented with cartesian coordinates (x,y) and a letter representing 4 possible orientations (N: North, E: East, S: South, W: West). It is assumed that the North direction is in the direction of positive y.

It is assumed that each of the rovers is navigated with a string of characters. The valid characters and its meaning is the following:
  - L: Turn 90 degrees left.
  - R: Turn 90 degrees right.
  - M: Move forward one unit in the grid whithout change its heading. 

## Input
The input of the problem is defined as follows:
  - The first line of input correspond to the the upper-right coordinates of the platform, the lower-left coordinates are assumed to be 0 0.
  - The remaining data of the input file correspond to the information of each of the rovers. Each rover has two lines of input. The first line gives the rover’s position, and the second line is the navigation information, that is, the string of characters.

Example of input file:

5 5
1 2 N
LMLMLMLMM
3 3 E
MMRMMRMRRM 

The platform is a 5x5 grid.
The first rover starts at (1,2) heading North.
Their instructions are to turn left, move forward, turn left, move forward, turn left, move forward, turn left, move forward and move forward.
The second rover starts at (3,3) heading East.
Their instructions are to move forward twice, turn right, move forward twice, turn right, move forward, turn right twice and move forward. 

## Output
The output is expected to containg the final position and orientation of each one of the rovers.

A simple example corresponding to the input example would be:
1 3 N
5 1 E


## Assumptions
Each rover will perform its navigation orders sequentially, which means that the second rover won’t start to move until the first one has finished moving. 
There can't be two rovers at the same location at any moment.


# Program

## Content
 - This readme file
 - data folder:
   + signal.txt
   + test_signal_1.txt
   + test_signal_2.txt
   + test_signal_3.txt
   + test_signal_4.txt
   + test_signal_5.txt
   + test_signal_6.txt
   + test_signal_7.txt
   + test_signal_8.txt
 - project folder
 - src folder:
   + receiver.hpp
   + reveicer.cpp
   + rover.hpp
   + rover.cpp
   + driver.hpp
   + driver.cpp
   + main.cpp
	

The source code can be found at the src folder and is divided in 7 files, 3 of them containing a class declaration each one, other 3 containing the definition of the classes and another file with the main of the program. Each of the classes are thought to be in charge of its own task:
 - receiver.hpp, receiver.cpp: Contains the receiver class. This class is in charge of reading the mission information from the file signal.txt and storing it.
 - rover.hpp, rover.cpp: Contains the rover class. This class represents each of the rovers and has information about the rover and how to perform actions.
 - driver.hpp, driver.cpp: Contains the driver class. This class is the conductor of the mission, interacts with te receiver to get the information about the mission and with the rovers to execute the orders. It also manages possible problems during the mission and stops it if necessary.
 - main.cpp: Main, calls the driver and creates the output.

## Assumptions
 - The input file exist and does not contain errors such as invalid order of statements, incorrect data types, partial information, etc, in order to reduce the scope of this project. That is, the receiver class will throw no errors in this version.
 - When an error arises, the mission stops.
 - The output is written in the mission_report.txt file which is created at the same location as the executable.

## Further work
 - We have considered all the methods and attributes of the classes as public. In a next version we would protect the attributes and implement setters and getters in order to gain control over modifications.
 - We have abused of accessing atributes resulting in commands such object.attribute.other, which may lead to confusion. This would be changed using local variables in order to make the code more readable.
 - Implement error management in the reading of the input file.

## Error checking
There have been created serveral files in order to validate the error management. This input files are named test_singal_i.txt and contain the following validations:

	1- Invalid platform values.
	2- No rovers.
	3- Initial position of rover outside the plateau.
	4- Initial position of rover in a busy location.
	5- Invalid initial heading.
	6- Invalid step order.
	7- Movement outside the platform.
	8- Collision.

## How to
### Compile program: 
   + Using the eclipse project located on the project folder,
   + Compiling manually using the following commands:
       g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"driver.d" -MT"driver.o" -o "driver.o" "/path/to/src/driver.cpp"
       g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"main.d" -MT"main.o" -o "main.o" "/path/to/src/main.cpp"
       g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"receiver.d" -MT"receiver.o" -o "receiver.o" "/path/to/src/receiver.cpp"
       g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"rover.d" -MT"rover.o" -o "rover.o" "/path/to/src/rover.cpp"
       g++  -o "NavigationPlatform"  ./driver.o ./main.o ./receiver.o ./rover.o   
     where /path/to/src/ is your local path to the src folder.
### Execute program: Execute the resulting application as follows:
     ./NavigationPlatform full_path_to_signal full_path_to_output
   where the the full_path_to_* is the actual full path to the files. Example: ./NavigationPlatform /home/David/NavigationPlatform/data/signal.txt /home/David/NavigationPlatform/output/report.txt


#include "InputParser.h"
#include "globaldef.h"
#include <iostream>

// Standard Values for Number of Points
int NUMBEROFPOINTS = 40;

bool StepbyStep = true;

// shows how to use command inputs
void show_usage(char *argv)
{
	std::cerr << "Usage: " << argv << " <option(s)> "
		<< "Options:\n"
		<< "\t--help\t\tShow this help message\n"
		<< "\t--stepbystep \t\t stepper function for drawing\n"
		<< "\t--points \t\tSpecify the number of points\n"
		<< std::endl;
}

// check command line inputs and set global values 
int checkInputs(int argc, char *argv[])
{
	if (argc < 1)
	{
		show_usage(argv[0]);
		return 0;
	}

	// Input Handling
	for (int i = 1; i < argc; ++i) {
		std::string arg = argv[i];
		if (arg == "--help") {
			show_usage(argv[0]);
			return 0;
		}
		else if (arg == "--stepbystep") {
			if (i + 1 < argc) {
				int step = atoi(argv[i + 1]);
				StepbyStep = (step == 0) ? false : true;
			}
			else{
				return 0;
			}
		}
		else if (arg == "--points") {
			if (i + 1 < argc){
				NUMBEROFPOINTS = atoi(argv[i + 1]);
			}
			else{
				return 0;
			}
		}
	}
	return 1;
}
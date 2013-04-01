
#include <iostream>
#include "CommandLineProcessor.h"

/**
  * Entry Point of the MIV Console
  */
int main() {
	int result = 0;
	bool loop_again = true;
	CommandLineProcessor commandLineProcessor;
	std::string sCommandLine;
	while (loop_again) {
		std::cout  << std::endl << ">";
		std::cin >> sCommandLine;
		loop_again = commandLineProcessor.execute(sCommandLine);
	}
	return result;
}

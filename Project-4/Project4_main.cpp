#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

int main(int argc, char** argv)
{
	//first input argument is always the program name...
	char* fileName = argv[1];
	
	//open the file
	std::ifstream fin(fileName);
	
	if(!fin)
	{
		std::cout<< "File not found" << std::endl;
		return EXIT_FAILURE;
	}
	
	std::string line;
	while(std::getline(fin,line))
	{
		//this is just to get you going.  You'll need to do much more here...
		std::cout << line << std::endl;
	}
	
	return EXIT_SUCCESS;
}

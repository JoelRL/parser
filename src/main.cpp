#include "operations.h"

std::vector<std::string> commands;

std::vector<std::string> world_variablesNames;
std::vector<int> world_variablesValues;

void initilizeCommands(std::vector<std::string> *cmdT);

int count_characters(char c,std::string s);

bool debug = false;

int main(int argc, char* argv[])
{
	
	// clear screen
	system("cls");
	
	// print welcome message
	std::cout << "Welcome to Parser v1. Please type file path" << std::endl << std::endl << "/";
	
	// char to store filepath
	char filePath[256];
	
	// recieve input of filepath
	std::cin.get(filePath,256);
	
	// bool value to check if file exists or not
	bool isFile;
	
	// attempt to open file
	std::ifstream infile(filePath);
	
	// check if file exists
	isFile = infile.good();
	
	// if file doesnt exist terminate program, if it does continue on
	if (!isFile) 
	{
		std::cout << "File does not exist. Quitting program because looping back is too hard." << std::endl;
		
		system("pause");
		
		return 0;
	}
	
	// create a new file
	std::ifstream file;
	
	// open the file in the filepath
	file.open(filePath,std::ifstream::in);
	
	if (debug)
	{
		std::cout << std::endl << "File loaded!" << std::endl << std::endl;
	}
	
	// get size of file
	file.seekg (0, file.end);
    int length = file.tellg();
    file.seekg (0, file.beg);
	
	// vector to store each line of file
	std::vector <std::string> fileLines;
	
	// while loop to fetch file lines
	while(file)
	{
		std::string line;
		
		getline(file, line);
		
		if (line != "" && line[0] != '#')
		{
			fileLines.push_back(line);
		}
	}
	
	// we are done with the file, close it
	file.close();
	
	if (debug)
	{
		std::cout << "Contents:" << std::endl;
		
		for (int i=0; i < fileLines.size(); i++)
		{
			std::cout << "'" << fileLines[i] << "'" << std::endl;
		}
	}
	
	// initilize interpreter commands
	initilizeCommands(&commands);
	
	// vector to store file operations
	std::vector<std::string> operations;
	
	// fetch file operations to execute
	for (int k=0; k < fileLines.size(); k++)
	{
		operations.push_back(getFileOperations(fileLines[k],commands,length));
	}
	
	if (debug)
	{
		std::cout << std::endl << "Operations:" << std::endl;
		
		if (debug)
		{
			for (int i=0; i < operations.size(); i++)
			{
				std::cout << "#" << i << ": " << operations[i] << std::endl;
			}
		}
	}
	
	// print start program message
	std::cout << std::endl << "-- Start program--" << std::endl << std::endl;
	
	for (int i=0; i < operations.size(); i++)
	{
		if (executeOperations(operations[i],&world_variablesNames,&world_variablesValues,length) == 1)
		{
			std::cout << std::endl << std::endl << "--Ended program successfully!--";
			break;
		}
	}
	
	// execute operations. if it returns a 1, it ended properly, if anything else, something went wrong
	
	
	if (debug)
	{
		// list variables used
		std::cout << std::endl << std::endl << "Variables:" << std::endl;
		
		for (int i=0; i < world_variablesNames.size(); i++)
		{
			std::cout << "Name: '" << world_variablesNames[i] << "' Var: " << world_variablesValues[i] << std::endl;
		}
	}
	
	std::cout << std::endl;
	std::cout << std::endl;
	
	system("pause");
	
	return 0;
}

void initilizeCommands(std::vector<std::string> *cmdT)
{
	cmdT->push_back("if");
	cmdT->push_back("print");
	cmdT->push_back("input");
	cmdT->push_back("int");
	cmdT->push_back("set");
	cmdT->push_back("add");
	cmdT->push_back("exit");
}

int count_characters(char c, std::string s)
{
	int count = 0;
	
	for (int i=0; i < s.size(); i++)
		if (s[i] == c) count++;
	
	return count;
}
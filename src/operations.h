#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <typeinfo>

std::string getFileOperations(std::string fileLine, std::vector<std::string> commands, int sizeOfFile, std::vector<std::string> fileLines);
	//getFileOperations - Fetches file operations and adds them in a vector (*list)
	//@param fileLine - Line to be processed
	//@param commands - Vector full of acceptable commands the interpreter recognizes
	//@param sizeOfFile - The size of the file we are reading
	//@return - string with bare bones code of operation
	
int executeOperations(std::string op, std::vector<std::string>* varsN, std::vector<int>* varsV, int sizeOfFile);
	//executeOperations - Executes operation
	//@param op - Bare bones string of operation
	//@param varsN - Pointer of vector list where world_variables identifier names are stored
	//@param varsV - Pointer of vector list where world_variables data are stored
	//@param sizeOfFile - The size of the file we are reading
	//@return - A 1 if program has exited, and anything else if it continues

void print(std::string op, std::vector<std::string>* varsN, std::vector<int>* varsV);
	//print - Executes "print" operation
	//@param op - Bare bones string of operation
	//@param varsN - Pointer of vector list where world_variables identifier names are stored
	//@param varsV - Pointer of vector list where world_variables data are stored

void integerCreation(std::string op, std::vector<std::string>* varsN, std::vector<int>* varsV, int sizeOfFile);
	//integerCreation - Creates an integer and adds it to the world_variables
	//@param op - Vector list of operations
	//@param i - Number that points where the operation is in the vector (op)
	//@param varsN - Pointer of vector list where world_variables identifier names are stored
	//@param varsV - Pointer of vector list where world_variables data are stored
	//@param sizeOfFile - The size of the file we are reading

extern const std::string compareCommands[4]; // List of compare commands for IF statments

#endif
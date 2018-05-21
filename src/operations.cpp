#include "operations.h"

const std::string compareCommands[4] = {"==","<",">","~="};

std::string getFileOperations(std::string fileLine, std::vector<std::string> commands, int sizeOfFile)
{
	
	std::string returnCommand;
	
	for (int i=0; i < commands.size(); i++)
	{
		std::size_t found = fileLine.find(commands[i]);
		
		if (found < sizeOfFile)
		{
			if (commands[i] == "print")
			{
				std::size_t s1 = fileLine.find("(");
				
				if (s1 < sizeOfFile)
				{
					std::size_t s2 = fileLine.find(")");
					
					if (s2 < sizeOfFile)
					{
						
						std::string parameter;
						
						std::string q;
						
						if (fileLine.find("\"") < sizeOfFile)
						{
							parameter = fileLine.substr(s1+2,s2-8);
							q = "1";
						}
						else
						{
							parameter = fileLine.substr(s1+1,s2-6);
							q = "0";
						}
						
						std::string finalCommand = commands[i] + parameter + q;
						
						returnCommand = finalCommand;
						
						break;
					}
					else
					{
						break;
					}
				}
				else
				{
					break;
				}
			}
			else if(commands[i] == "input")
			{
				std::size_t s1 = fileLine.find("(");
				
				if (s1 < sizeOfFile)
				{
					std::size_t s2 = fileLine.find(")");
					
					if (s2 < sizeOfFile)
					{
						
						std::string parameter;
						
						parameter = fileLine.substr(s1+1,s2-6);
						
						returnCommand = commands[i] + parameter;
						
						break;
					}
				}
			}
			else if(commands[i] == "exit")
			{
				returnCommand = "exit";
				break;
			}
			else if(commands[i] == "int" || commands[i] == "add" || commands[i] == "set")
			{
				std::size_t s1 = fileLine.find("(");
				
				if (s1 < sizeOfFile)
				{
					std::size_t s2 = fileLine.find(")");
					
					if (s2 < sizeOfFile)
					{
						
						std::string parameter = fileLine.substr(s1+1,s2-4);
						
						std::string finalCommand = commands[i] + parameter;
						
						returnCommand = finalCommand;
						
						break;
					}
				}
			}
			else if(commands[i] == "if")
			{
				std::size_t s1 = fileLine.find("(");
				
				int comp;
				
				int compPlace;
				
				std::string parameter;
				
				if (s1 < sizeOfFile)
				{
					std::size_t s2 = fileLine.find(")");
					
					if (s2 < sizeOfFile)
					{
						parameter = fileLine.substr(s1+1,s2-4);
						
						for (int j = 0; j < (sizeof(compareCommands)/sizeof(*compareCommands)); j++)
						{
							
							int num = parameter.find(compareCommands[j]);
							
							if (parameter.find(compareCommands[j]) < sizeOfFile)
							{
								comp = j;
								
								compPlace = num;
							}
						}
					}
				}
				
				std::string v1;
				
				for (int j = 0; j < compPlace; j++)
				{
					if (parameter.at(j) != ' ')
					{
						v1 += parameter.at(j);
					}
				}
				
				std::string v2;
				
				int point1;
				
				if (comp == 0 || comp == 3)
				{
					point1 = compPlace + 2;
				}
				else if(comp == 1 || comp == 2)
				{
					point1 = compPlace + 1;
				}
				
				int max = parameter.size();
				
				for (int j = point1; j < max; j++)
				{
					if (parameter.at(j) != ' ')
					{
						v2 += parameter.at(j);
					}
				}
				
				std::string compS = std::to_string(comp);
				
				std::size_t semi = fileLine.find(":");
				
				std::string action;
				
				if (semi < sizeOfFile)
				{
					
					std::string lastBit = fileLine.substr(semi,fileLine.size());
					
					std::size_t good = lastBit.find("(");
					
					std::size_t max = lastBit.find(")") + 1;
					
					for (int j = 0; j < max; j++)
					{
						if (j < good)
						{
							if (lastBit.at(j) != ' ' && lastBit.at(j) != ':' && lastBit.at(j) != ';')
							{
								action += lastBit.at(j);
							}
						}
						else
						{
							if (lastBit.at(j) != ';')
							{
								action += lastBit.at(j);
							}
						}
					}
				}
				
				std::string outputCommand = getFileOperations(action,commands,sizeOfFile);
				
				std::string finalCommand = commands[i] + v1 + "(" + compS + ")" + v2 + ":" + outputCommand;
				
				returnCommand = finalCommand;
				
				break;
			}
		}
	}
	
	return returnCommand;
}

int executeOperations(std::string op, std::vector<std::string>* varsN, std::vector<int>* varsV, int sizeOfFile)
{
	if (op.substr(0,5) == "print")
	{
		print(op, varsN, varsV);
	}
	if (op.substr(0,5) == "input")
	{
		int num;
		
		std::string varName = op.substr(5,op.size());
		
		std::cin >> num;
		
		std::string setNum = std::to_string(num);
		
		std::string setCommand = "set" + varName + "," + setNum;
		
		executeOperations(setCommand,varsN,varsV,sizeOfFile);
	}
	else if (op.substr(0,3) == "int")
	{
		integerCreation(op, varsN, varsV, sizeOfFile);
	}
	else if (op.substr(0,3) == "add" || op.substr(0,3) == "set")
	{
		std::size_t comma = op.find(",");
		
		if (comma < sizeOfFile)
		{	
			std::string var = op.substr(3,comma-3);
			
			std::string num = op.substr(comma+1,op.size());
			
			int varN = atoi(num.c_str());
			
			int id = 0;
			
			int max = varsN->size();
			
			for (int k=0; k < max; k++)
			{
				if ((*varsN).at(k) == var)
				{
					id = k;
				}
			}
			
			if (op.substr(0,3) == "add")
			{
				(*varsV).at(id) += varN;
			}
			else if (op.substr(0,3) == "set")
			{
				(*varsV).at(id) = varN;
			}
		}
	}
	else if (op.substr(0,2) == "if")
	{
		
		std::size_t paran1 = op.find("(");
		
		std::string v1 = op.substr(2,paran1-2);
		
		std::size_t paran2 = op.find(")");
		
		std::string compS = op.substr(paran1+1,paran2-1-paran1);
		
		int comp = atoi(compS.c_str());
		
		std::size_t semi = op.find(":");
		
		std::string v2 = op.substr(paran2+1,semi-(paran2+1));
		
		for (int p = 0; p < 2; p++)
		{
			int id = -1;
			
			int max = varsN->size();
			
			std::string var;
			
			if (p==0)
			{
				var = v1;
			}
			else
			{
				var = v2;
			}
			
			for (int k=0; k < max; k++)
			{
				if ((*varsN).at(k) == var)
				{
					id = k;
				}
			}
			
			if (id != -1)
			{
				if (p==0)
				{
					v1 = std::to_string((*varsV).at(id));
				}
				else
				{
					v2 = std::to_string((*varsV).at(id));
				}
			}
		}
		
		std::string action = op.substr(semi+1,op.size()-(semi+1));
		
		int var1 = atoi(v1.c_str());
		
		int var2 = atoi(v2.c_str());
		
		if (comp == 0)
		{
			if (var1 == var2)
			{
				executeOperations(action,varsN,varsV,sizeOfFile);
			}
		}
		else if(comp == 1)
		{
			if (var1 < var2)
			{
				executeOperations(action,varsN,varsV,sizeOfFile);
			}
		}
		else if(comp == 2)
		{
			if (var1 > var2)
			{
				executeOperations(action,varsN,varsV,sizeOfFile);
			}
		}
		else if(comp == 3)
		{
			if (var1 != var2)
			{
				executeOperations(action,varsN,varsV,sizeOfFile);
			}
		}
	}
	else if (op.substr(0,4) == "exit")
	{
		return 1;
	}
	return 0;
}

// OPERATION FUNCTIONS //

void print(std::string op, std::vector<std::string>* varsN, std::vector<int>* varsV)
{
	if (op.substr(5,op.size()-6) == ":nl")
	{
		std::cout << std::endl;
	}
	else
	{	
		if (op.at(op.size()-1) == '1')
		{
			std::cout << op.substr(5,op.size()-6);
		}
		else
		{
			std::string var = op.substr(5,op.size()-6);
			
			int id = 0;
			
			int max = varsN->size();
			
			for (int k=0; k < max; k++)
			{
				if ((*varsN).at(k) == var)
				{
					id = k;
				}
			}
			
			std::cout << (*varsV).at(id);
		}
	}
}

void integerCreation(std::string op, std::vector<std::string>* varsN, std::vector<int>* varsV, int sizeOfFile)
{
	std::size_t comma = op.find(",");
	
	if (comma < sizeOfFile)
	{
		
		std::string var = op.substr(3,comma-3);
		std::string num = op.substr(comma+1,op.size());
		
		int varN = atoi(num.c_str());
		
		varsN->push_back(var);
		varsV->push_back(varN);
	}
	else
	{
		
		std::string var = op.substr(3,op.size());
		
		varsN->push_back(var);
		varsV->push_back(0);
	}
}
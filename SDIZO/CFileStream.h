#pragma once
#include <iostream>
#include <fstream>
#include <string>

class CFileStream
{
public:
	~CFileStream();
	void openFile();
	int* readData(int* array, int & size);
	void write(int* array, int size);
	

private:
	std::ifstream fileRead;
	std::ofstream fileWrite;
	std::string filename;
};

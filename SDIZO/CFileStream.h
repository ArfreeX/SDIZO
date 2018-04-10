#pragma once
#include <iostream>
#include <fstream>
#include <string>

class CFileStream
{
public:
	CFileStream();
	void openFile();
	void readData();
	void write();
	void showArray();
	~CFileStream();

private:
	std::ifstream fileRead;
	std::ofstream fileWrite;
	std::string filename;
	int *array, size;
};

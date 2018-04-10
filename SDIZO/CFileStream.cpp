#include "stdafx.h"
#include "CFileStream.h"


CFileStream::CFileStream()
{
}

void CFileStream::openFile()
{
	do
	{
		std::cin >> filename;
		fileRead.open(filename, std::ios::in);

		if (fileRead.good() == true)
			std::cout << "Done, you can now read the data\n";
		else
			std::cout << "File not found, try again or type ""exit"" to leave\n";
	} while (fileRead.good() != true && filename != "exit");
}

void CFileStream::readData()
{
	int val;

	if (fileRead.is_open())
	{
		fileRead >> size;
		if (fileRead.fail())
			std::cout << "File error - READ SIZE" << std::endl;
		else
			array = new int[size];
		for (int i = 0; i < size; i++)
		{
			fileRead >> val;
			if (fileRead.fail())
			{
				std::cout << "File error - READ DATA" << std::endl;
				break;
			}
			else
				array[i] = val;
		}
		fileRead.close();
	}
	else
		std::cout << "File error - OPEN" << std::endl;

}

void CFileStream::write()
{
	std::cin >> filename;
	fileWrite.open(filename, std::ios::out | std::ios::app);
	for (int i = 0; i < size; i++)
	{
		fileWrite << array[i] << std::endl;
	}
}

void CFileStream::showArray()
{
	for (int i = 0; i < size; i++)
	{
		std::cout << array[i] << std::endl;
	}
}

CFileStream::~CFileStream()
{
	delete[] array;
	fileRead.close();
	fileWrite.close();
}

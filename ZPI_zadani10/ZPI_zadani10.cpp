// ZPI_zadani10.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <string>

using namespace std;

class Compute
{
public:
	Compute() {};
	Compute(const char* filename) :filename(filename)
	{
		data = new vector<string>;
		data->reserve(100);
		string temp = "";
		string result = "";
	}
	~Compute()
	{
		delete data;
	}
	void GiveResult();

private:
	vector<string> *data;
	string temp;
	string result;
	const char* filename;

	void fileread(const char* filename, vector<string> * data);
	string add(string a, string b);
	void WriteResult();
};


int _tmain(int argc, _TCHAR* argv[])
{
	Compute *compute = new Compute("Zad10.txt");
	compute->GiveResult();
	std::cin.get();
	return 0;
}

/*
function fileread is used to read data from file,
evry line from file is save in different string in vector data
for egzample:
fileread("Zad10.txt", &data);
should return nothing, but it temp_resultill save data from file in vector data
"123
456"
temp_resultill be saved as :
data[0] = "123"
data[1] = "456";
*/
void Compute::fileread(const char* filename, vector<string>  *data)
{
	FILE* file;
	fopen_s(&file, filename, "r");
	if (!file){
		perror("File opening failed");
	}

	char sign; // note: int, not char, required to handle EOF
	string temp = "";
	while ((sign = fgetc(file)) != EOF) { // standard C I/O file reading loop
		if ((sign != 10))
		{
			temp += sign;
		}
		else
		{
			data->push_back(temp);
			temp = "";
		}
	}
	data->push_back(temp);

	if (ferror(file))
	{
		cout << endl;
		cout << "I/O error temp_resulthen reading" << endl;
	}
	else if (feof(file))
	{

	}
	fclose(file);
}

/*
function add is used to adding number given as string data and return result as string
for egzample:
add("1", "2") temp_resultill return "3";
add("19", "23") temp_resultill return "42";
*/
string Compute::add(string a, string b)
{
	int comp_a = a.length() - 1;
	int comp_b = b.length() - 1;
	string result = "";

	int overflow = 0;

	while (comp_a >= 0 || comp_b >= 0)
	{
		int ca, cb, temp_result;

		if (comp_a >= 0) ca = a[comp_a] - 48; else ca = 0;
		if (comp_b >= 0) cb = b[comp_b] - 48; else cb = 0;

		temp_result = ca + cb + overflow;

		result = "0" + result;
		result[0] = 48 + temp_result % 10;

		overflow = temp_result / 10;

		comp_a--; comp_b--;
	}

	if (overflow) result = "1" + result;

	return result;
}


void Compute::WriteResult()
{
	result = temp.substr(0, 10);
	cout << "WYNIK: ";
	cout << result;
}

void Compute::GiveResult()
{
	fileread(filename, data);
	for each (string str in *data)
	{
		temp = add(temp, str);
	}
	WriteResult();
}

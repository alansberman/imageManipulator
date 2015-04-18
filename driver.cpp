//driver.cpp
// Author: Alan Berman
// 13/04/2015

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "Image.h"
//Driver that performs a variety of operations on two PNG image files
using namespace std;
int main(int argc, char * argv[])
{
	string file_one,file_two;
	//String used to parse args
	string s;
	int thresh_int;
	for (int i=2;i<argc;i++)
	{
		//Identify the option chosen
		s = string(argv[i]);
		
		if 	(s=="-a")
		{
			i++;
			//Extract the first file name from the args
			file_one=string(argv[i]);
			i++;
			//Extract the second file name from the args
			file_two=string(argv[i]);
			//add
			break;
		}
		if (s=="-s")
		{
			i++;
			//Extract the first file name from the args
			file_one=string(argv[i]);
			i++;
			//Extract the second file name from the args
			file_two=string(argv[i]);
			//subtract
			break;
		}
		if (s=="-i")
		{
			i++;
			//Extract the singular file name from the args
			file_one=string(argv[i]);
			//invert
			break;
		}
		if (s=="-l")
		{
			i++;
			//Extract the first file name from the args
			file_one=string(argv[i]);
			i++;
			//Extract the second file name from the args
			file_two=string(argv[i]);
			//mask
			break;
		}
		if (s=="-t")
		{
			i++;
			//Extract the singular file name from the args
			file_one=string(argv[i]);
			i++;
			string thresh = string(argv[i]);
			thresh_int= = atoi(thresh.c_str());
			//threshold
			break;
		}
		
	}	
	return 0;
}	

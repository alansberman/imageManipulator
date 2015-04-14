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
		}
		if (s=="-i")
		{
			i++;
			//Extract the first file name from the args
			file_one=string(argv[i]);
			
		}
		
	}	
	return 0;
}	

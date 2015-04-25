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
	for (int i=1;i<argc;i++)
	{
		//Identify the option chosen
		s = string(argv[i]);
		cout << "loop start\n";
		if 	(s=="-a")
		{
			i++;
			//Extract the first file name from the args
			file_one=string(argv[i]);
			i++;
			//Extract the second file name from the args
			file_two=string(argv[i]);
			//add
			string a = "hello.pgm";
			BRMALA003::Image addImage(file_one);
			addImage.addImages(file_one, file_two,a);
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
			BRMALA003::Image subImage(file_one);
			subImage.subtractImages(file_one, file_two);
			break;
		}
		if (s=="-i")
		{
			i++;
			//Extract the singular file name from the args
			file_one=string(argv[i]);
			//invert
			BRMALA003::Image inverted_img(file_one);
			inverted_img.invertImage(file_one);
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
			BRMALA003::Image mask(file_one);
			mask.maskImage(file_one,file_two);
			break;
		}
		if (s=="-t")
		{
			i++;
			//Extract the singular file name from the args
			file_one=string(argv[i]);
			i++;
			string thresh = string(argv[i]);
			thresh_int=  atoi(thresh.c_str());
			//threshold
			BRMALA003::Image threshImg(file_one);
			threshImg.threshImage(file_one, thresh_int);
			break;
		}
		
	}
	
	return 0;
}	

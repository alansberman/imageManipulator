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
	string file_one,file_two, outFile;
	//String used to parse args
	string s;
	int thresh_int;
	for (int i=1;i<argc;i++)
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
			i++;
			//Extract the output file name from the args
			outFile=string(argv[i]);
			//add
			cout << "Adding " << file_one << " to " << file_two << "..." << endl;
			cout <<"Placing the result in " << outFile << "..." << endl;
			BRMALA003::Image originalImage(file_one);
			BRMALA003::Image imageToAdd(file_two);
			originalImage + move(imageToAdd);
			originalImage.saveImage(outFile);
			cout << "Done!" << endl;
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
			i++;
			//Extract the output file name from the args
			outFile=string(argv[i]);
			//subtract
			cout << "Subtracting " << file_one << " to " << file_two << "..." << endl;
			cout <<"Placing the result in " << outFile << "..." << endl;
			BRMALA003::Image originalImage(file_one);
			BRMALA003::Image imageToSubtract(file_two);
			originalImage - move(imageToSubtract);
			originalImage.saveImage(outFile);
			cout << "Done!" << endl;
			break;
		}
		if (s=="-i")
		{
			i++;
			//Extract the singular file name from the args
			file_one=string(argv[i]);
			i++;
			//Extract the output file name from the args
			outFile=string(argv[i]);
			//invert
			cout << "Inverting " << file_one << "..." << endl;
			cout <<"Placing the result in " << outFile << "..." << endl;
			BRMALA003::Image inverted_img(file_one);
			!inverted_img;
			inverted_img.saveImage(outFile);
			cout << "Done!" << endl;
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
			i++;
			//Extract the output file name from the args
			outFile=string(argv[i]);
			//mask
			cout << "Masking " << file_one << " with " << file_two << "..." << endl;
			cout <<"Placing the result in " << outFile << "..." << endl;
			BRMALA003::Image originalImage(file_one);
			BRMALA003::Image mask_img(file_two);
			originalImage/move(mask_img);
			originalImage.saveImage(outFile);
			break;
		}
		if (s=="-t")
		{
			i++;
			//Extract the singular file name from the args
			file_one=string(argv[i]);
			i++;
			//Extract the threshold value from the args
			//cast it to an integer
			string thresh = string(argv[i]);
			thresh_int=  atoi(thresh.c_str());
			i++;
			//Extract the output file name from the args
			outFile=string(argv[i]);
			//threshold
			cout << "Thresholding " << file_one << " with " << thresh << "..." << endl;
			cout <<"Placing the result in " << outFile << "..." << endl;
			BRMALA003::Image threshImg(file_one);
			threshImg*thresh_int;
			threshImg.saveImage(outFile);
			break;
		}
		
	}
	
	return 0;
}	

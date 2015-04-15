//Image.cpp
//Author: Alan Berman
//13/04/2015

#include <memory>
#include "Image.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
//Creates a unique_ptr to a PNG image
namespace BRMALA003
{
	using namespace std;
	//Constructor
	Image::Image(int w, int h)
	{
		width=w;
		height=h;
		image_ptr=NULL;
	}
	//Image_ptr accessor	
	unique_ptr<unsigned char[]>& Image::getImagePtr()
	{
		return image_ptr;
	}
	void Image::constructImage(string filename, int rows, int columns)
	{
		ifstream img(filename).c_str(), ios::in|ios::binary);
		for (int i=0;i<columns;++i)
		{
			unique_ptr<unsigned char[]> image_row = new unsigned char[rows];
			img.read((char*)image_row, rows);
			image_ptr[i]=image_row;
		}
		
	}
	//Copy Constructor
	//Image(const Image & rhs);
	//Move Constructor
	//Image(Image && rhs);
	//Copy and Move Assignment Operators
	//Image & operator=(const Image & rhs); 
	//Image & operator=(Image && rhs);
	
	
}

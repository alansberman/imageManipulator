//Image.cpp
//Author: Alan Berman
//13/04/2015

#include <memory>
#include "Image.h"
#include <string>
#include <iostream>
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
	unique_ptr<unsigned char[]>& getImagePtr()
	{
		return image_ptr;
	}
	//Copy Constructor
	//Image(const Image & rhs);
	//Move Constructor
	//Image(Image && rhs);
	//Copy and Move Assignment Operators
	//Image & operator=(const Image & rhs); 
	//Image & operator=(Image && rhs);
	
	
}

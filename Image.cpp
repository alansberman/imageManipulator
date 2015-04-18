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
//and supports various operations on the images
namespace BRMALA003
{
	using namespace std;
	//Constructor
	Image::Image(string filename, int w, int h)
	{
		width=w;
		height=h;
		constructImage(filename,w,h);
	}
	//Image_ptr accessor	
	unique_ptr<unsigned char[]>& Image::getImagePtr()
	{
		return image_ptr;
	}
	void Image::constructImage(string filename, int rows, int columns)
	{
		ifstream img(filename.c_str(), ios::in|ios::binary);
		unique_ptr<unsigned char[]> image(new unsigned char[rows*columns]); 
		img.read((char *)image.get(), rows*columns);
		image_ptr = move(image);
	}
	
	unique_ptr<unsigned char[]>& Image::addImages(string file1, int w1, int h1,string file2, int w2, int h2)
	{
		Image imageA = Image(file1,w1,h1);
		Image imageB = Image(file2,w2,h2);
		for (int i=0;i<h1;++i)
		{
			imageB.getImagePtr().get()[i] = imageA.getImagePtr().get()[i] + imageB.getImagePtr().get()[i];
		}
		return imageB.getImagePtr();
	}
	
	//Copy Constructor
	Image::Image(const Image & rhs)
	{
		width=rhs.width;
		height=rhs.height;
		//image_ptr=rhs.image_ptr;
	}
	//Move Constructor
	Image::Image(Image && rhs)
	{
		width=rhs.width;
		height=rhs.height;
		image_ptr=move(rhs.image_ptr);
	}
	//Copy and Move Assignment Operators
	Image & Image::operator=(const Image & rhs)
	{
		if(this != &rhs) 
		{
			width=rhs.width;
			height=rhs.height;
			//image_ptr=rhs.getImagePtr();
		}
		return *this;
	}
	Image & Image::operator=(Image && rhs)
	{
		if(this != &rhs) 
		{
			width=rhs.width;
			height=rhs.height;
			//image_ptr=rhs.image_ptr;
			rhs.width=-1;
			rhs.height=-1;
			rhs.getImagePtr()=NULL;
		}
		return *this;
	}
	
	
}

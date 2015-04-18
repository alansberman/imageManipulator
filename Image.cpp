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
	//Reads the PNG file and assigns image_ptr to it
	void Image::constructImage(string filename, int rows, int columns)
	{
		ifstream img(filename.c_str(), ios::in|ios::binary);
		unique_ptr<unsigned char[]> image(new unsigned char[rows*columns]); 
		img.read((char *)image.get(), rows*columns);
		image_ptr = move(image);
	}
	//Add method of 2 images which makes all the pixels in image 2 equal to
	//the sum of the first image's and the second image's pixel at that location
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
	
	//Sum method of 2 images which makes all the pixels in image 2 equal to
	//the difference between the first image's and the second image's pixel at that location
	unique_ptr<unsigned char[]>& Image::subtractImages(string file1, int w1, int h1,string file2, int w2, int h2)
	{
		Image imageA = Image(file1,w1,h1);
		Image imageB = Image(file2,w2,h2);
		for (int i=0;i<h1;++i)
		{
			imageA.getImagePtr().get()[i] = imageA.getImagePtr().get()[i] - imageB.getImagePtr().get()[i];
		}
		return imageA.getImagePtr();
	}
	//Inverts an image
	unique_ptr<unsigned char[]>& Image::invertImage(string file1, int w1, int h1)
	{
		Image inverted = Image(file1,w1,h1);
		for (int i=0;i<h1;++i)
		{
			inverted.getImagePtr().get()[i] = 255 - inverted.getImagePtr().get()[i];
		}
		return inverted.getImagePtr();
	}
	//Masks an image
	unique_ptr<unsigned char[]>& maskImage(string file1, int w1, int h1, string file2, int w2, int h2)
	{
		Image imageA = Image(file1,w1,h1);
		Image imageB = Image(file2,w2,h2);
		for (int i=0;i<h1;++i)
		{
			if (imageB.getImagePtr().get()[i] == 255)
			{
				imageA.getImagePtr().get()[i] = imageB.getImagePtr().get()[i];
			}
			else
			{
				imageA.getImagePtr().get()[i] = 0;
			}
		}
		return imageA.getImagePtr();
		
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

//Image.cpp
//Author: Alan Berman
//13/04/2015

#include "Image.h"
#include <memory>
#include <string>
#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>
//Creates a unique_ptr to a PNG image
//and supports various operations on the images
namespace BRMALA003
{
	using namespace std;
	//Constructor
	Image::Image(string filename)
	{
		loadImage(filename);
	}
	//Image_ptr accessor	
	unique_ptr<unsigned char[]>& Image::getImagePtr()
	{
		return image_ptr;
	}
	//Reads in a PNG file and assigns image_ptr to it
	void Image::loadImage(string inputFile)
	{
		string line = "";
		char c;
		ifstream img(inputFile.c_str(), ios::in|ios::binary);		
		while (!img.eof())
		{
			getline(img,line);
			c=line.at(0);
			//Skip the 'P5' line
			if (c=='P')
			{
				//cout << line << endl;
				continue;
			}
			//Skip comments
			else if (c=='#')
			{
				//cout << line << endl;
				continue;
			}
			//Find the line containing the number of rows and columns
			else if (line.length() > 3)
			{
				istringstream ss(line);
				ss >> width >> ws >> height;
				continue;
			}
			//Find the '255' line and consume its whitespace
			else if (c=='2')
			{
			    istringstream ss_255(line);
			    ss_255 >> ws;
			    break;
			}
		}
		unique_ptr<unsigned char[]> image(new unsigned char[width*height]); 
		img.read((char *)image.get(), width*height);
		image_ptr = move(image);
	}
	//Get width
	int Image::getWidth()
	{
		return width;
	}
	
	//Get height
	int Image::getHeight()
	{
		return height;
	}
	
	//Save image
	void Image::saveImage(string outFile)
	{
		ofstream output;
		output.open(outFile.c_str(), ios::out | ios::binary);
		output << "P5" << endl;
		output << "# Made a new image!" << endl;
		output << width << " " << height << endl;
		output << 255 << endl;
		output.write((char *) image_ptr.get(),width*height);
		output.close();
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
	//Using two images, make all the pixels in the first image equal to
	//the sum of the first image's and the second image's pixel
	// at that location
	Image & Image::operator+(Image && rhs)
	{
		 Image::iterator beg = this->begin(), end = this->end();
		 Image::iterator inStart = rhs.begin(), inEnd = rhs.end();
		 //Until the end of the unsigned char buffer is reached 
		 while ( beg != end) 
		 {
			 //Clamp the value to 255
			 //so that it doesn't exceed the allowed range
			 if (*inStart == 255)
			 {
				*beg = 255; 
				++beg; ++inStart; 
			 }
			 else
			 {
				*beg = *beg + *inStart; 
				++beg; ++inStart; 
			 }
		 } 
		 return *this;
	}
	//Using two images, make all the pixels in the first image equal to
	//the difference between the first image's and the 
	//second image's pixel at that location
	Image & Image::operator-(Image && rhs)
	{
		 Image::iterator beg = this->begin(), end = this->end();
		 Image::iterator inStart = rhs.begin(), inEnd = rhs.end();
		 //Until the end of the unsigned char buffer is reached
		 while ( beg != end) 
		 {
			 //Clamp the value to 0
			 //so that a negative value is not obtained
			 if (*beg == 0 || *inStart == 0)
			 {
				*beg = 0; 
				++beg; ++inStart;
			 }
			 else
			 {
				*beg = *beg - *inStart; 
				++beg; ++inStart;
			 }		  
		 } 
		 return *this;
	}
	//Invert the pixels of an image
	Image & Image::operator!(void)
	{
		 Image::iterator beg = this->begin(), end = this->end();
		 //Until the end of the unsigned char buffer is reached
		 while ( beg != end) 
		 {			 
			*beg = 255 - *beg; 
			++beg;			 		  
		 } 
		 return *this;
	}
	//Using two images, copy all the pixels in the second image to
	//the first image (if they're 255), else set all the first image's
	//pixels to 0
	Image & Image::operator/(Image && rhs)
	{
		 Image::iterator beg = this->begin(), end = this->end();
		 Image::iterator inStart = rhs.begin(), inEnd = rhs.end();
		 //Until the end of the unsigned char buffer is reached 
		 while ( beg != end) 
		 {
			 //Only copy values from the second image if they're 255
			 if (*inStart == 255)
			 {
				*beg = *inStart; 
				++beg; ++inStart; 
			 }
			 //Else set the values to 0
			 else
			 {
				*beg = 0; 
				++beg; ++inStart; 
			 }
		 } 
		 return *this;
	}
	//Using a threshold value, set all the pixels in an image
	//bigger than the threshold to 255, else set them to 0
	Image & Image::operator*(int thresh_value)
	{
		 Image::iterator beg = this->begin(), end = this->end();
		 //Until the end of the unsigned char buffer is reached
		 while ( beg != end) 
		 {	
			if (*beg > thresh_value)
			{
				*beg = 255; 
				++beg; 
			}
			else
			{ 		 
				*beg = 0; 
				++beg;
			}			 		  
		 } 
		 return *this;
	}
	
	Image & Image::operator<<(string outFile)
	{
		Image::saveImage(outFile);
	}
	
	Image & Image::operator>>(string inputFile)
	{
		Image::loadImage(inputFile);
	}
}

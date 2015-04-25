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
		constructImage(filename);
	}
	//Image_ptr accessor	
	unique_ptr<unsigned char[]>& Image::getImagePtr()
	{
		return image_ptr;
	}
	//Reads the PNG file and assigns image_ptr to it
	void Image::constructImage(string filename)
	{
		string line = "";
		char c;
		ifstream img(filename.c_str(), ios::in|ios::binary);
		
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
				cout << line << endl;
				istringstream ss(line);
				ss >> width >> ws >> height;
				//cout << width << " " << height << endl;
				continue;
			}
			//Find the '255' line and consume its whitespace
			else if (c=='2')
			{
				//cout << line << endl;
				//cout << "got 255" << endl;
			    istringstream ss_255(line);
			    ss_255 >> ws;
			    cout << line << endl;
			    break;
			}
		}
		cout << "hello!" << endl;
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
		output << "#" << endl;
		output << width << " " << height << endl;
		output << 255 << endl;
		output.write((char *) image_ptr.get(),width*height);
		output.close();
	}
	
	//Add method of 2 images which makes all the pixels in image 2 equal to
	//the sum of the first image's and the second image's pixel at that location
	unique_ptr<unsigned char[]>& Image::addImages(string file1, string file2,string outFile) //////////////outfile
	{
		Image imageA = Image(file1);
		Image imageB = Image(file2);
		for (int i=0;i<(imageA.getWidth() * imageA.getHeight());++i)
		{
			imageB.getImagePtr().get()[i] = imageA.getImagePtr().get()[i] & imageB.getImagePtr().get()[i];
		}
		ofstream output;
		output.open(outFile.c_str(), ios::out | ios::binary);
		output << "P5" << endl;
		output << "#" << endl;
		output << imageB.getWidth() << " " << imageB.getHeight() << endl;
		output << 255 << endl;
		output.write((char *) imageB.getImagePtr().get(),width*height);
		output.close();
		return imageB.getImagePtr();
	}
	
	//Sum method of 2 images which makes all the pixels in image 2 equal to
	//the difference between the first image's and the second image's pixel at that location
	unique_ptr<unsigned char[]>& Image::subtractImages(string file1, string file2)
	{
		Image imageA = Image(file1);
		Image imageB = Image(file2);
		for (int i=0;i<(imageA.getWidth() * imageA.getHeight());++i)
		{
			imageA.getImagePtr().get()[i] = imageA.getImagePtr().get()[i] - imageB.getImagePtr().get()[i];
		}
		return imageA.getImagePtr();
	}
	//Inverts an image
	unique_ptr<unsigned char[]>& Image::invertImage(string file1)
	{
		Image inverted = Image(file1);
		for (int i=0;i<(inverted.getWidth() * inverted.getHeight());++i)
		{
			inverted.getImagePtr().get()[i] = 255 - inverted.getImagePtr().get()[i];
		}
		return inverted.getImagePtr();
	}
	//Masks an image
	unique_ptr<unsigned char[]>& Image::maskImage(string file1, string file2)
	{
		Image imageA = Image(file1);
		Image imageB = Image(file2);
		for (int i=0;i<(imageA.getWidth() * imageA.getHeight());++i)
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
	//Makes a threshold mask image
	unique_ptr<unsigned char[]>& Image::threshImage(string file1, int threshold)
	{
		Image threshImage = Image(file1);
		for (int i=0;i<(threshImage.getWidth() * threshImage.getHeight());++i)
		{
			if (threshImage.getImagePtr().get()[i] > threshold)
			{
				threshImage.getImagePtr().get()[i] = 255;
			}
			else
			{
				threshImage.getImagePtr().get()[i] = 0;
			}
		}
		return threshImage.getImagePtr();
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
	
	Image & Image::operator+(Image && rhs)
	{
		 Image::iterator beg = this->begin(), end = this->end();
		 Image::iterator inStart = rhs.begin(), inEnd = rhs.end();
		 cout << "Yo" << endl;
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
	Image & Image::operator-(Image && rhs)
	{
		 Image::iterator beg = this->begin(), end = this->end();
		 Image::iterator inStart = rhs.begin(), inEnd = rhs.end();

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
	
	
	
	
}

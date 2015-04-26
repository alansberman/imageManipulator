//UnitTests.cpp
//Author: Alan Berman
//26/04/2015

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <string>
#include "Image.h"
#include <memory>
#include <string>
#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>


bool checkImagesEqual (BRMALA003::Image& old, BRMALA003::Image& new_img)
{
	BRMALA003::Image::iterator old_beg = old.begin(), old_end = old.end();
	BRMALA003::Image::iterator new_beg = new_img.begin(), new_end = new_img.end();
	//Iterate through each pixel in the image
	while (old_beg!=old_end)
	{
	 //to check that the image has actually been changed
	 //if pixels different
		 if (*old_beg != *new_beg)
		 {
			return false;
		 }
		 
		++new_beg; ++old_beg; 
		 
	}
	return true; 	
}
//Check added image doesn't contain pixels with values >255
bool checkTwoFiveFiveBoundary (BRMALA003::Image& added)
{
	BRMALA003::Image::iterator added_beg = added.begin(), added_end = added.end();
	while ( added_beg != added_end) 
	{
		//Check the value isn't >255
		if (*added_beg> 255 )
		{
			return false; 
		}
		else
		{
			++added_beg; 
	    }
	}
	return true; 
		
}
//Check subtracted image doesn't contain pixels with values <0
bool checkZeroBoundary(BRMALA003::Image& subbed)
{
	BRMALA003::Image::iterator subbed_beg = subbed.begin(), subbed_end = subbed.end();
	while ( subbed_beg != subbed_end) 
	{
		//Check the value isn't >255
		if (*subbed_beg> 255 )
		{
			return false; 
		}
		else
		{
			++subbed_beg; 
	    }
	}
	return true; 
		
}

//Check the masked image is not the same as the original
TEST_CASE("Masked image M1","[]")
{
	BRMALA003::Image orig("shrek_rectangular.pgm");
	BRMALA003::Image masked("shrek_rectangular.pgm");
	int thresh = 60;
	masked*thresh;
	masked.saveImage("thresh.pgm");
	//Check dimensions equal
	REQUIRE(masked.getWidth()==orig.getWidth());
	REQUIRE(masked.getHeight()==orig.getHeight());
	//Check the masked image has changed from its original state
	REQUIRE(checkImagesEqual(masked,orig)==false);
}

//Invert an image, and then invert it again
//and check the result is the same as the original
TEST_CASE("Invert a masked image twice","[]")
{
	BRMALA003::Image to_invert("Lenna_standard.pgm");
	BRMALA003::Image orig("Lenna_standard.pgm");
	//Invert twice
	!to_invert;
	!to_invert;
	//Produce image
	to_invert.saveImage("inverted.pgm");
	//Check dimensions equal
	REQUIRE(to_invert.getWidth()==orig.getWidth());
	REQUIRE(to_invert.getHeight()==orig.getHeight());
	REQUIRE(checkImagesEqual(to_invert,orig)==true);
}

//Create a masked image
TEST_CASE("Create a masked image","[]")
{
	BRMALA003::Image to_mask("Lenna_standard.pgm");
	BRMALA003::Image mask_with("Lenna_hat_mask.pgm");
	to_mask/std::move(mask_with);
	//Produce image
	to_mask.saveImage("masked.pgm");
	//Check dimensions equal
	REQUIRE(to_mask.getWidth()==mask_with.getWidth());
	REQUIRE(to_mask.getHeight()==mask_with.getHeight());	
}
//Check overloaded << and >>  operator
//Should produce the image (write it to a file)
TEST_CASE("Check I/O << operator","[]")
{
	BRMALA003::Image orig("");
	orig>>"shrek_rectangular.pgm";
	orig<<"shrek_copy";
}


//Add images
//Check they have been clamped correctly
//(no pixels with values >255)
TEST_CASE("Adding images and boundary checking","[]")
{
	BRMALA003::Image img_a("shrek_rectangular.pgm");
	BRMALA003::Image img_b("donkey_mask.pgm");
	img_a+std::move(img_b);
	img_a.saveImage("added.pgm");
	REQUIRE(checkTwoFiveFiveBoundary(img_a)==true);		
}
//Subtract images
//Check they have been clamped correctly
//(no pixels with values <0)
TEST_CASE("Subtracting images and boundary checking","[]")
{
	BRMALA003::Image img_a("shrek_rectangular.pgm");
	BRMALA003::Image img_b("donkey_mask.pgm");
	img_a-std::move(img_b);
	img_a.saveImage("subbed.pgm");
	REQUIRE(checkZeroBoundary(img_a)==true);		
}
//Image move constructor test
TEST_CASE("Image move constructor test","[]")
{
	BRMALA003::Image img_a("shrek_rectangular.pgm");
	BRMALA003::Image img_a_moved=std::move(img_a);
	BRMALA003::Image img_a_copy("shrek_rectangular.pgm");
	REQUIRE(checkImagesEqual(img_a_moved,img_a_copy)==true);
	//Check dimensions equal
	REQUIRE(img_a_moved.getWidth()==img_a_copy.getWidth());
	REQUIRE(img_a_copy.getHeight()==img_a_copy.getHeight());
}

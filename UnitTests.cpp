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
TEST_CASE("Masked image M1","")
{
	BRMALA003::Image original("shrek_rectangular.pgm");
	BRMALA003::Image copy = original;
	int thresh = 60;
	original*thresh;
	REQUIRE(copy!=original);
	REQUIRE(original.getWidth()==1280);
	REQUIRE(original.getHeight()==1207);
}

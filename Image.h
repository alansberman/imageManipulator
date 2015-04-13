//Image.h
//Author: Alan Berman
//13/4/2015

#ifndef IMAGE_H
#define IMAGE_H
#include <memory>

//Header file that includes the Image class declaration
namespace BRMALA003
{
	using namespace std;
	class Image
	{
		private:
		int width, height;
		unique_ptr<unsigned char[]> image_ptr;
		
		public:
		Image();
		~Image() = default;
		unique_ptr<unsigned char[]>& getImagePtr();
		//Copy Constructor
		Image(const Image & rhs);
		//Move Constructor
		Image(Image && rhs);
		//Copy and Move Assignment Operators
		Image & operator=(const Image & rhs); 
		Image & operator=(Image && rhs);
	
	};
}

#endif //IMAGE_H

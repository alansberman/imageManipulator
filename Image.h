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
		Image(string filename, int w, int h);
		~Image() = default;
		unique_ptr<unsigned char[]>& getImagePtr();
		void constructImage(string filename, int rows, int columns);
		unique_ptr<unsigned char[]>& addImages(string file1, int w1, int h1, string file2, int w2, int h2);
		unique_ptr<unsigned char[]>& subtractImages(string file1, int w1, int h1, string file2, int w2, int h2);
		unique_ptr<unsigned char[]>& invertImage(string file1, int w1, int h1);
		unique_ptr<unsigned char[]>& maskImage(string file1, int w1, int h1, string file2, int w2, int h2);
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

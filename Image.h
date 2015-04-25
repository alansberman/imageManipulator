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
		class iterator
		{
			private:
			unsigned char *ptr;
			// grant private access to Image class functions
			friend class Image;
			// construct only via Image class (begin/end)
			iterator(u_char *p) : ptr(p) {}

			public:
			//copy construct is public
			iterator( const iterator & rhs) : ptr(rhs.ptr) {}
			// define overloaded ops: *, ++, --, =
			iterator & operator=(const iterator & rhs);
			iterator & operator*(const iterator & rhs);
			iterator & operator++(const iterator & rhs);
			iterator & operator--(const iterator & rhs);
			
		
		};
 // define begin()/end() to get iterator to start and
 // "one-past" end.
		iterator begin(void); 
		
		Image(string filename);
		~Image() = default;
		unique_ptr<unsigned char[]>& getImagePtr();
		int getWidth();
		int getHeight();
		void saveImage(unique_ptr<unsigned char[]>& Image, string outFile);
		void loadImage();
		void constructImage(string filename);
		unique_ptr<unsigned char[]>& addImages(string file1,string file2,string outFile);
		unique_ptr<unsigned char[]>& subtractImages(string file1, string file2);
		unique_ptr<unsigned char[]>& invertImage(string file1);
		unique_ptr<unsigned char[]>& maskImage(string file1, string file2);
		unique_ptr<unsigned char[]>& threshImage(string file1, int threshold);
		
		//Copy Constructor
		Image(const Image & rhs);
		//Move Constructor
		Image(Image && rhs);
		//Copy and Move Assignment Operators
		Image & operator=(const Image & rhs); 
		Image & operator=(Image && rhs);
		//Operators
		Image & operator+(Image && rhs);
		Image & operator!(void);
		Image & operator/(Image && rhs);
		Image & operator-(Image && rhs);
		Image & operator*(Image && rhs);
		
	};
}

#endif //IMAGE_H

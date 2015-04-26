//Image.h
//Author: Alan Berman
//13/4/2015

#ifndef IMAGE_H
#define IMAGE_H
#include <memory>

//Header file that includes the Image class declaration
//and the iterator class declaration
namespace BRMALA003
{
	using namespace std;
	class Image
	{
		private:
		int width, height;
		unique_ptr<unsigned char[]> image_ptr;
		//Adapted from framework given in assignment brief
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
			iterator & operator=(iterator & rhs)
			{
				if(this != &rhs) 
				{
					ptr=rhs.ptr;					
				}
				return *this;
			}
			u_char & operator*(void)
			{
				return *ptr;
			}
			iterator & operator++(void)
			{
				++ptr;
				return *this;
			}
			iterator & operator++(int a)
			{
				iterator temp = *this;
				operator++();
				return temp;
			}
			iterator & operator--(void)
			{
				--ptr;
				return *this;
			}	
			iterator & operator--(int a)
			{
				iterator temp = *this;
				operator--();
				return temp;
			}
			bool operator!=(iterator &rhs)
			{
				return this->ptr != rhs.ptr;
			}
			
		
		};
		//begin()
		iterator begin(void) { return iterator(image_ptr.get());}
		//end()
		iterator end(void) { return iterator(image_ptr.get()+(width*height));}
		//Constructor
		Image(string filename);
		~Image() = default;
		//Return a reference to image_ptr
		unique_ptr<unsigned char[]>& getImagePtr();
		int getWidth();
		int getHeight();
		//Write the image to outFile
		void saveImage(string outFile);
		//Read in the PGM inputFile
		void loadImage(string inputFile);
		//Copy Constructor
		Image(const Image & rhs);
		//Move Constructor
		Image(Image && rhs);
		//Copy and Move Assignment Operators
		Image & operator=(const Image & rhs); 
		Image & operator=(Image && rhs);
		//Operator overloads
		Image & operator+(Image && rhs);
		Image & operator!(void);
		Image & operator/(Image && rhs);
		Image & operator-(Image && rhs);
		Image & operator*(int thresh_value);
		Image & operator<<(string outFile);
		Image & operator>>(string inputFile);
		
	};
}
#endif //IMAGE_H

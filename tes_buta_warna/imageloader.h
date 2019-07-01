#ifndef IMAGELOADER_H_INCLUDED
#define IMAGELOADER_H_INCLUDED

//Represents an image
class Image {
	public:
		Image(char* ps, int w, int h);
		~Image();

		char* pixels;
		int width;
		int height;
};
//Reads a bitmap image from file.
Image* loadBMP(const char* tes_2);


#endif // IMAGELOADER_H_INCLUDED

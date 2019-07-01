#include <windows.h>
#include <stdio.h> // Header File For StandardInput/Output
#include <gl.h> // Header File For The OpenGL32 Library
#include <glu.h> // Header File For The GLu32 Library
#include <glaux.h> // Header File For The Glaux Library
#include "bmp.h"
AUX_RGBImageRec *LoadBMP(char *Filename) // Loads ABitmap Image
{
FILE *File=NULL; //File Handle
if (!Filename)
// Make Sure A Filename Was Given
{
return NULL;
// If Not Return NULL
}
File=fopen(Filename,"r"); //Check To See If The File Exists
if (File)
// Does The File Exist?
{
fclose(File);
// Close The Handle
return auxDIBImageLoad(Filename); // Load The Bitmap And Return A Pointer
}
return NULL;
// If Load Failed Return NULL
}

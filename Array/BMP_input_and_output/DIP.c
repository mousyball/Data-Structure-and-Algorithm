#include "DIP.h"

void rgb2gray(int** dst, int** src, int height, int width)
{
  int i, j;
  unsigned char blue;
  unsigned char green;
  unsigned char red;
  unsigned char alpha;
  unsigned char gray;


  for(i=0; i<height; ++i){
    for(j=0; j<width; ++j){
      // bitwise operation
      alpha = (src[i][j] & 0xff000000) >> 24;
      blue  = (src[i][j] & 0x00ff0000) >> 16;
      green = (src[i][j] & 0x0000ff00) >> 8;
      red   = (src[i][j] & 0x000000ff) >> 0;

      // rgb2gray
      gray = 0.299*red + 0.587*green + 0.114*blue;

      // boundary check
      if(gray > 255)  gray = 255;
      if(gray < 0)    gray = 0;

      // combine 4 char[one_byte] into 1 int[four_byte].
      dst[i][j] = (gray<<24) | (gray<<16) | (gray<<8) | gray;
    }
  }

  return NULL;
}

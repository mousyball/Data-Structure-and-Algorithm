#include <stdio.h>
#include "def.h"

#ifndef _BMP_IO_H

#define _BMP_IO_H

  BMP bmp_read(const char* filename , int* height, int* width);
  void writeRGBImage(BMP* src, char* filename, int height, int width);

#endif

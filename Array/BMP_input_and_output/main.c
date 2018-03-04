#include <stdio.h>

#include "matrix.h"
#include "bmp_IO.h"
#include "def.h"
#include "DIP.h"

int main(int argc, char* argv[])
{
  //******filename input******//
#if (INPUT_TYPE==1)
  // [method 1] hard coding
  char* filename_in = ".//input_1.bmp";
  char* filename_out = ".//output.bmp";
#endif

#if (INPUT_TYPE==2)
  // [method 2] scan input
  char* filename_in;
  char* filename_out;
  char buffer[20];

  printf("Input image name:\n");
  scanf("%s", &buffer);
  filename_in = (char*)malloc( (strlen(buffer)+1)*sizeof(char));
  memcpy(filename_in, &buffer, strlen(buffer)+1);

  printf("Output image name:\n");
  scanf("%s", buffer);
  filename_out = (char*)malloc( (strlen(buffer)+1)*sizeof(char));
  memcpy(filename_out, &buffer, strlen(buffer)+1);
#endif

#if (INPUT_TYPE==3)
  // [method 3] cmd input
  char* filename_in = argv[1];
  char* filename_out = argv[2];
#endif


  // Declaration
  BMP img_in, img_out;
  int height, width;

  // read input image
  img_in = bmp_read(filename_in, &height, &width);

  // initial output image
  memcpy(img_out.header, img_in.header, sizeof(char)*54);
  img_out.data = matrix_alloc(height, width);

  // show header
  #if SHOW_HEADER
    int i;
    for(i=0; i<54; ++i){
      printf("header_in[%d]=%d\n", i, img_in.header[i]);
      printf("header_out[%d]=%d\n\n", i, img_out.header[i]);
    }
  #endif

  // image processing
  rgb2gray(img_out.data, img_in.data, height, width);

  // write image
  writeRGBImage(&img_out, filename_out, height, width);

  // free map
  matrix_dealloc(img_in.data, height);
  matrix_dealloc(img_out.data, height);

  system("pause");
  return 0;
}

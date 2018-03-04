#ifndef _DEF_H

#define _DEF_H

  #define INPUT_TYPE 1
  #define SHOW_HEADER 0

  typedef struct BMPimg {
    char header[54];
    int** data;

  } BMP;

#endif

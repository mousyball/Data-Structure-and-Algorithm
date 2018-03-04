#include "BMP_io.h"



// Read bmp file
BMP bmp_read(const char* filename , int* height, int* width)
{

    BMP img_temp;
    FILE* fp;
    int i, j, k;
    int byte_to_skip;
    short int depth;


    if (!filename || strlen(filename) == 0) {
        fprintf(stderr,"File can't be open\n");
        exit(1);
    }

    if (!(fp = fopen(filename, "rb")))
    {
        printf("File can't be opened\n");
        exit(1);
    }

    // read the image header
    fread(img_temp.header, sizeof(unsigned char), 54, fp);
    // get header.info
    memcpy(width, &img_temp.header[18], 4);
    memcpy(height, &img_temp.header[22], 4);
    memcpy(&depth, &img_temp.header[28], 2);

    // compute byte_to_skip, it depends on the image width and depth.
    byte_to_skip = ((*width)*depth)%4;

    // memory allocate
    img_temp.data = matrix_alloc(*height, *width);

    for (i=(*height)-1; i>=0; --i) {
        // read image data
        for(j=0; j<(*width); ++j) {
          if(depth == 24) fread(&img_temp.data[i][j], sizeof(unsigned char), 3, fp);
          if(depth == 32) fread(&img_temp.data[i][j], sizeof(unsigned char), 4, fp);
        }
        // padding
        for(k=0; k<byte_to_skip; ++k)
            getc(fp);
    }
    fclose(fp);

    return img_temp;
}


// write bmp file
void writeRGBImage(BMP* src, char* filename, int height, int width)
{
    FILE *fp;
    int i, j, k;
    unsigned char tmp[4];
    int padding;
    short int depth;

    fp = fopen(filename, "wb");

    for(i=0; i<54; ++i) {
        fputc(src->header[i], fp);
    }

    // compute padding byte
    memcpy(&depth, &src->header[28], 2);
    padding = (width*depth)%4;

    for(i=height-1; i>=0; --i) {
        for(j=0; j<width; ++j) {
            // bitwise operation
            tmp[0] = ( src->data[i][j] & 0x000000ff );
            tmp[1] = ( src->data[i][j] & 0x0000ff00 ) >> 8;
            tmp[2] = ( src->data[i][j] & 0x00ff0000 ) >> 16;

            if(depth == 32){
              tmp[3] = ( src->data[i][j] & 0xff000000 ) >> 24;
              fputc(tmp[3], fp);
            }

            // write into BMP.data
            fputc(tmp[2], fp);
            fputc(tmp[1], fp);
            fputc(tmp[0], fp);
        }

        for(k=0;k<padding;++k)
        {
            // padding
            tmp[0] = 255;
            fputc(tmp[0], fp);
        }
    }

    fclose(fp);
    return NULL;
}

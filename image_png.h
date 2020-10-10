#include "config.h"
#include "readpng.h"


#ifndef _IMAGE_PNG_H
#define _IMAGE_PNG_H 1


  extern FILE *infile;
  extern ulg image_width, image_height, image_rowbytes;
  extern uch *image_data;
  extern unsigned char image_channels;
  extern unsigned char image_color_type;
  extern unsigned char image_bit_depth;
  extern uch *image;
  extern uch *red;
  extern uch *image_data;
  
extern unsigned int number_of_passes;


extern png_structp png_ptr;
extern png_infop info_ptr;


extern struct _fct _fptr_png;

FILE* read_infile_png(char * filename);
unsigned char* get_image_png();
unsigned char* get_red_png(unsigned char* image);
void set_red_png(unsigned char* image, unsigned char* red);
void set_image_png(unsigned char *image);
void write_outfile_png(char* filename);

#endif /* _IMAGE_PNG_H */


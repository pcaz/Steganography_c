#include "config.h"
#include "readpng.h"


#ifndef _IMAGE_H
#define _IMAGE_H 1


  extern FILE *infile;
  extern ulg image_width, image_height, image_rowbytes;
  extern int image_channels;
  extern uch *image_data;
  extern uch *image;
  extern uch *red;
  

extern FILE* read_infile(string filename);
extern uch* get_image();
extern uch* get_red(uch* image);
extern void set_red(uch* image, uch* red);
extern void set_image(uch* image);
extern void write_outfile( string filename);

png_byte color_type;
png_byte bit_depth;

png_structp png_ptr;
png_infop info_ptr;
extern unsigned int number_of_passes;


#endif /* _IMAGE_H */


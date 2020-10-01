#include "config.h"
#include "readpng.h"


#ifndef _IMAGE_H
#define _IMAGE_H 1


  extern FILE *infile;
  extern ulg image_width, image_height, image_rowbytes;
  extern uch *image_data;
  extern png_byte image_channels;
  extern png_byte image_color_type;
  extern png_byte image_bit_depth;
  extern uch *image;
  extern uch *red;
  

extern FILE* read_infile(string filename);
extern uch* get_image();
extern uch* get_red(uch* image);
extern void set_red(uch* image, uch* red);
extern void set_image(uch* image);
extern void write_outfile( string filename);

extern unsigned int number_of_passes;


extern png_structp png_ptr;
extern png_infop info_ptr;

#endif /* _IMAGE_H */


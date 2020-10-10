#include <jpeglib.h>
#include <setjmp.h>
#include "config.h"



#ifndef _IMAGE_JPG_H
#define _IMAGE_JPG_H 1

extern struct _fct _fptr_jpg;

struct jpegErrorManager {
    /* "public" fields */
    struct jpeg_error_mgr pub;
    /* for return to caller */
    jmp_buf setjmp_buffer;
};

extern unsigned long image_rowbytes;
extern unsigned long image_height;
extern unsigned long image_width;
extern unsigned char image_channels;
extern unsigned char image_color_type;
extern unsigned char image_bit_depth;
extern unsigned char* image_data;


FILE* read_infile_jpg(char * filename);
unsigned char* get_image_jpg();
unsigned char* get_red_jpg(unsigned char* image);
void set_red_jpg(unsigned char* image, unsigned char* red);
void set_image_jpg(unsigned char *image);
void write_outfile_jpg(char* filename);


#endif // IMAGE_JPG_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "config.h"
#include "image_jpg.h"
#include "jpeglib.h"

FILE* file;
struct jpeg_compress_struct cinfo_out;
struct jpeg_error_mgr jerr_out;

struct _fct _fptr_jpg =
  {
   &read_infile_jpg,
   &get_image_jpg,
   &get_red_jpg,
   &set_red_jpg,
   &set_image_jpg,
   &write_outfile_jpg
  };






FILE* read_infile_jpg(char * filename) {



  if ((file = fopen(filename, "rb")) == NULL) {
    fprintf(stderr, "can't open %s\n", filename);
    exit(1);
  }

  

 //fclose(infile);
 
 return file;
}
unsigned char* get_image_jpg() {


  struct jpeg_decompress_struct cinfo;
  JSAMPARRAY buffer;	
  int row_stride;
  struct jpegErrorManager myerr;
  char jpegLastErrorMsg[JMSG_LENGTH_MAX];
  unsigned char *image;

  //   cinfo. err= &myerr;
    /* note : *(cinfo->err) is now equivalent to myerr->pub */

    /* output_message is a method to print an error message*/ 
    //cinfo.err->output_messag (cinfo);      

    /* Create the message */
    //cinfo.err->format_message  (cinfo, jpegLastErrorMsg);

    /* Jump to the setjmp point 
    // longjmp(myerr->setjmp_buffer, 1);
    */
    cinfo.err = jpeg_std_error(&myerr.pub);
  //jerr.pub.error_exit = jpegErrorExit
 
  jpeg_create_decompress(&cinfo);

  jpeg_stdio_src(&cinfo, file);

  
  (void)jpeg_read_header(&cinfo, TRUE);

  (void) jpeg_start_decompress(&cinfo);

  row_stride = cinfo.output_width * cinfo.output_components;
  image_channels = cinfo.output_components;
  image_width = cinfo.output_width;
  image_height = cinfo.output_height;
  image_rowbytes = row_stride;
  image_color_type = 2;
  image_bit_depth = 8;
 
  
  buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);
  image = (unsigned char*) malloc(row_stride * cinfo.output_height);
  if(image == NULL) error("Not enough memory to allocate image");
  
   while (cinfo.output_scanline < cinfo.output_height) {
    (void) jpeg_read_scanlines(&cinfo, buffer, 1);
    memcpy (&image[(cinfo.output_scanline-1) * row_stride], *buffer, row_stride); 
   }

 (void) jpeg_finish_decompress(&cinfo);

 jpeg_destroy_decompress(&cinfo);
 image_data = image; 
    return image; 
}
unsigned char* get_red_jpg(unsigned char* image) {
  unsigned char *red;
  int i;
  int j;

  // get red buffer
  if((red = (unsigned char*)malloc(image_rowbytes*image_height)) == NULL){
    fprintf(stderr, PROGNAME ": Not enough memory\n");
    return NULL;
  }

  
  for(i=0, j=0; i< image_rowbytes*image_height; i++)
    {
      if( i%image_channels == 0)
	{
	  red[j] = image[i];
	  j++;
	}
    }

  return red;

}

void set_red_jpg(unsigned char* image, unsigned char* red) {

  int i;
  int j;

  for(i=0, j=0; i< image_rowbytes*image_height; i++)
    {
      if( i%image_channels == 0)
	{
	  image[i] = red[j];
	  j++;
	}
    }
  
  free(red);
}
void set_image_jpg(unsigned char* image) {
  


  jpeg_create_compress(&cinfo_out);

  cinfo_out.err = jpeg_std_error(&jerr_out);

 

  cinfo_out.image_width = image_width; 	
  cinfo_out.image_height = image_height;
  cinfo_out.input_components = 3;		
  cinfo_out.in_color_space = JCS_RGB;


  // cinfo_out.arith_code =FALSE;
  //cinfo_out.block_size = 1;

  jpeg_set_defaults(&cinfo_out);
  jpeg_set_quality(&cinfo_out, 100, FALSE);

  //cinfo_out.jpeg_color_space=JCS_RGB;
  //cinfo_out.color_transform = JCT_SUBTRACT_GREEN;
  //  jpeg_set_colorspace(&cinfo_out, JCS_RGB);



  
   
   return;  
}
void write_outfile_jpg(char* filename) {
  int row_stride;
  JSAMPROW row_pointer[1];
  
  if ((file = fopen(filename, "wb")) == NULL) {
    fprintf(stderr, "can't open %s\n", filename);
    exit(1);
  }

  
   
  row_stride = image_width * 3;
  //cinfo_out.dest=file;
  jpeg_stdio_dest(&cinfo_out, file);
  jpeg_start_compress(&cinfo_out, TRUE);
  
   while (cinfo_out.next_scanline < cinfo_out.image_height) {
      row_pointer[0] = & image_data[cinfo_out.next_scanline * row_stride];
      (void) jpeg_write_scanlines(&cinfo_out, row_pointer, 1);
  }

  jpeg_finish_compress(&cinfo_out);
}

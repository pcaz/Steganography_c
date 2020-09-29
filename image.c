#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <png.h>
#include "config.h"
#include "image.h"
#include "readpng.h"


FILE *infile;
ulg image_width, image_height, image_rowbytes;
int image_channels;
uch *image_data;
static double display_exponent;
  
FILE* read_infile(string filename){

  static int error = 0;
  static int rc;
  
  if (!(infile = fopen(filename, "rb"))) {
        fprintf(stderr, PROGNAME ":  can't open PNG file [%s]\n", filename);
        ++error;
    } else {
        if ((rc = readpng_init(infile, &image_width, &image_height)) != 0)
	  {
            switch (rc)
	      {
                case 1:
                    fprintf(stderr, PROGNAME
                      ":  [%s] is not a PNG file: incorrect signature\n",
                      filename);
                    break;
                case 2:
                    fprintf(stderr, PROGNAME
                      ":  [%s] has bad IHDR (libpng longjmp)\n", filename);
                    break;
                case 4:
                    fprintf(stderr, PROGNAME ":  insufficient memory\n");
                    break;
                default:
                    fprintf(stderr, PROGNAME
                      ":  unknown readpng_init() error\n");
                    break;
            }
            ++error;
	}
  if (error) fclose(infile);


  }
  if (error) {
        fprintf(stderr, PROGNAME ":  aborting.\n");
        exit(2);
    }
  return infile;
}

uch* get_image()
{
  display_exponent = 2.2;
    image_data = readpng_get_image(display_exponent, &image_channels,
      &image_rowbytes);
       
    return image_data;
    
}

uch* get_red(uch* image)
{

  uch *red;
  int i;
  int j;

  // get red buffer
  if((red = (uch *)malloc(image_width*image_height)) == NULL){
    fprintf(stderr, PROGNAME ": Not enough memory\n");
    return NULL;
  }

  
  for(i=0, j=0; i< image_rowbytes*image_height; i++)
    {
      if( i%3 == 0)
	{
	  red[j] = image[i];
	  j++;
	}
    }

  return red;
 
  
}

void set_red(uch* image, uch* red)
{
  int i;
  int j;

  for(i=0, j=0; i< image_rowbytes*image_height; i++)
    {
      if( i%3 == 0)
	{
	  image[i] = red[j];
	  j++;
	}
    }
  
  free(red);
}

void set_image(uch* image)
{

}
void write_outfile(char* file_name)
//void write_png_file(char* file_name)
{
  int i;
  png_bytepp row_pointers = NULL;
   
        /* create file */
        FILE *fp = fopen(file_name, "wb");
        if (!fp)
	  fprintf (stderr, "[write_png_file] File %s could not be opened for writing", file_name);


        /* initialize stuff */
        png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

        if (!png_ptr)
	  fprintf(stderr,"[write_png_file] png_create_write_struct failed");

        info_ptr = png_create_info_struct(png_ptr);
        if (!info_ptr)
	  fprintf(stderr,"[write_png_file] png_create_info_struct failed");

        if (setjmp(png_jmpbuf(png_ptr)))
                fprintf(stderr,"[write_png_file] Error during init_io");

        png_init_io(png_ptr, fp);


        /* write header */
        if (setjmp(png_jmpbuf(png_ptr)))
                fprintf(stderr,"[write_png_file] Error during writing header");

	bit_depth = 8;
	color_type = 2;
	
        png_set_IHDR(png_ptr, info_ptr, image_width, image_height,
                     bit_depth, color_type, 0,0,0);

        png_write_info(png_ptr, info_ptr);

       if ((row_pointers = (png_bytepp)malloc(image_height*sizeof(png_bytep))) == NULL)
	 {
           png_destroy_write_struct(&png_ptr, &info_ptr);
           free(image_data);
           image_data = NULL;
           fprintf(stderr,"Not enough memory to write %s", file_name);
           exit(1);
         }

	
	for(i=0; i < image_height;i++)
	{
	  row_pointers[i] = &image_data[i*image_width*image_channels];
        }

        /* write bytes */
        if (setjmp(png_jmpbuf(png_ptr)))
                fprintf(stderr,"[write_png_file] Error during writing bytes");
	

        png_write_image(png_ptr,row_pointers);


        /* end write */
        if (setjmp(png_jmpbuf(png_ptr)))
                fprintf(stderr,"[write_png_file] Error during end of write");

        png_write_end(png_ptr, NULL);

        /* cleanup heap allocation */

        free(row_pointers);
	
	free(image_data);
	
        fclose(fp);
}

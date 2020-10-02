/* @(#)config.h
 */
#ifndef _CONFIG_H
#define _CONFIG_H 1

#include <stdio.h>

#define PROGNAME  "stegano"
#define LONGNAME  "Message hidden in image"
#define VERSION   "1.0"


#define string char*
#define SIZEMSG 255

extern int line;
extern string inFileName;
extern string outFileName;
extern char message[SIZEMSG];



void codage(int argc, string *argv);
void decodage(int argc, string *argv);

extern void badArgs();
extern void usage();
extern int remove_array(char **array, char *item, int array_length);

  
//#define DEBUG
#ifdef DEBUG
void trace(char* ctx,char* msg);
#endif

typedef struct image_fct
{
  FILE* (*read_infile)(char * filename);
  unsigned char* (*get_image)();
  unsigned char* (*get_red)(unsigned char* image);
  void (*set_red)(unsigned char* image, unsigned char* red);
  void (*set_image)(unsigned char *image);
  void (*write_outfile)(char* filename);
} _fct;



#endif /* _CONFIG_H */


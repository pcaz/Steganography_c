#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image_png.h"
#include "image_jpg.h"
#include "config.h"

unsigned char image_channels;
unsigned char image_color_type;
unsigned char image_bit_depth;


void codage(int argc, string *argv)
{
  
  char *motif;
  int in = 0;
  int out = 0;
  int msg = 0;
  uch *image;
  uch *red;;
  unsigned int val=1;
  unsigned int initial;
  int msg_length;
  
  struct _fct *_fptr_in = NULL;
  struct _fct *_fptr_out = NULL;
  
  // loop indexes 
  int i,j,k;
  
  
  // first, verify all args

  // jump over "coding"
    argv++;
    argc--;

    
  while (argc >0) {
    motif = *argv;
    
  if( *motif !='-'){
    fprintf(stderr, "%s","\nyou have to prefix all parameter unless coding/decoding with a tiret (-)\n");
    usage();
  }
  motif+= sizeof(char);

  if(strcmp(motif, "in")==0)
    {
      argv++;
      argc--;
      if( argc>0 && in==0)
	{
  	  inFileName = *argv ;
	  in=1;
          argv++;
          argc--;

	  
#ifdef DEBUG
	  trace("inFileName", inFileName);
#endif
	   continue;  
	}
      else
	{
	  badArgs();
	  return;
	}      
    }
  else if(strcmp(motif,"out")==0)
    {
      argv++;
      argc--;
      if( argc>0 && out==0)
	{
	  outFileName = *argv;
	  out=1;
          argv++;
          argc--;

#ifdef DEBUG
          trace("outFileName", outFileName);
#endif	    

	  continue;    
	} else
	{
	  badArgs();
	  return;
	}      

    }
  else if(strcmp(motif,"msg")==0)
    {
      argv++;
      argc--;
      if( argc>0 && msg==0)
	{
	  if(strlen(*argv) < SIZEMSG)
	    {
	      strncpy(message,*argv,strlen(*argv));
	      	      
	      msg=1;
	      argv++;
	      argc--;
#ifdef DEBUG
	      trace("message", message);
#endif	    
	    continue;
	    
	    }
	  else
	    {
	      fprintf(stderr, "%s%i%s", "\nNo more than ",SIZEMSG," characters in message");
	      return;
	    }
	}
      else
	{
	  badArgs(); return;
	
	}
  
    }
  else if (strcmp(motif, "line")==0)
	{
	  argv++;
	  argc--;
	  if( argc>0)
	    {
	      line = atoi(*argv);
	      argv++;
	      argc--;
#ifdef DEBUG
	      trace("line", line);
#endif	    
	      

	    }
	}
  else
    {
      fprintf(stderr, "%s%s%s","\nNot understand -",motif," parameter");
      usage();
    }
  }

  if( (in==0) || (out == 0) || (msg== 0)) {
    fprintf(stderr, "%s","\nNot enough parameters for coding\n");
    usage();
  }

  //so, we have all the necessary arguments (maybe line also)

  // load functions
  if (strcmp(extension(inFileName) ,".png")==0){ _fptr_in = &_fptr_png;}
  if (strcmp(extension(outFileName),".png")==0){ _fptr_out = &_fptr_png;}
  if (strcmp(extension(inFileName),".jpg")==0){ _fptr_in = &_fptr_jpg;}
  if (strcmp(extension(inFileName),".jpeg")==0){ _fptr_in = &_fptr_jpg;}

  if ((strcmp(extension(outFileName),".jpg")==0) ||  (strcmp(extension(outFileName),".jpeg")==0)){
    error("Unable to create a JPEG or JPG output file format, only PNG is supported !");
  }

  


  if (_fptr_in == NULL) error("Type of input file not supported");
  if (_fptr_out == NULL) error("Type of output file not supported");
  

  //    printf("\n%s\n\n",message);
  
  _fptr_in->read_infile(inFileName);
  image =_fptr_in-> get_image();
  red =_fptr_in->get_red(image);

  initial = (line-1) * image_width;
  
  // code length of message in the 8 first byte of red
  // (coding is 'little indian', least significant bit first)
  // sample:
  // 11 is 11010000
  

  msg_length = strlen(message);

  if(msg_length > 255) {
    fprintf(stderr, PROGNAME" Too large message, must be < 255 characters\n");
    exit(1);
  }

  for(i=0; i<8; i++) {
    red[i+initial] = (red[i]/2) * 2;
    red[i+initial] += (msg_length & (val << i)) >> i;
  }

  // then code message
  k=0;         // poition char in message
  j=initial+8; // Initial position in image plus size of msg_length (0..7)
  
  while(k < msg_length)
    {
      for(i=0; i<8; i++)
	{
	  red[j+i] = (red[j+i]/2)*2;
	  red[j+i] += (message[k] & (val << i)) >> i;
        }
      k++;
      j = j+8;	  
	  
    }
  
  _fptr_out->set_red(image,red);
  
  _fptr_out->set_image(image);

  _fptr_out->write_outfile(outFileName);
}

 

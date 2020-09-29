#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "image.h"

void decodage(int argc, string *argv)
{

  char *motif;
  int in = 0;
  uch *image;
  uch *red;
  int msg_length=0;
  unsigned int val=1;
  unsigned int initial;
  char msg_char;
  char *_message, *msg;

   // loop indexes 
  int i,j;


   // first, verify all args

  // jump over "coding"
  
    argv++;
    argc--;

   while (argc >0)
     {
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
       if( in==0)  {
	 fprintf(stderr, "%s","\nNot enough parameters for decoding\n");
	 usage();
       }
     
     //so, we have all the necessary arguments (maybe line also)

    read_infile(inFileName);
    image = get_image();
    red = get_red(image);

    initial = (line-1) * image_width;

    // read code length message
    // (coding is 'little indian', least significant bit first)
    // sample:
    // 11 is 11010000

    msg_length=0;
    for(i=0;i<8;i++)
      {
	if ((red[i+initial] % 2) == 1)
	  {
	    msg_length+= (val<<i);
	  }
      }

    // read message

    _message = (char *)malloc((msg_length +1)* sizeof(char));
    
    // loop on message
    msg = _message;
    for(j=8; j< 8*(msg_length + 1); j=j+8)
      {
	msg_char = (char) 0;
	// loop on character
	for (i=0; i<8; i++)
	  {
	    if((red[initial+j+i] % 2) == 1)
	      {
		msg_char += (val<<i);
	      }  
	    
	  }
	*msg = msg_char;
	msg++;
      }
    *msg = '\0';

    printf("\n%s\n\n",_message);
}




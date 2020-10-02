/**---------------------------------------------------------------------------
 *
 *  \file stegano.c
 *  \brief  Main program
 *  \author Pascal CAZABAT
 *  \version 1.0
 *  \date 2020/09/26
 *
 *  write and read message in an image file
 *
 *  Todo:
 *  - for the moment, only works with PNG/RGB files (8 bits per channel)
 *   -------------------------------------------------------------------------**/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"





int main(int argc, string *argv)
{

  // jump appname (arg[0])
  
  argv++;
  argc--;

  if(argc<1) {usage();}

  
  if (strcmp(*argv, "coding")==0){
    codage(argc,argv);
  }
  else if(strcmp(*argv,"decoding") ==0)
  {
    decodage(argc, argv);
  }
  else { 
    usage();
  }
  
} 
 

  



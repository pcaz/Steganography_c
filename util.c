/* @(#)util.c
 */

#ifndef _UTIL
#define _UTIL
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "config.h"

int line = 1;
string inFileName = NULL;
string outFileName = NULL;
char message[SIZEMSG];

/**
 * remove_array
 *
 * Remove an element from an array (memory doesn't change)
 *
 * array  array of strings (char**) 
 * return new size relevant of the array.
 *
**/
 
int remove_array(char **array, char *item, int array_length)
{
   int i;
   int index=-1;
   
   for(i=0;i<array_length; i++){
     if(strcmp(array[i],item) == 0)
       {
	 index = i;
       }
   }

   if (index == -1 ) return array_length;
   
   for(i = index; i < array_length - 1; i++) array[i] = array[i + 1];

   return(array_length - 1);
}

void usage()
{
   fprintf(stderr, "\n%s %s:  %s\n", PROGNAME, VERSION, LONGNAME);
   fprintf(stderr, "\n"
	   "Usage: coding -in fileIn -out fileOut -msg message [-line line]");
   fprintf(stderr, "\n"
	   "or decoding -in fileIn [-line line]\n");
   fprintf(stderr, "\n"
	   "default line is one \n\n");
   exit(1);

}


void badArgs(){
    fprintf(stderr,"\n Bad args\n");

}


#ifdef DEBUG
void trace(char* ctx, char* msg)
{
  fprintf(stderr,"%c%s%s%s%c",'\n',ctx," : ",msg,'\n');
}
#endif /* DEBUG */

#endif /* _UTIL_ */

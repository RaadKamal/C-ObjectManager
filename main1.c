/* 
 * main1.c
 * COMP 2160 Programming Practices
 * Assignment 4
 * 
 * compact should be called 3 times
 */

#include "ObjectManager.h"
#include <stdlib.h>
#include <stdio.h>

#define OBJECTS 2000L

struct ALF{
  int value;
  double d;
  char buffer[1024];
};

typedef struct ALF alf;

void tester(){
  double x;
  Ref test = insertObject(sizeof(alf));
  alf *ptr = (alf *)retrieveObject(test);

  ptr->value = rand();
  fprintf( stdout, "%d\n", ptr->value );
  x = ptr->d;

  fprintf( stdout, "%f\n", x );
  dropReference(test);
}// tester

int main( int argc, char *argv[] ){
  Ref me;
  long i;

  initPool();
  me = insertObject(sizeof(alf));
  
  for ( i=0 ; i<OBJECTS ; i++ )
    tester();
  dumpPool();
  destroyPool();
  
  return 0;
}// main

/* 
 * main3.c
 * COMP 2160 Programming Practices
 * Assignment 4
 * 
 * dumpPool will display 100 objects with size 16 bytes (why 16?)
 */

#include "ObjectManager.h"
#include <stdio.h>

struct ALF{
  int value;
  double d;
};

typedef struct ALF alf;

void tester(){
  Ref test1 = insertObject(sizeof(alf));
  Ref test2 = insertObject(sizeof(alf));
  Ref test3 = insertObject(sizeof(alf));
  alf *ptr1 = retrieveObject(test1);
  alf *ptr2 = retrieveObject(test2);

  ptr1->value = 5;
  ptr2->value = 10;
  fprintf( stdout, "%d\n", ptr1->value );
  ptr1->value = ptr2->value;
  fprintf( stdout, "%d\n", ptr1->value );
  dropReference(test1);
  dropReference(test2);
}// tester

int main( int argc, char *argv[] ){
  int i;
  
  initPool();

  for ( i=0 ; i<100 ; i++ )
    tester();
  dumpPool();
  destroyPool();
  
  return 0;
}// main

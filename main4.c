/* 
 * main4.c
 * COMP 2160 Programming Practices
 * Assignment 4
 * 
 * pass an object reference to a function.
 */

#include "ObjectManager.h"
#include <stdio.h>

struct LUCKY{
  int value1;
  int value2;
};

typedef struct LUCKY lucky;

void sub_tester( lucky *obj ){
  obj->value1 = 987;
  obj->value2 = 345;
}// sub_tester

void tester(){
  Ref test = insertObject(sizeof(lucky));
  
  lucky *ptr = retrieveObject(test);

  ptr->value1 = 456;
  ptr->value2 = 999;

  sub_tester( ptr );

  fprintf( stdout, "Is this right? %d %d\n", ptr->value1, ptr->value2 );
  dropReference(test);
}// tester

int main( int argc, char *argv[] ){
  initPool();
  
  tester();
  dumpPool();
  destroyPool();
  
  return 0;
}// main

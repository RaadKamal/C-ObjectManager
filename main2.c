/* 
 * main2.c
 * COMP 2160 Programming Practices
 * Assignment 4
 * 
 * compact should be called 3 times, once each for obj4, obj5 and obj6
 */

#include "ObjectManager.h"
#include <stdio.h>

#define OBJECTS 1000UL

struct ALF{
  int value;
  double d;
  char buffer[1024*128];
};

typedef struct ALF alf;

int main( int argc, char *argv[] ){
  initPool();

  Ref obj1 = insertObject(sizeof(alf));
  Ref obj2 = insertObject(sizeof(alf));
  Ref obj3 = insertObject(sizeof(alf));
  Ref obj4 = insertObject(sizeof(alf));
  Ref obj5 = insertObject(sizeof(alf));
  Ref obj6 = insertObject(sizeof(alf));

  destroyPool();

  return 0;
}// main

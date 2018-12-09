/*
 * ObjectManager.h
 * COMP2160 Programming Practices
 *
 * Object Manager header file
 */
#ifndef _OBJECT_MANAGER_H
#define _OBJECT_MANAGER_H

#ifndef MEMORY_SIZE
#define MEMORY_SIZE 1024*512
#endif

#define NULL_REF 0

typedef unsigned long Ref;
typedef unsigned long ulong;
typedef unsigned char uchar;

Ref insertObject( ulong size );
void *retrieveObject( Ref ref );
void addReference( Ref ref );
void dropReference( Ref ref );
void initPool();
void destroyPool();
void dumpPool();

#endif

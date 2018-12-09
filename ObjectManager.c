    // NAME: Mostafa Raad Kamal     
    // COURSE: COMP 2160, SECTION: A02    
    // INSTRUCTOR: Franklin Bristow     
    // ASSIGNMENT: Assignment 4, QUESTION: Question 1
    //      
    // REMARKS: The purpose of this program to create a Garbage collector and avoid the failure of perpetually allocating memory 


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "ObjectManager.h"


 //-------------------------------------------------------------------------------------
 // CONSTANTS and TYPES
 //------------------------------------------------------------------------------------- 


ulong freeptr;
static unsigned NumEle;
Ref reference;

typedef struct NODE Index;

struct NODE{
    unsigned int identifier;
    ulong length;
    ulong location;
    unsigned int count;
    Index *next;
};


 //-------------------------------------------------------------------------------------
 // VARIABLES
 //-------------------------------------------------------------------------------------

Index *Top;
uchar buffer1[MEMORY_SIZE];
uchar buffer2[MEMORY_SIZE];
uchar *Buffer_use;

 //-------------------------------------------------------------------------------------
 // PROTOTYPES
 //-------------------------------------------------------------------------------------

void compact();

 //-------------------------------------------------------------------------------------
 // FUNCTIONS
 //-------------------------------------------------------------------------------------

void initPool()
{  
   reference=1;
   freeptr=0;
   Top=NULL;
   NumEle=0;
   Buffer_use=buffer1;
}

 //------------------------------------------------------
 // insertObject
 //
 // PURPOSE: Updating the index of a char block on the memory
 // INPUT PARAMETERS: long size
 // It takes input as long size
 // OUTPUT PARAMETERS: Reference that is integer
 // It returns reference that is identifier
 // 1 to infinity value
 // No parameter is creating inside
 //------------------------------------------------------ 
Ref insertObject( ulong size )
{   
    
    assert(size>0 && size<MEMORY_SIZE);
   
    Index *new=malloc(sizeof(Index));    


    if((freeptr+size)>=MEMORY_SIZE)    //Time to check if we are out of memory or not
    {
        compact();

        if(freeptr+size>=MEMORY_SIZE)  //If any of our buffer is full, return NULL;
		{
		return NULL_REF;
		}    
    }
     
        new->identifier=reference;
        new->length=size;
        new->location=freeptr;
        new->count=1;

        new->next=NULL;

        if(Top==NULL)
         {
            Top=new;
         }
        else
         {
            new->next=Top;
            Top=new;
         }
    
     freeptr+=(size);
     reference++;
     NumEle++;
    
    return new->identifier;
}

 //------------------------------------------------------
 // retrieveObject
 //
 // PURPOSE: Finding a suitable place according to the reference
 // INPUT PARAMETERS: long size
 // It takes input as long size
 // OUTPUT PARAMETERS: Reference that is integer
 // It returns an address somewhere into the buffer
 // 1 to infinity value
 // A parameter that is created curr which is the top of the linkledlist
 //------------------------------------------------------ 
void *retrieveObject( Ref ref )
{
  assert(ref!=NULL || ref>0;)

  Index *curr=Top;

  assert(curr!=NULL);

  void *address=NULL;

  while(curr!=NULL)
  {
      if(curr->identifier==ref)
      {  
         break;
      }
      curr=curr->next;

  }
  
  address = &Buffer_use[curr->location];

  return address;

}

 //------------------------------------------------------
 // addReference
 //
 // PURPOSE: Finding the node according to the reference and incrementthe count
 // INPUT PARAMETERS: long Ref
 // It takes input as a long data type
 // OUTPUT PARAMETERS: Nothingeger
 // Just update an index
 // Nothing produce as value
 // A parameter that is created curr which is the top of the linkledlist
 //------------------------------------------------------ 


void addReference( Ref ref )
{
  Index *curr=Top;
  
  while(curr!=NULL)
  {
      if(curr->identifier==ref)
      {   
          curr->count+=1;
          break;
      }
      curr=curr->next;
  }
  
}


 //------------------------------------------------------
 // dropReference
 //
 // PURPOSE: Finding the node according to the reference and decrement the count
 // INPUT PARAMETERS: long Ref
 // It takes input as a long data type
 // OUTPUT PARAMETERS: Nothingeger
 // Just update an index
 // Nothing produce as value
 // A parameter that is created curr which is the top of the linkledlist
 //------------------------------------------------------ 
void dropReference( Ref ref )
{
  Index *curr=Top;
  
  while(curr!=NULL)
  {
      if(curr->identifier==ref)
      {   
          curr->count=(curr->count)-1;
          break;
      }
      curr=curr->next;
  }

}
 //------------------------------------------------------
 // dumpPool
 //
 // PURPOSE: Printing out the statement of the index 
 // INPUT PARAMETERS: Nothing
 // Nothing take input.
 // OUTPUT PARAMETERS: Nothing
 // Printing the information
 // Nothing produce as value
 // A parameter that is created curr which is the top of the linkledlist
 //------------------------------------------------------ 
 
void dumpPool()
{
    
     for(int i=NumEle ; i>0 ; i--)
      {
       Index *curr=Top;

       for(int j=0;j<i-1 && curr!=NULL; j++)  //printing reversely in order to match with the given output
        { 
	        curr=curr->next;  
        }

    if(curr->count>0)
     {
        printf("ID :%d    Address :%lu \tBlockSize:%lu \n", curr->identifier,curr->location,curr->length);
     }

    }
}

 //------------------------------------------------------
 // destroyPool
 //
 // PURPOSE: Free up the allocated space.
 // INPUT PARAMETERS: None
 // OUTPUT PARAMETERS: None
 // parameters created inside the function is a Node of the Top and a previous Node that is follow.
 //------------------------------------------------------ 

void destroyPool()

{
    Index *curr=Top;
    Index *follow;
    while(curr!=NULL)
    {
        follow=curr;
        curr=curr->next;
        free(follow);
    }
    NumEle=0;
    
}

 //------------------------------------------------------
 // compact
 //
 // PURPOSE: Compacting the buffer by copying items from one buffer to another and remove who has zero reference
 // INPUT PARAMETERS: Nothing
 // It takes input as long size
 // OUTPUT PARAMETERS: Reference that is integer
 // It doesn't return anything
 // A parameter that is created curr which is the top of the linkledlist and the prev that is the previous one
 // before curr.
 // int collectionbyte that holds the bytes of those removed objects and InuseBytes is the new byte of the new buffer
 // int start the location of the new buffer
 //------------------------------------------------------ 

void compact()
{
 
 Index *curr=Top;
 Index *prev=NULL;

 int CollectedBytes=0;
 int InUseBytes=0;
 int start=0;

 uchar *Buffer_use2;


 if(Buffer_use==buffer1)
  {
   Buffer_use2=buffer2;
  } 
 else                          //checking which buffer is in used.
  {
   Buffer_use2=buffer1;
  }

 while(curr!=NULL)

 { 
  if(curr->count>0)

    {
	
	 {	
 	  memcpy(&Buffer_use2[start],&Buffer_use[curr->location],curr->length);
          curr->location=start;
          start+=(curr->length);
          InUseBytes=start;
	 }
      prev=curr;
      curr=curr->next; 

    }

  else if(prev==NULL && curr->count<=0)
    	 {
           Top=curr->next;
    	   CollectedBytes+=curr->length;
           free(curr);
           curr=Top;   
   	       NumEle--;
         }

  else if(prev!=NULL && curr->count<=0)
         {
           prev->next=curr->next;
           CollectedBytes+=curr->length;
           free(curr);
           curr=prev->next;
           NumEle--;
         }

    }

  

  if(Buffer_use==buffer1)
    {
        Buffer_use=buffer2;
    }
  else                     //Setting which buffer we have to use now on
    {
        Buffer_use=buffer1;
    }

   freeptr=start;          //updating next buffer location
    
     
     printf("Compact: %d objects using %d bytes, %d bytes collected\n",
           NumEle,InUseBytes,CollectedBytes);


}


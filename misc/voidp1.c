

/*  voidp1.c  */  

/*                                                     
  A simple program using a void pointer. 
  This code is released to the public domain. 
  "Share and enjoy...."   ;)  
*/                    

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <math.h> 
      
    
int main(void) 
{ 
  
  int a = 42; 
  char mystr[12] = "Just a test";   
  char foo[] = "Another string" ; 
  
  /*  Void pointer  */  
  void *mydata;      
              
  mydata = &a ; 
  printf("I am pointing at %d\n", *(int*) mydata);
 
  mydata = &mystr ; 
  /* NOTE! We must only use one asterisk here (as shown) - not two */ 
  printf("Now I am pointing at %s\n", (char*) mydata);
 
  mydata = &foo ; 
  /* NOTE! We must only use one asterisk here (as shown) - not two */ 
  printf("Now I am pointing at %s\n", (char*) mydata);
 
  return 0; 

} 








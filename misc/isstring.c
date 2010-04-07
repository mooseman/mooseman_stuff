

/*  isstring.c  */   
/*  Test to see if a function argument is a string */  
/*  This code is released to the public domain. 
  "Share and enjoy...."   ;)  
*/                     
 
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <math.h> 


void test(void *myarg) 
{ 
   /* Get the size of myarg. This gives us some information. */ 
   int a = sizeof(myarg);  
       
   char *mystr = (char*) myarg; 
   printf("The size of the argument is %d \n", a);  
   printf("You entered %s \n", (char *) mystr);                 
}     


    
int main(void) 
{ 
  
  void *myptr;         
  char ch;   
  char *myval; 
                
  do { 
    puts("Enter some data : "); 
    scanf("%p", &myval);
    
    myptr = &myval ; 
    
    test(myptr); 
                        
    printf("Try again? (y/n) : "); 
    scanf(" %c%*c", &ch);  
  } 
  
    while( toupper(ch) != 'N' );  
       
  return 0; 

} 



 
 
 
  


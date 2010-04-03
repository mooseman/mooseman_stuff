

/*  fp1.c  */  

/*                                                     
  A simple program using function pointers. 
  This code is released to the public domain. 
  "Share and enjoy...."   ;)  
*/                    


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <math.h> 

/*  Multiply an integer by 2 */  
int times2(int num1) 
{ 
   int retval = num1 * 2; 
   return retval;   
}     

/*  Multiply an integer by 3 */  
int times3(int num1) 
{ 
   int retval = num1 * 3; 
   return retval;   
}  

      

    
int main(void) 
{ 
  
  int myint; 
  char *funcname;
    
  /*  Function pointer  */   
  int (*fp) (int) ; 
  char ch; 
                
  do { 
    puts("Enter an integer : "); 
    scanf("%d", &myint);
    
    /* If the number is even, we call sqr. 
       Otherwise, we call cube.  */                
    fp = (myint % 2 == 0) ? times2 : times3; 
    
    /*  Get the name of the function called */ 
    funcname = (myint % 2 == 0) ? "times2" : "times3" ;
    
    /*  Run the function  */  
    fp(myint);  
    
    {       
       printf("You called %s. Your answer is %d. \n" , funcname, fp(myint) );     
    }
                        
    printf("Try again? (y/n) : "); 
    scanf(" %c%*c", &ch);  
  } 
  
    while( toupper(ch) != 'N' );  
       
  return 0; 

} 








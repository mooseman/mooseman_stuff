

#  testgen.py 
#  Test generators. 
#  A couple of small functions to create a forward 
#  and reverse generator on a list. 
#  Author:  Andy Elvey 
# This code is released to the public domain.  


l = ["mary", "had", "a", "little", "lamb,", "its", "fleece", "was", "white", "as", "snow"]

def mynext(l, num):
  for item in range(num+1, len(l)-1):
     yield l[item] 

def myprev(l, num): 
  for item in range(num-1, 0, -1):
     yield l[item]  


#  Run the code      
a = mynext(l, 2) 

print a.next()

print a.next() 

print a.next() 


b = myprev(l, 11) 

print b.next() 

print b.next() 

print b.next() 




    


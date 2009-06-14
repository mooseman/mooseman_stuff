
#  prevnextclass.py 
#  A simple class which has both next and prev methods.  
#  Author: Andy Elvey 
#  This code is released to the public domain.  


import itertools 

class prevnext(object): 
   def init(self): 
      self.pointerlist = [] 
      self.datalist = [] 
	  
   def add(self, data): 
      for k,v in enumerate(data.split(" ")) : 
         self.pointerlist.append(k)	 		 
         self.datalist.append(v)
		 
   def display(self):
      print self.pointerlist, self.datalist, \
          zip(self.pointerlist, self.datalist) 
	
   def prev(self, itemnum):
      if 0 < itemnum <= len(self.datalist):
          self.prev = self.datalist[itemnum-1] 
      else: 
	      pass  
      print "Previous item to ", self.datalist[itemnum] ,  \
	  	 "is " , self.prev 		  
		  
   def next(self, itemnum): 
      if 0 <= itemnum < len(self.datalist): 
	      self.next = self.datalist[itemnum+1] 
      else: 
	      pass 
      print "Next item after ", self.datalist[itemnum],  \
	     "is " , self.next 		  
		  		  
	  	  		  		  		  	  	  
#  Run the code 
a = prevnext() 

a.init() 

a.add("mary had a little lamb") 

a.display() 

a.next(2) 

a.prev(3) 


	  		 
	  	  

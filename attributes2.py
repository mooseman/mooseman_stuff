
#  attributes2.py 
#  Another bit of code experimenting with attributes 

class foo(object): 
   def a(self): 
      pass 
   def b(self): 
      pass 
   def alpha(self): 
      return 10 
   def omega(self): 
      return "Just a nice little string"             
      
   def test(self, thing):
      if hasattr(self, thing): 
        print "found attribute", thing 
      else: 
        print "sorry - did not find attribute" 
        
#  Run the code 
a = foo() 
a.test('a')  
a.test('b') 
a.test('alpha') 
a.test('omega') 
a.test('foo') 
a.test('bar') 
a.test('baz') 


class bar(object): 
  def set(self, name, val): 
    setattr(self, name, val) 
  def display(self, name): 
    if hasattr(self, name): 
      # The usual way to print an attribute's value 
      print getattr(self, name) 
      # Another way to do it 
      print self.__dict__[name]  
    else: 
      print "Sorry - that attr does not exist" 


# Run the code 
a = bar()
a.set('bar', 123) 
a.set('baz', "A nice long string of text") 
a.display('bar') 
a.display('baz') 



        



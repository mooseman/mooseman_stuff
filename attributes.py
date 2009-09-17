

#  A simple example of getattr and setattr.  
#  Acknowledgement - this was done by "7stud" in the Python forum.  


class A(object):        
    def __getattr__(self, name):                          
        print ("python has been asked to retrieve the value "
          "for the non-existent attr: %s") % name
        #...so I'm going to return this random value:
        return 10

    def __setattr__(self, name, value):
        print ("python has been asked to set the "
                "attribute: %s to the value: %s") % (name, value)

        #...but I'm going to set the attribute to the value "hello" instead:
        self.__dict__[name] = "hello"


a = A()

print a.x
print a.alpha 
print a.beta 
print a.gamma 

a.y = 10
print a.y

''' --output:--
python has been asked to retrieve the value for the non-existent attr: x
10
python has been asked to set the attribute: y to the value: 10
hello ''' 

 

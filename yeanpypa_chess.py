#!/usr/bin/env/python

# A simple chess parser using the yeanpypa parsing 
# library. 
#  
# Author:  Andy Elvey 
# 
# Requires:  The yeanpypa parsing library  
# http://www.slash-me.net/dev/snippets/yeanpypa/documentation.html  
# 
# This code is released to the public domain. 

from yeanpypa import * 


# Start of simple chess grammar

# First, a function to use with the "setaction" function. 
# Setaction() is a built-in function in yeanpypa which allows us
# to do semantic actions in the grammar. 

def print_msg(text_to_print):	
	print text_to_print

	   
file = Literal('a') | Literal('b') | Literal('c') | Literal('d') \
       | Literal('e') | Literal('f') | Literal('g') | Literal('h') 
       
rank = Literal('1') | Literal('2') | Literal('3') | Literal('4') \
       | Literal('5') | Literal('6') | Literal('7') | Literal('8')         

square = Word( file + rank ) 

piece = Literal('N') | Literal('R') | Literal('K') \
        | Literal('Q') | Literal('B') 
        
pawn_capture = file + Literal('x') + square        
        
piece_capture = piece + Literal('x') + square        
        
pawn_move = square         
        
piece_move = piece + square        
        
        
# In the next rule, you see a rule called "specifying_move". 
# That's what I have called the situation where you have 
# two identical pieces (say, rooks) which cam both move to 
# a given square. In that case, you need to specify which piece 
# you want to move. You do that by naming the rank or file that 
# the piece is on, then the target square. 

specifying_move = piece + ( file | rank ) + square 
        
promote_to_piece = Literal('N') | Literal('R') \
        | Literal('Q') | Literal('B') 
               
pawn_promotion = Word( file + Literal('8') + promote_to_piece )    

# IMPORTANT NOTE! - I have put the various move-types in the 
# order shown below for a good reason. The "pawn promotion" and 
# "specifying move" must come first, because if they do not, the 
# parser looks for other "tokens" first and then fails.    
        
move = pawn_promotion.setAction( print_msg("Well done!") )  \
  | specifying_move.setAction( print_msg("Thanks for specifying") )  \
  | piece_move        \
  | pawn_move         \
  | piece_capture.setAction( print_msg("Nice piece capture") )  \
  | pawn_capture.setAction( print_msg("Nice pawn capture") )    

game = move
#  End of grammar 


#  A function to parse input
def parseit(grammar_name, input):

    result = parse(grammar_name, input)

    if result.full(): 
       print "Success!" 
    else: 
       print "Fail"  


#  Parse a few moves
parseit(game, "R4e7")
parseit(game, "e4")
parseit(game, "Nc4")
parseit(game, "c8Q")
parseit(game, "R3g6")
parseit(game, "Rxc5")
parseit(game, "Nxf7")




 



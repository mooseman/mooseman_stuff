
//
//  A simple chess-move parser for Spirit.
//  Requires -  Boost::Spirit version 2.0 or later
//
//  Written by:  Andy Elvey
//
//  Acknowledgements: I wanmt to acknowledge all of the developers who
//  have worked on Spirit, pretty much all of whom have helped me 
//  at one time or another on the Spirit mailing-list.     
//
//  This parser is released to the public domain.  
//
///////////////////////////////////////////////////////////////////////////////

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <string>

using namespace boost::spirit;
using namespace boost::spirit::qi;
using namespace boost::spirit::ascii;
using namespace boost::spirit::arg_names;

///////////////////////////////////////////////////////////////////////////////
//  Our chess move grammar
///////////////////////////////////////////////////////////////////////////////
template <typename Iterator>
struct chess : grammar<Iterator, space_type> 
{
    chess() : chess::base_type(expression)
    {
		
    expression 					
	%= en_passant_capture 
	 | pawn_capture_and_promotion
	 | q_castle 
	 | k_castle 
	 | specifying_move 
	 | promotion    
	 | pawn_capture 
	 | piece_move 
	 | square 
	 | pawn_move 
	 | ordinary_pawn_move 
     | ordinary_pawn_capture 
	 | ordinary_piece_move 
	 | piece_capture ; 

//  Pawn moves and captures
  pawn_move %= ( pawn_capture
   | ordinary_pawn_move 
   | promotion
   | pawn_capture_and_promotion ) ; 

  pawn_capture 
  %= ( ordinary_pawn_capture 
     | en_passant_capture ) ;

  ordinary_pawn_capture %= lexeme[ char_('a', 'h')  
  >>  char_('x') >> square ];     

//  An "en passant" capture is when a pawn captures
//  another pawn (which moved two squares in its first
//  move), **as if** it had only moved ONE square.  
//  This is the only move where the captured piece is
//  not on the "destination square".   
  en_passant_capture 
  %= lexeme[ ordinary_pawn_capture >> lit("ep") ];   

//  An ordinary pawn move just specifies the square that the pawn 
//  moves to.  
  ordinary_pawn_move %= square ; 
  
//  How to specify a square.  This is used in a number of places 
//  in the grammar.    
  square %= lexeme[ char_('a', 'h') 
           >> char_('1', '8') ] ;             
         
  promotion 
     %= lexeme[ char_('a', 'h') 
     >> ( char_('8') | char_('1') ) 
     >> ( char_('B')  
        | char_('N') 
        | char_('Q')
        | char_('R') ) ];    
         
// It is possible for a pawn to do a capture AND be promoted at 
// the same time. We cover that possibility here. 
   pawn_capture_and_promotion
   %= lexeme[ char_('a', 'h')  
     >>  char_('x') 
     >>  char_('a', 'h') 
	 >> ( char_('8') | char_('1') ) 
     >> ( char_('B')  
        | char_('N') 
        | char_('Q')
        | char_('R') ) ];  

         
// Piece moves and captures  
  piece_move %= ( ordinary_piece_move | piece_capture );     
  
  ordinary_piece_move 
  %= lexeme[ ( char_('B') 
                 | char_('K')
                 | char_('N') 
                 | char_('Q')
                 | char_('R') )
  >> square ];         
       
  piece_capture 
  %= lexeme[ ( char_('B') 
                 | char_('K')
                 | char_('N') 
                 | char_('Q')
                 | char_('R') )
  >>  char_('x') 
  >>  square ];        
       
       
// Specifying move. Sometimes, you may have two pieces of the same 
// type that can move to the same square. This means that you must 
// specify which one you are moving. This is done by giving either
// the rank or file of the piece being moved.
// For example,  N4e6 (which specifies the rank), 
// Rac3 (which specifies the file), and so on. 
// NOTE - I have included the bishop here. It is only possible to 
// have two bishops that attack the same square if one of them is 
// a promoted pawn.  

  specifying_move 
  %= lexeme[ ( char_('B')  
             | char_('N') 
             | char_('Q')
             | char_('R') )
  >> ( char_('a','h') | char_('1','8') )
  >>  square ] ;      

//  Castle on the Queen's side            
   q_castle %= lit("O-O-O") ; 
                                                            
//  Castle on the King's side
   k_castle %= lit("O-O") ;             

                
								
    }

    rule<Iterator, space_type> expression, square, 
	    pawn_move, ordinary_pawn_move, pawn_capture, 
		ordinary_pawn_capture, en_passant_capture, 
		pawn_capture_and_promotion, piece_move, ordinary_piece_move, 
		piece_capture, specifying_move, promotion, q_castle, 
		k_castle ;  
	
};


///////////////////////////////////////////////////////////////////////////////
//  Main program
///////////////////////////////////////////////////////////////////////////////
int
main()
{
		
    std::cout << "/////////////////////////////////////////////////////////\n\n";
    std::cout << " A chess move parser...\n\n";
    std::cout << "/////////////////////////////////////////////////////////\n\n";
	std::cout << " Type a chess move \n" ; 
    std::cout << " (e.g.  c4  Nf3  Rxe2  Bg5  b8Q  Qc7  \n" ;
    std::cout << " Type [x or X] to exit\n\n" ;

    typedef std::string::const_iterator iterator_type;
    typedef chess<iterator_type> chess;

    chess mychess; // Our grammar

    std::string str;

    while (std::getline(std::cin, str))
    {
        if (str.empty() || str[0] == 'x' || str[0] == 'X')
            break;

        std::string::const_iterator iter = str.begin();
        std::string::const_iterator end = str.end();
        bool r = phrase_parse(iter, end, mychess, space);

        if (r && iter == end)
        {
            std::cout << "-------------------------\n";
            std::cout << "Parsing succeeded\n";
            std::cout << "-------------------------\n";
        }
        else
        {
            std::string rest(iter, end);
            std::cout << "-------------------------\n";
            std::cout << "Parsing failed\n";
            std::cout << "stopped at: \": " << rest << "\"\n";
            std::cout << "-------------------------\n";
        }
    }

    std::cout << "Bye... :-) \n\n";
    return 0;
}



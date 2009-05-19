
//
//  A simple "toy SQL" parser for Spirit.
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
//  This parser parses a very small subset of SQL : 
//  the "select" clause only.
//  
//  NOT YET SUPPORTED - 
//  a) Left joins. 
//  b) The "case when" statement 
//      ( e.g. case when myvar <= 5 then 'foo' 
//                  when myvar  = 6 then 'bar'  
//                  else 'baz' 
//             end 
//                  as var1  )  
//  
//  NOTE - If you use a text variable in your query (e.g. 
//   select * from mystuff where var1 = 'abc' ;  ) make sure that 
//  the variable is in **single** quotes, as shown above. 
//
//  Examples of queries that will work - 
//    select * from table1, table2 where table1.foo = table2.bar ;  
//    select var1, var2, var3 from moredata, mystuff, yourdata ; 
//    select test as var1, foo as var2 from mystuff 
//          where a < 45 and b in (1, 2, 3) or c <= 78 ;  
//    select table1.foo as test1, table2.bar as test2 from mytables;  
//    select table1.foo as test, table2.bar as test2 from mytables where 
//           x > 334 and y < 5463 and z = 45; 
//
//#define BOOST_SPIRIT_DEBUG  ///$$$ DEFINE THIS WHEN DEBUGGING $$$///


#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace boost::spirit;
using namespace boost::spirit::qi;
using namespace boost::spirit::ascii;
using namespace boost::spirit::arg_names;


///////////////////////////////////////////////////////////////////////////////
//  Our Toy SQL grammar
///////////////////////////////////////////////////////////////////////////////
template <typename Iterator>
struct toysql : grammar<Iterator, space_type> 
{
    toysql() : toysql::base_type(expression)
	
    {
		
    expression 					
	%=  ( long_expression | short_expression ) 
	>> char_(";") ; 
	
	long_expression 
	%= select_clause >> from_clause >> where_clause ; 
	
	short_expression 
	%= select_clause >> from_clause ; 
		   
    select_clause 
	%= select_star | select_fields ; 
	
	select_star 
	%= lit("select") >> "*" ; 
	
	select_fields 
    %= lit("select") 
	>> multiple_identifiers | identifier ;
		   
	from_clause 
    %= lit("from") >>  identifier ; 
	
    where_clause
    %= lit("where") 
	>> 	multiple_compare_clause | compare_clause ; 
	
	compare_clause
	%= identifier >> op >> value ; 
	
	multiple_compare_clause 
	%= compare_clause % and_or ; 
	
	and_or 
	%= lit("and") | lit("or") ;  
	                                           	
    identifier %= lexeme[ ( alpha >> *(alnum | '_' | '.' ) ) ] ;   
	
//  Note the use here of the "%" operator.  This operator allows us 
//  to define a list of things separated by something. Here, we have 
//  a list of fields separated by commas.   	
	multiple_identifiers 
	%= identifier % ',' ;          
	
	op %=  ( lit("lt") 
	       | lit("le") 
		   | lit("eq") 
		   | lit("ge") 
		   | lit("gt") 
		   | lit("ne") 		   
		   | char_("<") 
		   | lit("<=") 
		   | char_("=") 
		   | lit(">=") 
		   | char_(">") 
		   | lit("!=") ) ;  
		   
    value %= int_  | quoted_string ;    
	
	quoted_string %= single_quoted_string | double_quoted_string ;  
	
	single_quoted_string %= lexeme[ "'" >> +(char_ - "'") >> "'"]; 
	
	double_quoted_string %= lexeme['"' >> +(char_ - '"') >> '"']; 		
		   
		                                                                                                                                                                                                                                                                             
   }

      rule<Iterator, space_type> expression, 
	     long_expression, short_expression, select_clause, 
		 select_star, select_fields, from_clause, where_clause, 
		 multiple_compare_clause, compare_clause, and_or, identifier, 
		 multiple_identifiers, op, value, quoted_string, 
		 single_quoted_string, double_quoted_string ; 
		                  
};



int main()  
{
    std::cout << "/////////////////////////////////////////////////////////\n\n";
    std::cout << "\t\t A toy SQL parser...\n\n";
    std::cout << "/////////////////////////////////////////////////////////\n\n";
    std::cout << "Type a SQL expression \n" ; 
    std::cout << " (e.g.  select * from mytable where city = \'Sydney\' ; ) \n" ;
    std::cout << " Type [q or Q] to quit\n\n" ;

    typedef std::string::const_iterator iterator_type;
    typedef toysql<iterator_type> toysql;

    toysql mytoysql; 

    std::string str;

    while (std::getline(std::cin, str))
    {
        if (str.empty() || str[0] == 'x' || str[0] == 'X')
            break;

        std::string::const_iterator iter = str.begin();
        std::string::const_iterator end = str.end();
        bool r = phrase_parse(iter, end, mytoysql, space);

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




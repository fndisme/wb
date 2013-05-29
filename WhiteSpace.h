#ifndef FND_WEB_GAME_SPIRIT_WHITE_SPACE_H
#define FND_WEB_GAME_SPIRIT_WHITE_SPACE_H
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
namespace WebGame {
namespace Utility {
  namespace qi = boost::spirit::qi ;
  namespace phoenix = boost::phoenix ;
  namespace ascii = boost::spirit::ascii ;

  template <typename Iterator>
  struct WhiteSpace: qi::grammar<Iterator>
  {
    WhiteSpace() : WhiteSpace::base_type(start)
    {
      using boost::spirit::standard::char_;

      start =
        char_(" \t\r\n")                               // tab/space/cr/lf
        | "//" >> *(char_ - "\n")
        | ";" >> *(char_ -"\n") // for lisp
        |   "/*" >> *(char_ - "*/") >> "*/"     // C-style comments
        ;
    }

    qi::rule<Iterator> start;
  };
}
}


#endif

#ifndef FND_GAME_WEB_GAME_UTITILIT_PAGE_FILE_PARSER_H
#define FND_GAME_WEB_GAME_UTITILIT_PAGE_FILE_PARSER_H
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/noncopyable.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
namespace WebGame {
namespace Utility {
  class PageParser : boost::noncopyable {
    public:
      explicit PageParser(const std::string& file_name) : m_tree() {
        using boost::property_tree::ptree ;
        read_json(file_name, m_tree) ;
      }
      //bool parse_from_file(const std::string& file_name) ;
      template<typename T> T get(const std::string& group,
          const std::string& key,
          const T& t = T()) {
        return m_tree.get(group + "." + key, t) ; // this is very slowly.
        //FIXIT....
      }

      template<typename T>
        void getGroup(const std::string& group,
            const std::string& key,
            T& container) {
          using boost::property_tree::ptree ;
          std::string info = group + "." + key ;
          typedef typename T::value_type value_type ;
          BOOST_FOREACH(ptree::value_type& v,
              m_tree.get_child(info))
            container.push_back(boost::lexical_cast<value_type>(v.second.data())) ;
        }

      template<typename T>
        void getGroup(const std::string& group,
            const std::string& key,
            const std::string& key2,
            T& container) {
          using boost::property_tree::ptree ;
          std::string info = group + "." + key + "." + key2 ;
          typedef typename T::value_type value_type ;
          BOOST_FOREACH(ptree::value_type& v,
              m_tree.get_child(info))
            container.push_back(boost::lexical_cast<value_type>(v.second.data())) ;
        }
    private:
      boost::property_tree::ptree m_tree ;
      //PageParser(const PageParser&) = delete ;
      //PageParser& operator = (const PageParser&) = delete ;
  } ;
}
}
#endif

#ifndef FND_GAME_RACING_UTILITY_H
#define FND_GAME_RACING_UTILITY_H
#include <string>
#include <vector>
#include <iosfwd>
namespace WebGame {
namespace Utility {

  std::string readFromFile(const char* infile) ;
  inline std::string readFromFile(const std::string& file_name) {
    return readFromFile(file_name.c_str()) ;
  }

  std::string readFromStream(std::istream& stream) ;
  std::vector<char> readBlockFromStream(std::istream& stream) ;
  std::vector<char> readBlockFromFile(const char* infile) ;

  /// this is not the fast way just a lazy dirty action
  std::vector<std::string> readFileAsLines(const std::string& filename,
      const std::string& linetoken = std::string("\r\n")) ;
  
}
}

#endif

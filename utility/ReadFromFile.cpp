#include "webgame/utility/ReadFromFile.h"

#include <cstdio>
#include <fstream>
#include <stdexcept>
#include <locale>
#include <iostream>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

namespace WebGame {
namespace Utility {
  std::string readFromFile(const char* file_name) {
#ifdef WIN32
    std::locale loc = std::locale::global(std::locale(".936")) ;
#endif
    std::ifstream instream(file_name, std::ios_base::binary
                           | std::ios_base::in) ;
    if(!instream.is_open()) {
#ifdef WIN32
      std::locale::global(loc) ;
#endif
      throw std::runtime_error(file_name) ;
    }
    //        instream.unsetf(std::ios::skipws) ;
    //        std::string return_info(std::istreambuf_iterator<char>(instream.rdbuf()),
    //                                std::istreambuf_iterator<char>()) ;
    std::string return_info(readFromStream(instream)) ;
#ifdef WIN32
    std::locale::global(loc) ;
#endif
    return return_info ;
  }

  std::vector<std::string> readFileAsLines(const std::string& file_name,
      std::string const& linebreak) {

    std::string data = readFromFile(file_name) ;

    using namespace boost ;
    std::vector<std::string> lines ;
    split(lines, data, is_any_of(linebreak), token_compress_on) ;
    return lines ;
  }

  std::vector<char> readBlockFromFile(const char* file_name) {
#ifdef WIN32
    std::locale loc = std::locale::global(std::locale(".936")) ;
#endif
    std::ifstream instream(file_name, std::ios_base::binary
                           | std::ios_base::in) ;
    if(!instream.is_open()) {
#ifdef WIN32
      std::locale::global(loc) ;
#endif
      throw std::runtime_error(file_name) ;
    }
    std::vector<char> return_info(readBlockFromStream(instream)) ;
#ifdef WIN32
    std::locale::global(loc) ;
#endif
    return return_info ;
  }

  std::vector<char> readBlockFromStream(std::istream& in) {
    in.unsetf(std::ios::skipws) ;
    in.seekg(0, std::ios::end) ;
    auto len = in.tellg();
    in.seekg(0, std::ios::beg) ;
    if(len > 0) {
      std::vector<char> infomation(len) ;
      in.read(&infomation[0], len) ;
      return infomation ;
    }
    return std::vector<char>() ;
  }

  std::string readFromStream(std::istream& in) {
    in.unsetf(std::ios::skipws) ;
    std::string return_info(std::istreambuf_iterator<char>(in.rdbuf()),
                            std::istreambuf_iterator<char>()) ;
    return return_info ;
  }
}
}

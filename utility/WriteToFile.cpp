/*
 * =====================================================================================
 *
 *       Filename:  WriteToFile.cpp
 *
 * =====================================================================================
 */
#include "webgame/utility/WriteToFile.h"

#include <cstdio>
#include <algorithm>
#include <functional>
#include <fstream>
#include <iostream>
#include <locale>
#include <stdexcept>

bool WebGame::Utility::writeToFile(const Utility::StringGroupType& infos, std::ostream& os) {
  try {
    std::for_each(infos.begin(), infos.end(), [&os](StringGroupType::const_reference v) {
        os << v << "\n";
        }) ;
    return true;
  }
  catch ( const std::exception &ExceptObj ) {		/* handle exception: */
    return false ;
  }
  catch (...) {		/* handle exception: unspecified */
    return false ;
  }
}

bool WebGame::Utility::writeToFile(const std::string& info, std::ostream& os) {

  try {
    os << info << std::endl ;
    return true ;
  }
  catch ( const std::exception &) {		/* handle exception: */
    return false ;
  }
  catch (...) {		/* handle exception: unspecified */
    return false ;
  }

}

bool WebGame::Utility::writeToFile(const Utility::StringGroupType& infos,
    const std::string& file_name,
    const std::string&
#ifdef WIN32

     locinfo
#endif
     ) {
#ifdef WIN32
  std::locale loc = std::locale::global(std::locale(locinfo.c_str())) ;
#endif
  std::ofstream outstream(file_name.c_str(), std::ios_base::out |
      std::ios_base::trunc) ;
  if(!outstream.is_open()) {
#ifdef WIN32
    std::locale::global(loc) ;
#endif
    return false ;
  }
  bool ok = writeToFile(infos, outstream) ;
#ifdef WIN32
  std::locale::global(loc) ;
#endif
  return ok ;
}


bool WebGame::Utility::writeToFile(const std::string& infos,
    const std::string& file_name,
    const std::string& locinfo) {
#ifdef WIN32
  std::locale loc = std::locale::global(std::locale(locinfo.c_str())) ;
#endif
  std::ofstream outstream(file_name.c_str(), std::ios_base::out |
      std::ios_base::trunc) ;
  if(!outstream.is_open()) {
#ifdef WIN32
    std::locale::global(loc) ;
#endif
    return false ;
  }
  bool ok = writeToFile(infos, outstream) ;
#ifdef WIN32
  std::locale::global(loc) ;
#endif
  return ok ;
}

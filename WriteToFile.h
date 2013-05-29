/*
 * =====================================================================================
 *
 *       Filename:  write_to_file.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-9-28 17:24:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *        Company:  GJY
 *
 * =====================================================================================
 */
#ifndef FND_UNTILITY_WRITE_TO_FILE_H
#define FND_UNTILITY_WRITE_TO_FILE_H
#include <iosfwd>
#include <string>
#include <vector>
namespace WebGame {
namespace Utility {
  typedef std::vector<std::string> StringGroupType ;
  bool writeToFile(const StringGroupType& infos, std::ostream& stream) ;
  bool writeToFile(const StringGroupType& infos, const std::string& file_name,
      const std::string& loc = std::string(".936")) ;
  bool writeToFile(const std::string& info, std::ostream& stream);
  bool writeToFile(const std::string& info, const std::string& filename,
      const std::string& loc = std::string(".936")) ;
}
}
#endif


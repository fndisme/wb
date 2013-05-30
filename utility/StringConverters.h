#ifndef FND_GAME_OT2_UTILITY_HPP
#define FND_GAME_OT2_UTILITY_HPP
#include <string>
namespace WebGame {
namespace Utility {
    std::wstring toWString(const char* pstr) ;
    std::string toString(const std::wstring& str) ;
    std::wstring toWString(const std::string& str) ;
    std::string gbkToUtf8(const std::string& str) ;
    std::string utf8ToGbk(const std::string& str) ;
} // end Utility
} // end WebGame
#endif

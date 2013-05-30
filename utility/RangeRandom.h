#ifndef FND_GAME_UTILITY_RANGE_RANDOM_H
#define FND_GAME_UTILITY_RANGE_RANDOM_H
#include <cstdlib>
#include	<boost/noncopyable.hpp>
namespace WebGame {
namespace Utility {
    int rangeRandom(int min_num, int max_num) ;
    double rangeRandom(double min_num, double min_max) ;
    class FixPoolRandom : boost::noncopyable {
      public:
      typedef FixPoolRandom class_type ;
      explicit FixPoolRandom(size_t seed) : m_seed(seed) {}
      double randomNumber() const ;
      inline
      double operator()()const { return randomNumber() ;}
      private:
      mutable size_t m_seed ;
    } ;
}
}
#endif

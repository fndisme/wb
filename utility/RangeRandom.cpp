#include "webgame/utility/RangeRandom.h"

#include <cassert>
#include <ctime>

#include	<vector>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
namespace WebGame {
namespace Utility {
  static boost::mt19937 gen(static_cast<boost::uint32_t>(std::time(0)));
  int rangeRandom(int min_num, int max_num) {
    assert(min_num < max_num) ;
    boost::uniform_int<> dist(min_num, max_num);
    boost::variate_generator<boost::mt19937&, boost::uniform_int<> > int_random(gen, dist);
    return int_random();

  }

  double rangeRandom(double min_num, double max_num) {
    assert(min_num < max_num) ;
    boost::uniform_real<> dist(min_num, max_num);
    boost::variate_generator<boost::mt19937&, boost::uniform_real<> > random(gen, dist);
    return random();
  }

  class FixPoolRandomCache: boost::noncopyable {
    public:
      static FixPoolRandomCache& instance() {
        static FixPoolRandomCache cache ;
        return cache ;
      }

      double randomNumber(size_t index) const {
        return m_pool[index%max_index_size] ;
      }

    private:
      enum { max_index_size = 1500 } ;
      FixPoolRandomCache() {
        m_pool.reserve(max_index_size) ;
        boost::mt19937 gen(1345) ;
        boost::uniform_real<> dist(0.0, 1.0) ;
        boost::variate_generator<boost::mt19937&, boost::uniform_real<> > r(gen, dist) ;
        for(size_t i = 0 ; i < max_index_size ; ++i) 
          m_pool.push_back(r()) ;
      }

      std::vector<double> m_pool ;

  } ;

  double FixPoolRandom::randomNumber() const {
    return FixPoolRandomCache::instance().randomNumber(m_seed++) ;
  }
}
}

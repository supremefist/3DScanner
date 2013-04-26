#include <boost/test/unit_test.hpp> 
#include <string.h>

BOOST_AUTO_TEST_SUITE( testPreprocessing )

BOOST_AUTO_TEST_CASE( testPreprocessingConstructor ) {
  std::string s("Hello");
  BOOST_CHECK_EQUAL(s.length(), 5);
}

BOOST_AUTO_TEST_SUITE_END()

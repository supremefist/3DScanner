//#define BOOST_TEST_MODULE preprocessing
#include <boost/test/unit_test.hpp> 
#include <string.h>

BOOST_AUTO_TEST_SUITE( test_preprocessing )

BOOST_AUTO_TEST_CASE( test_preprocessing_constructor ) {
  std::string s("Hello");
  BOOST_CHECK_EQUAL(s.length(), 5);
}

BOOST_AUTO_TEST_SUITE_END()

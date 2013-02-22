//#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE frame
#include <boost/test/unit_test.hpp> 
#include <string.h>

BOOST_AUTO_TEST_SUITE( test_frame )

BOOST_AUTO_TEST_CASE( test_frame_constructor ) {
  std::string s("Hello");
  BOOST_CHECK_EQUAL(s.length(), 5);
}

BOOST_AUTO_TEST_SUITE_END()

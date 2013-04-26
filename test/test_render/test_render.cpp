#include <boost/test/unit_test.hpp> 
#include <utils/frame_viewer/frame_viewer.h>

BOOST_AUTO_TEST_SUITE (testRender)

BOOST_AUTO_TEST_CASE( testSimpleRender ) {
  scanner::FrameViewer fr;


  fr.renderFrameFromFile("../data/test_data/ism_test_lioness.pcd");

}

BOOST_AUTO_TEST_SUITE_END()

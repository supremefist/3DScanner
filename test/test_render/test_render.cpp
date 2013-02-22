#include <boost/test/unit_test.hpp> 
#include <utils/frame_viewer/frame_viewer.h>

BOOST_AUTO_TEST_SUITE (test_render)

BOOST_AUTO_TEST_CASE( test_simple_render ) {
  scanner::FrameViewer fr;


  fr.renderPCD("../data/test_data/random.pcd");

}

BOOST_AUTO_TEST_SUITE_END()

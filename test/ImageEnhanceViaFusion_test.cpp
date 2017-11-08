
#define BOOST_TEST_DYN_LINK
//Define our Module name (prints at testing)
#define BOOST_TEST_MODULE "ImageEnhanceViaFusion_test"
//VERY IMPORTANT - include this last

#include <ImageEnhanceViaFusion.hpp>
#include <string>
#include <iostream>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test_suite.hpp>


#define PATH_DATASET "../dataset/"
#define FILE_NAME "img_%02d.jpg"

using namespace dehaze_undewater_image;

BOOST_AUTO_TEST_CASE(colorBalance_testcase) {

  std::string path_daset(PATH_DATASET);
  std::string file_name(FILE_NAME);

  std::cout << "DATASET PATH " << path_daset + file_name << std::endl;
  cv::VideoCapture capture(path_daset + file_name);

  while(capture.grab()){

      cv::Mat img;
      capture.retrieve(img);
      cv::imshow("out original" , img);
      img = colorBalance(img, 0.01);
      cv::imshow("out processed" , img);
      cv::waitKey();
  }

}


BOOST_AUTO_TEST_CASE(colorBalanceByChannel_testcase) {

  std::string path_daset(PATH_DATASET);
  std::string file_name(FILE_NAME);

  std::cout << "DATASET PATH " << path_daset + file_name << std::endl;
  cv::VideoCapture capture(path_daset + file_name);

  while(capture.grab()){

    cv::Mat img;
    capture.retrieve(img);
    cv::imshow("out original" , img);
    img = colorBalance(img, cv::Scalar(0.01,0.001,0.001));
    cv::imshow("out colorBalance " , img);

    cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE(2, cv::Size(4, 4));
    std::vector<cv::Mat> channels;
    cv::cvtColor(img, img, CV_BGR2HSV);
    cv::split(img, channels);
    clahe->apply(channels[2], channels[2]);
    // cv::equalizeHist(channels[2], channels[2]);
    cv::merge(channels, img);
    cv::cvtColor(img, img, CV_HSV2BGR);

    cv::imshow("out CLAHE " , img);

    cv::waitKey();
  }
}

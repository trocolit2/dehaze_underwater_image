#include "ImageEnhanceViaFusion.hpp"

#include <vector>
#include <iostream>


#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


namespace dehaze_undewater_image {

cv::Mat ImageEnhanceViaFusion::apply(cv::Mat image){


  return cv::Mat1b::zeros(500,500);
}


// percent should have values between 0.01 and 0.99
cv::Mat ImageEnhanceViaFusion::colorBalance(cv::Mat image, float percent){
  if (percent <= 0)
    percent = 0.001;
  else if( percent >= 1)
    percent = 0.99;

  int rows = image.rows;
  int cols = image.rows;

  std::vector<cv::Mat> channels;
  if(image.channels() == 3)
    cv::split(image, channels);
  else
    channels.push_back(image);

  for (size_t j = 0; j < channels.size(); j++) {
    cv::Mat flat = channels[j].reshape(1, 1).clone();
    // std::cout << " flat " << flat << std::endl;
    // std::cout << " flat SIZE " << flat.size() << std::endl;
    cv::sort(flat, flat, CV_SORT_ASCENDING);
    // std::cout << " sort flat " << flat << std::endl;

    int low_position = (int) flat.cols * percent;
    uchar low_value = flat.at<uchar>( 0, low_position);
    uchar top_value = flat.at<uchar>( 0, flat.cols - low_position );

    // std::cout << " LOW | TOP " << (int) low_value
    //                            << "| "
    //                            << (int) top_value << std::endl;

    for (size_t m = 0; m < rows; m++)
      for (size_t n = 0; n < cols; n++) {
        if( channels[j].at<uchar>(m, n) < low_value )
          channels[j].at<uchar>(m, n) = low_value;
        else if( channels[j].at<uchar>(m, n) > top_value )
          channels[j].at<uchar>(m, n) = top_value;
      }

    cv::normalize(channels[j], channels[j], 0, 255, cv::NORM_MINMAX);
  }

  if(image.channels() == 3)
    cv::merge(channels, image);
  else
    image = channels[0];

  return image;
}

}

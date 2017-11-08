#include "ImageEnhanceViaFusion.hpp"

#include <vector>
#include <iostream>


#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


namespace dehaze_undewater_image {


// percent should have values between 0.0001 and 0.05
cv::Mat colorBalance( cv::Mat image, const cv::Scalar& percent_channel ){

  std::vector<cv::Mat> channels;
  if(image.channels() == 3)
    cv::split(image, channels);
  else
    channels.push_back(image);

  for (size_t j = 0; j < channels.size(); j++) {
    cv::Mat flat = channels[j].reshape(1, 1).clone();
    cv::sort(flat, flat, CV_SORT_ASCENDING);

    int low_position = (int) flat.cols * percent_channel[j];
    uchar low_value = flat.at<uchar>( 0, low_position);
    uchar top_value = flat.at<uchar>( 0, flat.cols - low_position );

    for (size_t m = 0; m < channels[j].rows; m++)
      for (size_t n = 0; n < channels[j].cols; n++) {
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

cv::Mat colorBalance(cv::Mat image, float percent){
  cv::Scalar percent_channel(percent, percent, percent, 0);
  return colorBalance(image, percent_channel);
}

}

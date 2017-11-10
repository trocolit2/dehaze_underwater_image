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

AdaptativeColorBalance::AdaptativeColorBalance()
  : low_values_(cv::Scalar(128, 128, 128))
  , top_values_(cv::Scalar(128, 128, 128)){
}

AdaptativeColorBalance::AdaptativeColorBalance(
                                    cv::Scalar intial_low_value,
                                    cv::Scalar intial_top_value)
  : low_values_(cv::Scalar( intial_low_value[0],
                            intial_low_value[1],
                            intial_low_value[2]))
  , top_values_(cv::Scalar( intial_top_value[0],
                            intial_top_value[1],
                            intial_top_value[2])){
}


cv::Mat AdaptativeColorBalance::apply(  cv::Mat image,
                                        float clip_value,
                                        float learn_rate){

  std::vector<cv::Mat> channels;
  if(image.channels() == 3)
    cv::split(image, channels);
  else
    channels.push_back(image);

  // std::cout << "\nVALUES " << std::endl;

  for (size_t j = 0; j < channels.size(); j++) {
    cv::Mat flat = channels[j].reshape(1, 1).clone();
    cv::sort(flat, flat, CV_SORT_ASCENDING);

    int low_position = (int) flat.cols * clip_value;
    float low_value = (float) flat.at<uchar>( 0, low_position);
    float top_value = (float) flat.at<uchar>( 0, flat.cols - low_position );

    // std::cout << "LOW | TOP " << low_value << " | " << top_value << std::endl;

    float low_diff = low_value - low_values_[j];
    if(low_diff){
      if( low_diff < 0 )
        low_values_[j] -= learn_rate;
      else
        low_values_[j] += learn_rate;
    }

    float top_diff = top_value - top_values_[j];
    if(top_diff){
      if( top_diff < 0 )
        top_values_[j] -= learn_rate;
      else
        top_values_[j] += learn_rate;
    }

    for (int m = 0; m < channels[j].rows; m++)
      for (int n = 0; n < channels[j].cols; n++) {
        if( channels[j].at<uchar>(m, n) < (uchar) low_values_[j] )
          channels[j].at<uchar>(m, n) = (uchar) low_values_[j];
        else if( channels[j].at<uchar>(m, n) > (uchar) top_values_[j] )
          channels[j].at<uchar>(m, n) = (uchar) top_values_[j];
      }

    cv::normalize(channels[j], channels[j], 0, 255, cv::NORM_MINMAX);
  }

  if(image.channels() == 3)
    cv::merge(channels, image);
  else
    image = channels[0];

  return image;
}


} // end namespace dehaze_undewater_image

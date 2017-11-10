#ifndef DEHAZE_UNDEWATER_IMAGE_IMAGEENHANCEVIAFUSION_HPP_
#define DEHAZE_UNDEWATER_IMAGE_IMAGEENHANCEVIAFUSION_HPP_

#include <opencv2/core/core.hpp>

namespace dehaze_undewater_image {

cv::Mat colorBalance(cv::Mat image, float percent = 0.05);
cv::Mat colorBalance(cv::Mat image, const cv::Scalar& percent_channel);

class AdaptativeColorBalance {

public:
  AdaptativeColorBalance();
  AdaptativeColorBalance(cv::Scalar intial_low_value,
                         cv::Scalar intial_top_value);

  cv::Mat apply(cv::Mat image,
                float clip_value = 0.01,
                float learn_rate = 0.5);

private:
  cv::Scalar low_values_;
  cv::Scalar top_values_;
};

} // end namespace dehaze_undewater_image

#endif /* DEHAZE_UNDEWATER_IMAGE_IMAGEENHANCEVIAFUSION_HPP_ */

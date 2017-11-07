#ifndef DEHAZE_UNDEWATER_IMAGE_IMAGEENHANCEVIAFUSION_HPP_
#define DEHAZE_UNDEWATER_IMAGE_IMAGEENHANCEVIAFUSION_HPP_

#include <opencv2/core/core.hpp>

namespace dehaze_undewater_image {

class ImageEnhanceViaFusion {

public:
  static cv::Mat apply(cv::Mat image);
  static cv::Mat colorBalance(cv::Mat image, float percent = 0.05);


};

} // end namespace dehaze_undewater_image

#endif /* DEHAZE_UNDEWATER_IMAGE_IMAGEENHANCEVIAFUSION_HPP_ */

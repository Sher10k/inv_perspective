#ifndef INV_PERSPECTIVE_H
#define INV_PERSPECTIVE_H

// opencv
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
//#include <opencv2/calib3d.hpp>

/**
 * @brief inv_perspective
 * @param src       - input image
 * @param dst       - output image
 * @param mtx       - camera matrix [3x3]
 * @param dist      - distortion coefficients [1x5] = [ k1, k2, p1, p2, k3 ]
 * @param M         - perspective transformation matrix [3x3]
 * @param roi_left  - left border [ in meter ]
 * @param roi_right - right border [ in meter ]
 * @param length    - length [ in meter ]
 * @param scale     - scale output image [ N pix = 1 meter ]
 */

void inv_perspective( cv::Mat &src, 
                      cv::Mat &dst, 
                      cv::Mat mtx, 
                      cv::Mat dist,
                      cv::Mat M,
                      float roi_left,
                      float roi_right,
                      float length,
                      int scale );


#endif // INV_PERSPECTIVE_H

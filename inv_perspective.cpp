#include "inv_perspective.h"

void inv_perspective( cv::Mat &src, 
                      cv::Mat &dst, 
                      cv::Mat mtx, 
                      cv::Mat dist,
                      cv::Mat M,
                      float roi_left,
                      float roi_right,
                      float length,
                      float shift,
                      int scale )
{
    // --- Check matrix dimensions & value of variables 
    roi_left = (roi_left > 0.0f) ? roi_left : (-1.0f) * roi_left;
    roi_right = (roi_right > 0.0f) ? roi_right : (-1.0f) * roi_right;
    length = (length > 0.0f) ? length : (-1.0f) * length;
    scale = (scale > 0) ? scale : (-1) * scale;
    
    // --- Undistort image
    cv::Mat img_undist;
    cv::undistort( src, img_undist, mtx, dist, cv::noArray() );
    
    // --- Perspective transformation to an image.
    float scale_default = 20.0f;
    float length_default = 21.28f;
    float roi_left_default = 10.0f;
    float roi_right_default = 10.0f;    
    int width_warp = int( scale_default * (roi_left_default + roi_right_default) );
    int height_warp = int( scale_default * length_default );
    cv::warpPerspective( img_undist, dst, M, cv::Size(width_warp, height_warp) );
    
    // --- Transform output image
    int width = int( scale_default * (roi_left + roi_right) );
    int height = int( scale_default * length );
    int offsetx = int( scale_default * ( roi_left - roi_left_default ) );
    int offsety = int( scale_default * ( length - length_default - shift ) );
    cv::Mat trans_mat = ( cv::Mat_<double>(2,3) << 1, 0, offsetx, 0, 1, offsety );
    cv::warpAffine( dst, dst, trans_mat, cv::Size(width, height) );
    
    // --- Image scaling
    cv::resize( dst, dst, dst.size() * scale, 0, 0, cv::INTER_LINEAR );
}

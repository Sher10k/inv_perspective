#include "inv_perspective.h"

void inv_perspective( cv::Mat &src, 
                      cv::Mat &dst, 
                      cv::Mat mtx, 
                      cv::Mat dist,
                      cv::Mat M,
                      float roi_left,
                      float roi_right,
                      float length,
                      int scale )
{
    // --- Check matrix dimensions & value of variables 
    roi_left = (roi_left > 0.0f) ? roi_left : (-1.0f) * roi_left;
    roi_right = (roi_right > 0.0f) ? roi_right : (-1.0f) * roi_right;
    length = (length > 0.0f) ? length : (-1.0f) * length;
    scale = (scale > 0) ? scale : (-1) * scale;
    
    // W x H - output image
    int width = int( scale * (roi_left + roi_right) );
    int height = int( scale * length );
    
    if (dst.empty()) dst = cv::Mat::zeros( cv::Size(width, height), CV_8UC3 );
    else cv::resize( dst, dst, cv::Size(width, height), 0, 0, cv::INTER_LINEAR );
    
    
}

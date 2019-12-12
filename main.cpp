#include <iostream>

#include "inv_perspective.h"

// opencv
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
//#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
//#include <opencv2/calib3d.hpp>

using namespace std;
using namespace cv;

int main( int argc, char *argv[] )  // int argc, char *argv[]
{
    // --config=cfg/config.yaml
    /*** READ CONFGURATION ***/
    const cv::String keys =
        "{help h usage ? |             | print this message   }"
        "{config         |config.yaml  | path to config       }"
        ;

    cv::CommandLineParser parser(argc, argv, keys);
    parser.about("invert perspective");
    if (parser.has("help"))
    {
        parser.printMessage();
        return 0;
    }
    std::string filename = parser.get< cv::String >("config");
    std::cout << "Configuration file is " << filename << "\n";
    
    // --- Open config file
    cv::FileStorage fs( filename, cv::FileStorage::READ );
    fs.open( filename, cv::FileStorage::READ );
    
    // --- Read config
    Mat mtx, dist, M;
    float roi_left, roi_right, length, shift;
    int scale;
    fs["mtx"] >> mtx;
    fs["dist"] >> dist;
    fs["M"] >> M;
    roi_left = -10.0;
    roi_right = 10.0;
    length = 20.0;
    shift = 0;//1.52f;
    scale = 2;
    cout << "mtx = " << endl << mtx << endl;
    cout << "dist = " << endl << dist << endl;
    cout << "M = " << endl << M << endl;
    cout << "roi_left = " << roi_left << endl;
    cout << "roi_right = " << roi_right << endl;
    cout << "length = " << length << endl;
    cout << "shift = " << shift << endl;
    cout << "scale = " << scale << endl;
    
    // --- Read image
    Mat img_in, img_out;
    img_in = imread( "frame_front_1.png", IMREAD_COLOR );
    //img_in = imread( "frame_back_1.jpg", IMREAD_COLOR );
    
    inv_perspective( img_in, img_out, mtx, dist, M, roi_left, roi_right, length, shift, scale );
    
    // --- Show image
    resize( img_in, img_in, Size(480, 720), 0, 0, INTER_LINEAR );
    imshow( "input", img_in );
    imshow( "output", img_out );
    
    // --- Close config file
    fs.release();
    int key = 0;
    while( key != 'q' && key != 'Q' )
    {
        key = waitKey(0);
    }
    
    
    return 0;
}

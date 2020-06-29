#ifndef _OPERATION_HPP
#define _OPERATION_HPP


/*Include Library*/
#include <iostream>
#include <string>
#include <cmath>
#include <opencv2/opencv.hpp>

/*static*/

const bool vertical = true;
const bool horizontal = false;

/*Class*/
class Operation {
    public:
        cv::Mat img_src;
        cv::Mat img_dst;
        cv::Mat op;

        Operation(std::string input_path);
        ~Operation();
        void set(float num = 1.0);
        void smoothing(std::string file_dst);
        void weightedAverage(std::string file_dst);
        void differential(std::string file_dst, bool Vertical);
        void sobel(std::string file_dst, bool Vertical);
        void laplacian(std::string file_dst);
        void sharpen(std::string file_dst);

    private:
        void filtering(std::string file_dst);
};

#endif // !_OPERATION_HPP

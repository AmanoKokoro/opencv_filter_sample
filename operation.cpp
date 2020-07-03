#include <string>
#include "operation.hpp"

using namespace std;
using namespace cv;

Operation::Operation(string input_path) {
    img_src = imread(input_path, 1);

    if (!img_src.data) {
        throw runtime_error("Input error!!");
	} // F_open
}

Operation::~Operation() {

}

void Operation::set_ones(float num) {
    op = Mat::ones(3, 3, CV_32F) / num;	//全要素が1の3*3フィルタを生成
}

void Operation::set_zeros(){
    op = Mat::zeros(3, 3, CV_32F);	//全要素が0の3*3フィルタを生成
}

void Operation::smoothing(string file_dst) {
    set_ones(9);
    filtering(file_dst);
}

void Operation::weightedAverage(string file_dst) {
    set_ones(16);
    op.at<float>(1,1) = 4/16.0;
    op.at<float>(1,0) = 2/16.0;
    op.at<float>(0,1) = 2/16.0;
    op.at<float>(2,1) = 2/16.0;
    op.at<float>(1,2) = 2/16.0;

    filtering(file_dst);
}

void Operation::differential(string file_dst, bool Vertical) {
    set_zeros();

    if (Vertical == true) {
        op.at<float>(1,1) = -1;
        op.at<float>(1,2) = 1;

    } else if(Vertical == false) {
        op.at<float>(1,1) = -1;
        op.at<float>(2,1) = 1;

    } else {
        cout << "error\n";
    }

    filtering(file_dst);
}

void Operation::sobel(string file_dst, bool Vertical) {
    set_zeros();

    if (Vertical == true) {
        op.at<float>(0, 0) = 1;
        op.at<float>(0, 1) = 2;
        op.at<float>(0, 2) = 1;
        op.at<float>(2, 0) = -1;
        op.at<float>(2, 1) = -2;
        op.at<float>(2, 2) = -1;

    } else if (Vertical == false) {
        op.at<float>(0, 0) = -1;
        op.at<float>(1, 0) = -2;
        op.at<float>(2, 0) = -1;
        op.at<float>(0, 2) = 1;
        op.at<float>(1, 2) = 2;
        op.at<float>(2, 2) = 1;

    } else {
        cout << "error\n";
    }

    filtering(file_dst);
}

void Operation::laplacian(string file_dst) {
    set_ones();
    op.at<float>(1, 1) = -8;
    filtering(file_dst);
}

void Operation::sharpen(string file_dst) {
    float k = 1/(-5.0);
    set_ones(k);
    filtering(file_dst);
}

void Operation::filtering(string file_dst) {
    filter2D(img_src, img_dst, -1, op);
    convertScaleAbs(img_dst, img_dst, 1, 0);
    imwrite(file_dst, img_dst);
}
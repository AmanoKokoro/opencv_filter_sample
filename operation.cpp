#include <string>
#include "operation.hpp"

using namespace std;
using namespace cv;

Operation::Operation(string input_path) {
    img_src = imread(input_path, 1);

    if (!img_src.data) {
        throw runtime_error("Input error!!");
	}

    set();
}

Operation::~Operation() {

}

void Operation::set(float num) {
    op = Mat::ones(3, 3, CV_32F) / 9.0 * num;	//全要素が1の3*3フィルタを生成 9で割る (全要素が1/9の3*3行列)
}

void Operation::smoothing(string file_dst) {
    set();
    filtering(file_dst);
}

void Operation::weightedAverage(string file_dst) {
    set();
    op.at<float>(1,1) = 4/16.0;
    op.at<float>(1,0) = 2/16.0;
    op.at<float>(0,1) = 2/16.0;
    op.at<float>(2,1) = 2/16.0;
    op.at<float>(1,2) = 2/16.0;

    filtering(file_dst);
}

void Operation::differential(string file_dst, bool Vertical) {
    set();

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
    set(); 

    if (Vertical == true) {
        op.at<float>(0, 0) = -1;
        op.at<float>(0, 1) = -2;
        op.at<float>(0, 2) = -1;
        op.at<float>(2, 0) = 1;
        op.at<float>(2, 1) = 2;
        op.at<float>(2, 2) = 1;

    } else if (Vertical == false) {
        op.at<float>(0, 0) = -1;
        op.at<float>(1, 0) = -2;
        op.at<float>(2, 0) = -2;
        op.at<float>(0, 2) = 1;
        op.at<float>(1, 2) = 2;
        op.at<float>(2, 2) = 0;

    } else {
        cout << "error\n";
    }

    filtering(file_dst);
}

void Operation::laplacian(string file_dst) {
    set();
    op.at<float>(1, 1) = -8;
    filtering(file_dst);
}

void Operation::sharpen(string file_dst) {
    float k = 5.0;
    set(k);
    filtering(file_dst);
}

void Operation::filtering(string file_dst) {
    filter2D(img_src, img_dst, -1, op);
    convertScaleAbs(img_dst, img_dst, 1, 0);
    imwrite(file_dst, img_dst);
}
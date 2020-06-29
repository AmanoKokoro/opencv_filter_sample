#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINE

#include "main.hpp"

//Name space
using namespace cv;
using namespace std;

int main(void) {
    string file_src = "img/hoge.jpg";	//input image path

    //Output Image files
    string file_sm = "img/smoothing.jpg";	//output_image path
    string file_we = "img/weightedAverage.jpg";	//output_image path
    string file_di_vertical = "img/di_Vertical.jpg";	//output_image path
    string file_di_horizontal = "img/di_Horizontal.jpg";	//output_image path
    string file_so_vertical = "img/so_Vertical.jpg";	//output_image path
    string file_so_horizontal = "img/so_Horizontal.jpg";	//output_image path
    string file_la = "img/laplacian.jpg";	//output_image path
    string file_sh = "img/sharpen.jpg";	//output_image path

    //インスタンス生成
    Operation* opr = 0;
    opr = new Operation(file_src);

    opr->smoothing(file_sm);
    opr->weightedAverage(file_we);
    opr->differential(file_di_vertical, vertical);
    opr->differential(file_di_horizontal, horizontal);
    opr->sobel(file_so_vertical, vertical);
    opr->sobel(file_so_horizontal, horizontal);
    opr->laplacian(file_la);
    opr->sharpen(file_sh);

    return 0;
}
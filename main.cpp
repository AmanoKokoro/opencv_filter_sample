#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINE

#include "main.hpp"

//Name space
using namespace cv;
using namespace std;

// global
string win_src = "src";
string win_dst = "dst";

int main(void) {
	string file_src = "img/hoge.jpg";	//input image path
	string file_dst = "img/foobar.jpg";	//output_image path

	Mat img_src = imread(file_src, 1);		//カラー画像として入力
	//Mat img_src = imread(file_src, 0);	//0でグレースケール

	Mat img_dst;	//画像処理オブジェクト
	
	/*ファイルオープンチェック*/
	if (!img_src.data) {
		cout << "Input error!!" << endl;
		return -1;
	}

	namedWindow(win_src, WINDOW_AUTOSIZE);	//input image window
	namedWindow(win_dst, WINDOW_AUTOSIZE);	//output image window

	/*Operation*/
	Mat op = Mat::ones(3, 3, CV_32F) / 9.0;	//全要素が1の3*3フィルタを生成 9で割る (全要素が1/9の3*3行列)

	/*edgefilter*/
	op.at<float>(1, 1) = -1;
	op.at<float>(1, 2) = 1;
	

	filter2D(img_src, img_dst, -1, op);
	convertScaleAbs(img_dst, img_dst, 1, 0);

	imshow(win_src, img_src);
	imshow(win_dst, img_dst);

	imwrite(file_dst, img_dst);
	waitKey(-1);

	return 0;
}
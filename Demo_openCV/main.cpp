#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char **argv) {
  // 加载图片
  Mat src = imread("./picture01.jpg");
  if (src.empty()) {
    cout << "Could not load image!" << endl;
    return -1;
  }

  // 调整图像大小以适应预览
  Mat resized;
  float scale = 640.0 / src.cols; // 假设我们想要的宽度是640
  resize(src, resized, Size(640, src.rows * scale), 0, 0, INTER_LINEAR);

  // 图像处理
  Mat gray, binary;
  cvtColor(resized, gray, COLOR_BGR2GRAY);
  threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);

  // 物体检测
  vector<vector<Point>> contours;
  vector<Vec4i> hierarchy;
  findContours(binary, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE,
               Point());

  // 绘制轮廓
  Mat result(resized.size(), CV_8U, Scalar(255));
  drawContours(result, contours, -1, Scalar(0), 2);

  // 显示结果
  imshow("Result", result);
  waitKey(0);

  return 0;
}

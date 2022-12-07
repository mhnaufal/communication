#include "message.hpp"

int main()
{
  std::string tag = "tag";
  const std::time_t now = std::time(nullptr);
  std::string text = "pack_this!";

  auto img = cv::imread("../img1.jpg", cv::IMREAD_COLOR);
  //  cv::Mat img = cv::Mat(2, 2, CV_8UC3, cv::Scalar(126, 0, 255));

  Message m1;
  m1.tag = tag;
  m1.time = now;
  m1.text = text;
  // NOTE: see this F*CK
  m1.img = std::vector<uchar>(
      img.data, img.data + (img.rows * img.cols * img.channels()));

  std::cout << "[REAL] " << m1.tag << " " << m1.time << " " << m1.text << " "
            << img << " ";
  for (auto item : m1.img) std::cout << item << std::endl;



  return EXIT_SUCCESS;
}
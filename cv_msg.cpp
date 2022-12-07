#include "message.hpp"

int main()
{
  /* prepare data */
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
            << img.empty() << std::endl;
  //  for (auto item : m1.img) std::cout << item << std::endl;

  /* packing data */
  msgpack::sbuffer packed_data;
  msgpack::pack(&packed_data, m1);

  std::cout << "[PACKED] " << packed_data.data() << " || " << packed_data.size()
            << std::endl;

  /* unpacking data */
  msgpack::unpacked unpacked_data;
  msgpack::unpack(unpacked_data, static_cast<const char*>(packed_data.data()),
                  packed_data.size());

  auto returned_data = unpacked_data.get().convert(m1);
  std::cout << "[UNPACKED] " << unpacked_data.get() << " || "
            << returned_data.tag << " || " << returned_data.time << " || "
            << returned_data.text << returned_data.img.empty() << std::endl;

  //  auto ss = cv::Mat(2, 2, CV_8UC3, cv::Scalar(126, 0, 255));
  //  auto new_img = std::vector<uchar>(
  //      ss.data, ss.data + (ss.rows * ss.cols * ss.channels()));

  auto new_img = returned_data.img;
  bool is_equal = cv::countNonZero(new_img != m1.img) == 0;

  if (is_equal)
    std::cout << "IT'S THE SAME!" << std::endl;
  else
    std::cout << "FUCKING DIFFERENT!!!" << std::endl;

  return EXIT_SUCCESS;
}
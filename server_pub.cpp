#include <chrono>
#include <iostream>
#include <msgpack.hpp>
#include <mutex>
#include <opencv2/dnn.hpp>
#include <opencv2/dnn/all_layers.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <thread>
#include <zmq.hpp>
#include <zmq_addon.hpp>

int main()
{
  using namespace std::chrono_literals;

  void* context = zmq_ctx_new();
  void* publisher = zmq_socket(context, ZMQ_PUB);
  int bind = zmq_bind(publisher, "ipc:///home/fr13nds/temp/ipc/pubsubmul.sock");
  std::cout << "prepare socket... " << bind << std::endl;

  //  cv::Mat img = cv::imread("../img1.jpg", cv::IMREAD_COLOR);
  cv::Mat img = cv::Mat{1, 2, 3};
  uint32_t height = img.rows;
  uint32_t width = img.cols;

  std::vector<uchar> buffer;
  cv::imencode(".jpg", img, buffer);
  std::cout << "prepare data..." << std::endl;

  while (true) {
    zmq_send(publisher, buffer.data(), buffer.size(), ZMQ_NOBLOCK);
    std::this_thread::sleep_for(2s);
    std::cout << "send data..." << std::endl;
  }

  return EXIT_SUCCESS;
}

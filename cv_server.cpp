#include <chrono>
#include <ctime>
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
#include "message.hpp"

using namespace std::chrono_literals;

template <typename T>
void sendResponse(zmq::socket_t& socket, const std::string& tag, const T& data)
{
  msgpack::sbuffer packed_data;
  msgpack::pack(&packed_data, data);

  zmq::message_t tag_msg(tag.size());
  std::memcpy(tag_msg.data(), tag.data(), tag.size());

  zmq::message_t body_msg(packed_data.size());
  std::memcpy(body_msg.data(), packed_data.data(), packed_data.size());

  std::cout << "publish... " << body_msg << std::endl;

  //  socket.send(tag_msg, zmq::send_flags::sndmore);
  socket.send(body_msg, zmq::send_flags::none);
}

int main()
{
  zmq::context_t ctx{1};
  zmq::socket_t server{ctx, zmq::socket_type::rep};
  server.bind("ipc:///home/fr13nds/temp/ipc/cv.sock");

  const std::string tag = "tag";

  while (true) {
    zmq::message_t req;

    server.recv(req, zmq::recv_flags::none);
    std::cout << "process 1 " << req.to_string() << std::endl;

    const std::time_t now = std::time(nullptr);

    Message msg1;
    msg1.tag = tag;
    msg1.time = now;
    msg1.text = "[publish from the server]";

    sendResponse(server, tag, msg1);
    std::this_thread::sleep_for(2s);
  }

  return EXIT_SUCCESS;
}

/*##############################################################*/
//template <typename T>
//using unique_vector = std::unique_ptr<std::vector<T>>;
//
//std::vector<uchar> parseMsg(zmq::message_t& msg)
//{
//  uint32_t size = 0;
//  msg.size() >> size;
//
//  std::vector<uchar> buffer(size);
//  auto img = (uchar*)msg.data();
//  std::vector<uchar> data_vec(img, img + size);
//  return data_vec;
//}
//
//cv::Mat recvDecode(zmq::socket_t& socket)
//{
//  zmq::message_t msg;
//  socket.recv(msg);
//  auto data = parseMsg(msg);
//
//  return cv::imdecode(data, cv::IMREAD_COLOR);
//}

//int main()
//{
//  using namespace std::chrono_literals;
//
//  zmq::context_t ctx{1};
//  zmq::socket_t server(ctx, zmq::socket_type::rep);
//  server.bind("ipc:///home/fr13nds/temp/ipc/cv.sock");
//
//  auto img = cv::imread("../img1.jpg", cv::IMREAD_COLOR);
//  std::vector<uchar> buffer;
//  auto data = cv::imencode(".jpg", img, buffer);
//
//  while (true) {
//    zmq::message_t mat(buffer);
//    server.send(mat, zmq::send_flags::sndmore);
////    std::cout << mat << std::endl;
//
//    std::this_thread::sleep_for(2s);
//  }
//
//  return EXIT_SUCCESS;
//}

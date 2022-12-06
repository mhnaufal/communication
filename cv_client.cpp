#include <unistd.h>
#include <array>
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

template <typename T>
void sendRequest(zmq::socket_t& socket, T& data)
{
  zmq::message_t tag_msg, body_msg;

  auto tag_msg_res = socket.recv(tag_msg, zmq::recv_flags::none);
  auto body_msg_res = socket.recv(body_msg, zmq::recv_flags::none);

  std::cout << "received.. " << body_msg << " " << body_msg_res.value()
            << " || ";

  const std::string tag(static_cast<const char*>(tag_msg.data()),
                        tag_msg.size());

  msgpack::unpacked unpacked_body;
  msgpack::unpack(unpacked_body, static_cast<const char*>(body_msg.data()),
                  body_msg.size());
  unpacked_body.get().convert(data);
}

int main()
{
  zmq::context_t ctx{1};
  zmq::socket_t client{ctx, zmq::socket_type::req};
  client.connect("ipc:///home/fr13nds/temp/ipc/cv.sock");

  //  const std::string tag = "tag";
  const std::string data{"client 👁"};

  while (true) {
    std::cout << "sending request..." << std::endl;
    client.send(zmq::buffer(data), zmq::send_flags::none);

    /*response*/
    Message msg1;
    zmq::message_t reply;
    msgpack::unpacked unpacked_body;

    client.recv(reply, zmq::recv_flags::none);
    msgpack::unpack(unpacked_body, static_cast<const char*>(reply.data()),
                    reply.size());
    unpacked_body.get().convert(msg1);

    std::cout << "received response: " << reply << " || " << msg1.time << "[ "
              << msg1.tag << " ] ==> " << msg1.text << std::endl;
  }

  return EXIT_SUCCESS;
}

/*########################################################*/
//int main()
//{
//  zmq::context_t ctx{1};
//  zmq::socket_t client(ctx, zmq::socket_type::req);
//  client.connect("ipc:///home/fr13nds/temp/ipc/cv.sock");
//
//  const std::string data{"from client 👁"};
//
//  for (auto request_num = 0; request_num < 10; ++request_num) {
//    std::cout << "sending request...-" << request_num << std::endl;
//    client.send(zmq::buffer(data), zmq::send_flags::none);
//
//    zmq::message_t reply{};
//    client.recv(reply, zmq::recv_flags::none);
//
//    //    change the reply data format
//    std::cout << "received response: " << reply.to_string() << std::endl;
//  }
//
//  return EXIT_SUCCESS;
//}
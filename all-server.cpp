#include "message.hpp"

int main()
{
  using namespace std::chrono_literals;

  zmq::context_t ctx{1};
  zmq::socket_t server{ctx, zmq::socket_type::rep};
  server.bind("ipc:///home/fr13nds/temp/ipc/all.sock");

  auto img = cv::imread("../img1.jpg", cv::IMREAD_COLOR);

  while (1) {
    const std::time_t now = std::time(nullptr);
    /* open for requests */
    std::cout << "open for request..." << std::endl;
    zmq::message_t req;
    server.recv(req, zmq::recv_flags::none);
    std::cout << "[⚡ got request] => " << req.to_string() << std::endl;

    /* prepare reply data */
    Message msg_reply;
    msg_reply.tag = "ALL";
    msg_reply.time = now;
    msg_reply.text = "I replied with cv::Mat";
    msg_reply.img = std::vector<uchar>(
        img.data, img.data + (img.rows * img.cols * img.channels()));

    /* packed the reply data using msgpack */
    msgpack::sbuffer packed_reply;
    msgpack::pack(&packed_reply, msg_reply);

    /* serialize the packed reply data using zeromq */
    zmq::message_t packed_msg(packed_reply.size());
    std::memcpy(packed_msg.data(), packed_reply.data(), packed_reply.size());
    server.send(packed_msg, zmq::send_flags::none);

    std::this_thread::sleep_for(2s);
  }

  return EXIT_SUCCESS;
}

#include "message.hpp"

int main()
{
  zmq::context_t ctx{1};
  zmq::socket_t client{ctx, zmq::socket_type::req};
  client.connect("ipc:///home/fr13nds/temp/ipc/all.sock");

  const std::string req_data{"I ask for a reply"};

  while (true) {
    /* send request */
    std::cout << "sending request... " << std::endl;
    client.send(zmq::buffer(req_data), zmq::send_flags::none);

    /* catch reply message */
    zmq::message_t reply_msg;
    auto what_is_this = client.recv(reply_msg, zmq::recv_flags::none);
    std::cout << "[⚓ replied msg] => " << reply_msg << " => "
              << what_is_this.value() << std::endl;

    //// get type helper
    Message m1;
    //// get type helper

    /* deserialize the reply message */
    msgpack::unpacked unpacked_reply_msg;
    msgpack::unpack(unpacked_reply_msg,
                    static_cast<const char*>(reply_msg.data()),
                    reply_msg.size());
    auto unpacked_reply_data = unpacked_reply_msg.get().as<Message>();
    auto unpacked_reply_data_2 = unpacked_reply_msg.get().convert(m1);
    std::cout << "[⚓ replied data] => " << unpacked_reply_msg.get() << " => "
              << unpacked_reply_data.tag << " || " << unpacked_reply_data.time
              << " || " << unpacked_reply_data.text << " || "
              << unpacked_reply_data.img.size() << std::endl;

    //// DELETED?
    /* return back the vector<uchar> to cv::Mat image */
    cv::imshow(
        "GGWP",
        cv::Mat(unpacked_reply_data.height, unpacked_reply_data.width,
                unpacked_reply_data.type, unpacked_reply_data.img.data()));
    if (cv::waitKey(0) == 'c') return 0;
    getchar();
    cv::destroyAllWindows();
    //// DELETED?
  }

  return EXIT_SUCCESS;
}

#include "message.hpp"

int main()
{
  zmq::context_t ctx{1};
  zmq::socket_t client{ctx, zmq::socket_type::req};
  client.connect("ipc:///home/fr13nds/temp/ipc/all.sock");

  const std::string req_data{"I ask for a reply"};

  while (1) {
    /* send request */
    std::cout << "sending request... " << std::endl;
    client.send(zmq::buffer(req_data), zmq::send_flags::none);

    /* catch reply message */
    zmq::message_t reply_msg;
    auto what_is_this = client.recv(reply_msg, zmq::recv_flags::none);
    std::cout << "[⚓ replied msg] => " << reply_msg << " => "
              << what_is_this.value() << std::endl;

    //
    Message m1;
    //

    /* deserialize the reply message */
    msgpack::unpacked unpacked_reply_msg;
    msgpack::unpack(unpacked_reply_msg,
                    static_cast<const char*>(reply_msg.data()),
                    reply_msg.size());
    auto unpacked_reply_data = unpacked_reply_msg.get().convert(m1);
    std::cout << "[⚓ replied data] => " << unpacked_reply_msg.get() << " => "
              << unpacked_reply_data.tag << " || " << unpacked_reply_data.time
              << " || " << unpacked_reply_data.text << " || "
              << unpacked_reply_data.img.size() << std::endl;
  }

  return EXIT_SUCCESS;
}

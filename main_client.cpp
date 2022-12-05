#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <zmq.hpp>

int main()
{
  using namespace std::chrono_literals;

  // initialize zmq context
  zmq::context_t context{1};

  // construct a reply socket and bind to interface
  zmq::socket_t socket{context, zmq::socket_type::req};
  // socket.connect("tcp://localhost:5555"); // connect to nge-connect ke open connection
  socket.connect("ipc:///home/fr13nds/temp/ipc/hole.sock"); // connect to nge-connect ke open connection

  // prepare request data
  const std::string data{"client 👁"};

  for (auto request_num = 0; request_num < 10; ++request_num) {
    // send the request message
    std::cout << "sending request..." << request_num << std::endl;
    socket.send(zmq::buffer(data), zmq::send_flags::none);

    // wait for reply server
    zmq::message_t reply{};
    socket.recv(reply, zmq::recv_flags::none);

    std::cout << "received response: " << reply.to_string() << std::endl;
  }

  return 0;
}
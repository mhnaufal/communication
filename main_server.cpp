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
  zmq::socket_t socket{context, zmq::socket_type::rep};
  socket.bind("tcp://*:5555"); // bind untuk buka connection

  // prepare response data
  const std::string data{"[server]"};

  for (;;) {
    zmq::message_t request;

    // receive a request from client
    socket.recv(request, zmq::recv_flags::none);
    std::cout << "received request: " << request.to_string() << std::endl;

    // BUSINESS PROCESS
    std::this_thread::sleep_for(2s);

    // send reply to client
    socket.send(zmq::buffer(data), zmq::send_flags::none);
  }

  return 0;
}
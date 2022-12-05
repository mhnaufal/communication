#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <zmq.hpp>

int main()
{
  using namespace std::chrono_literals;

  zmq::context_t context{1};

  zmq::socket_t socket{context, zmq::socket_type::rep};
  socket.bind("ipc:///home/fr13nds/temp/ipc/hole.sock");

  const std::string data{"process 1"};

  while (true) {
    zmq::message_t req;

    socket.recv(req, zmq::recv_flags::none);
    std::cout << "process 1 " << req.to_string() << std::endl;

    std::this_thread::sleep_for(2s);

    socket.send(zmq::buffer(data), zmq::send_flags::none);
  }

  return EXIT_SUCCESS;
}
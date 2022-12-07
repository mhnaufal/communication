#ifndef THREAD_MESSAGE_HPP
#define THREAD_MESSAGE_HPP

#include <chrono>
#include <ctime>
#include <iostream>
#include <msgpack.hpp>
#include <mutex>
#include <opencv2/core.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/dnn/all_layers.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <thread>
#include <zmq.hpp>
#include <zmq_addon.hpp>

struct Message {
  std::string tag;
  std::time_t time{};
  std::string text;
  std::vector<uchar> img;
  MSGPACK_DEFINE(tag, time, text, img);
};

#endif  //THREAD_MESSAGE_HPP

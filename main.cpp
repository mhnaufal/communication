#include <chrono>
#include <iostream>
#include <thread>

static bool is_finish = false;

void printLog()
{
  using namespace std::literals::chrono_literals;

  while (!is_finish) {
    auto start_time = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(1s);
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end_time - start_time;

    std::cout << "[INFO] running on thread " << std::this_thread::get_id()
              << " on sec: " << duration.count() << std::endl;
  }

  std::cout << "[DEBUG] thread " << std::this_thread::get_id() << " finished"
            << std::endl;
}

int main()
{
  std::thread worker_1(printLog);
  std::cout << worker_1.get_id() << std::endl;

  std::cin.get();
  is_finish = true;

  worker_1.join();  // force the "main thread" to wait until the worker_1
                    // thread finished

  return 0;
}
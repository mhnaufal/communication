#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;

void printPattern(char c)
{
  std::unique_lock<std::mutex> lock(mtx);
  for (int i = 0; i < 10; ++i) {
    std::cout << c;
  }
  std::cout << std::endl;
}

int main()
{
  std::thread th1(printPattern, 'X');
  std::thread th2(printPattern, '0');

  th1.join();
  th2.join();
  return 0;
}
# C++ Threading

## Thread

1. **Program** = a running code + data
2. **Process** = a running program, one program can have multiple processes
3. **Thread** = a unit of execution inside a process, one process can have multiple threads
4. **Join** = the same as wait, block current thread until this other thread had completed

## IPC/RPC

1. **Shared memory** = create a special memory region that ack as the memory region lake. when a process want to
   share some data, it just need make a write to the memory region, and the same thing goes when other process wants
   to read data from the memory
2. **Message passing** = when process A wants to share data to process B, process A calls the system kernel to
   passing the data to process B
3. **Socket** = A socket is an endpoint of communication to which a name can be bound
4. **Semaphore** = Semaphores let processes query or alter status information
5. **Message passing** = message-passing module a message onto a queue which can be read by another process

## ZeroMQ

zeromq operate the IPC/RPC through socket

1. Download the two header-only libs
2. Copy-paste to **/usr/include/** and **/usr/local/include**
3. add `target_link_libraries(${PROJECT_NAME} zmq)` to CMake

## Credits

1. https://www.youtube.com/results?search_query=c%2B%2B+thread
2. https://www.educba.com/c-plus-plus-thread/
3. https://en.cppreference.com/w/cpp/thread/thread
4. https://cplusplus.com/reference/future/

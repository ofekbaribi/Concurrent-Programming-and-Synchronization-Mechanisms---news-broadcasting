#ifndef BOUNDED_BUFFER_H
#define BOUNDED_BUFFER_H

#include <queue>
#include <string>
#include <mutex>
#include <condition_variable>

class BoundedBuffer {
private:
    std::queue<std::string> buffer;
    std::mutex mtx;
    std::condition_variable not_full;
    std::condition_variable not_empty;
    int max_size;

public:
    BoundedBuffer(int size);
    void insert(const std::string& item);
    std::string remove();
};

#endif // BOUNDED_BUFFER_H

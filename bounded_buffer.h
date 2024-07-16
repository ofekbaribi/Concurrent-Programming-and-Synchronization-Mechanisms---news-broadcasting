#ifndef BOUNDED_BUFFER_H
#define BOUNDED_BUFFER_H

#include <mutex>
#include <queue>
#include <string>
#include <semaphore.h>

class BoundedBuffer {
public:
BoundedBuffer(int size);
~BoundedBuffer();
void insert(const std::string& item);
std::string remove();

private:
int maxSize;
std::queue<std::string> buffer;
std::mutex mtx;
sem_t emptySlots;
sem_t fullSlots;
};

#endif // BOUNDED_BUFFER_H
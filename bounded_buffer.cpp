#include "bounded_buffer.h"

BoundedBuffer::BoundedBuffer(int size) : max_size(size) {}

void BoundedBuffer::insert(const std::string& item) {
    std::unique_lock<std::mutex> lock(mtx);
    not_full.wait(lock, [this]() { return buffer.size() < static_cast<size_t>(max_size); });
    buffer.push(item);
    not_empty.notify_one();
}

std::string BoundedBuffer::remove() {
    std::unique_lock<std::mutex> lock(mtx);
    not_empty.wait(lock, [this]() { return !buffer.empty(); });
    std::string item = buffer.front();
    buffer.pop();
    not_full.notify_one();
    return item;
}

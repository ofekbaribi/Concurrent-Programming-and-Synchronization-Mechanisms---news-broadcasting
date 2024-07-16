#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "bounded_buffer.h"
#include <vector>

using namespace std; 

class Dispatcher {
private:
    vector<BoundedBuffer*>& producer_queues;
    BoundedBuffer& sports_queue;
    BoundedBuffer& news_queue;
    BoundedBuffer& weather_queue;
    int num_producers;

public:
    Dispatcher(vector<BoundedBuffer*>& pq, BoundedBuffer& sq, BoundedBuffer& nq, BoundedBuffer& wq);
    void dispatch();
};

#endif 
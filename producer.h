#ifndef PRODUCER_H
#define PRODUCER_H

#include "bounded_buffer.h"
#include <vector>
#include <string>

using namespace std; 

class Producer {
private:
    int id;
    int num_products;
    BoundedBuffer& buffer;
    vector<string> types = {"SPORTS", "NEWS", "WEATHER"};

public:
    Producer(int id, int num_products, BoundedBuffer& buffer);
    void produce();
};

#endif // PRODUCER_H

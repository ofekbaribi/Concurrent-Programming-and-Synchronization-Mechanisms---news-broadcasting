#include "producer.h"
#include <cstdlib> // For rand()
#include <ctime>   // For srand(time(0))
#include <unordered_map> // For counting types

using namespace std; 

Producer::Producer(int id, int num_products, BoundedBuffer& buffer)
    : id(id), num_products(num_products), buffer(buffer) {
    srand(time(0)); 
}

void Producer::produce() {
    unordered_map<string, int> type_count;
    for (int i = 0; i < num_products; ++i) {
        string type = types[rand() % types.size()];
        string message = "Producer " + to_string(id) + " " + type + " " + to_string(type_count[type]);
        buffer.insert(message);
        type_count[type]++;
    }
    buffer.insert("DONE");
}

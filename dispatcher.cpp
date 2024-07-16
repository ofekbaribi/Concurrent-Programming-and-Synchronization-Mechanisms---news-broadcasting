#include "dispatcher.h"
#include <unistd.h> // For usleep()

using namespace std; // Use the std namespace

Dispatcher::Dispatcher(vector<BoundedBuffer*>& pq, BoundedBuffer& sq, BoundedBuffer& nq, BoundedBuffer& wq)
    : producer_queues(pq), sports_queue(sq), news_queue(nq), weather_queue(wq), num_producers(pq.size()) {}

void Dispatcher::dispatch() {
    bool all_done = false;
    vector<bool> producer_done(num_producers, false);

    while (!all_done) {
        all_done = true;

        for (int i = 0; i < num_producers; ++i) {
            if (!producer_done[i]) {
                std::string message = producer_queues[i]->remove(); // Access method on pointer

                if (message == "DONE") {
                    producer_done[i] = true;
                } else {
                    all_done = false;

                    if (message.find("SPORTS") != std::string::npos) {
                        sports_queue.insert(message);
                    } else if (message.find("NEWS") != std::string::npos) {
                        news_queue.insert(message);
                    } else if (message.find("WEATHER") != std::string::npos) {
                        weather_queue.insert(message);
                    }
                }
            }
        }

        usleep(100); // Sleep for a short period to avoid busy-waiting
    }

    sports_queue.insert("DONE");
    news_queue.insert("DONE");
    weather_queue.insert("DONE");
}

#include "bounded_buffer.h"
#include "producer.h"
#include "dispatcher.h"
#include "co_editor.h"
#include "screen_manager.h"
#include <vector>
#include <thread>
#include <fstream>
#include <iostream>
#include <string>

using namespace std; // Use the std namespace

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <config_file>" << endl;
        return 1;
    }

    ifstream config_file(argv[1]);
    if (!config_file) {
        cerr << "Error opening configuration file." << endl;
        return 1;
    }

    vector<Producer> producers;
    vector<BoundedBuffer*> producer_queues;
    string line;
    int producer_id = 0;

    while (getline(config_file, line)) {
        if (line.find("PRODUCER") != string::npos) {
            int num_products, queue_size;

            // Read the number of products
            config_file >> num_products;
            config_file.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the line

            // Read the queue size line
            getline(config_file, line);
            if (line.find("queue size = ") != string::npos) {
                queue_size = stoi(line.substr(line.find('=') + 1)); // Extract queue size value
            } else {
                cerr << "Invalid configuration file format." << endl;
                return 1;
            }

            // Create a new BoundedBuffer and Producer
            BoundedBuffer* buffer = new BoundedBuffer(queue_size);
            producer_queues.push_back(buffer);
            producers.emplace_back(++producer_id, num_products, *buffer);
        } else if (line.find("Co-Editor queue size") != string::npos) {
            int co_editor_queue_size;
            co_editor_queue_size = stoi(line.substr(line.find('=') + 1)); // Extract Co-Editor queue size

            BoundedBuffer sports_queue(co_editor_queue_size);
            BoundedBuffer news_queue(co_editor_queue_size);
            BoundedBuffer weather_queue(co_editor_queue_size);
            BoundedBuffer screen_manager_queue(co_editor_queue_size);

            Dispatcher dispatcher(producer_queues, sports_queue, news_queue, weather_queue);
            CoEditor sports_editor(sports_queue, screen_manager_queue);
            CoEditor news_editor(news_queue, screen_manager_queue);
            CoEditor weather_editor(weather_queue, screen_manager_queue);
            ScreenManager screen_manager(screen_manager_queue);

            // Start threads
            vector<thread> producer_threads;
            for (auto& producer : producers) {
                producer_threads.emplace_back(&Producer::produce, &producer);
            }
            thread dispatcher_thread(&Dispatcher::dispatch, &dispatcher);
            thread sports_thread(&CoEditor::edit, &sports_editor);
            thread news_thread(&CoEditor::edit, &news_editor);
            thread weather_thread(&CoEditor::edit, &weather_editor);
            thread screen_thread(&ScreenManager::display, &screen_manager);


            // Join threads
            for (auto& t : producer_threads) {
                t.join();
            }
            dispatcher_thread.join();
            sports_thread.join();
            news_thread.join();
            weather_thread.join();
            screen_thread.join();

            // Clean up dynamic memory
            for (auto buffer : producer_queues) {
                delete buffer;
            }


            return 0;
        }
    }

    cerr << "Invalid configuration file format." << endl;
    return 1;
}

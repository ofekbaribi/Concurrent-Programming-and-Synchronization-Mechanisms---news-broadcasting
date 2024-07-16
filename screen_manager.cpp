#include "screen_manager.h"
#include <iostream> // For std::cout

using namespace std; 

ScreenManager::ScreenManager(BoundedBuffer& q) : queue(q) {}

void ScreenManager::display() {
    int done_count = 0;
    while (done_count < 3) {
        string message = queue.remove();
        if (message == "DONE") {
            ++done_count;
        } else {
            cout << message << endl;
        }
    }
    cout << "DONE" << endl;
}
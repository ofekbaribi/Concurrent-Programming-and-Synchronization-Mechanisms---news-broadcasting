#include "co_editor.h"
#include <thread>
#include <chrono>

using namespace std; // Use the std namespace

CoEditor::CoEditor(BoundedBuffer& iq, BoundedBuffer& oq)
    : input_queue(iq), output_queue(oq) {}

void CoEditor::edit() {
    while (true) {
        string message = input_queue.remove();
        if (message == "DONE") {
            output_queue.insert("DONE");
            break;
        }
        this_thread::sleep_for(chrono::milliseconds(1000)); // Simulate editing delay
        output_queue.insert(message);
    }
}

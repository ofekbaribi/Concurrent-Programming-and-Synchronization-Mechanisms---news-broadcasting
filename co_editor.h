#ifndef COEDITOR_H
#define COEDITOR_H

#include "bounded_buffer.h"

using namespace std; 

class CoEditor {
private:
    BoundedBuffer& input_queue;
    BoundedBuffer& output_queue;

public:
    CoEditor(BoundedBuffer& iq, BoundedBuffer& oq);
    void edit();
};

#endif
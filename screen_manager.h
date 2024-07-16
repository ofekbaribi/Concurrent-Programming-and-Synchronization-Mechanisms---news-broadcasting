#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "bounded_buffer.h"

using namespace std; 

class ScreenManager {
private:
    BoundedBuffer& queue;

public:
    ScreenManager(BoundedBuffer& q);
    void display();
};

#endif 
CXX = g++
CXXFLAGS = -std=c++11 -pthread -Wall

OBJS = main.o bounded_buffer.o producer.o dispatcher.o co_editor.o screen_manager.o
TARGET = ex3.out

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp bounded_buffer.h producer.h dispatcher.h co_editor.h screen_manager.h
	$(CXX) $(CXXFLAGS) -c main.cpp

bounded_buffer.o: bounded_buffer.cpp bounded_buffer.h
	$(CXX) $(CXXFLAGS) -c bounded_buffer.cpp

producer.o: producer.cpp producer.h bounded_buffer.h
	$(CXX) $(CXXFLAGS) -c producer.cpp

dispatcher.o: dispatcher.cpp dispatcher.h bounded_buffer.h
	$(CXX) $(CXXFLAGS) -c dispatcher.cpp

co_editor.o: co_editor.cpp co_editor.h bounded_buffer.h
	$(CXX) $(CXXFLAGS) -c co_editor.cpp

screen_manager.o: screen_manager.cpp screen_manager.h bounded_buffer.h
	$(CXX) $(CXXFLAGS) -c screen_manager.cpp

clean:
	rm -f $(TARGET) $(OBJS)

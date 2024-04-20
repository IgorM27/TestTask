#pragma once

#include <vector>
#include <stdexcept>

template<typename T>
class CircularBufferArray {
private:
    std::vector<T> buffer;
    size_t head = 0;
    size_t tail = 0;
    bool full = false;
    size_t capacity;
public:
    CircularBufferArray(size_t size) : buffer(size), capacity(size) {
        if (size <= 0){
            throw std::out_of_range("Size should be positive");
        }
    }

    void push(T value) {
        if (full){
            head = (head + 1) % capacity;
        }
        buffer[tail] = value;
        tail = (tail + 1) % capacity;
        if (tail == head){
            full = true;
        }
    }

    T pop() {
        if (isEmpty()) {
            throw std::out_of_range("Empty buffer");
        }
        T value = buffer[head];
        head = (head + 1) % capacity;
        full = false;
        return value;
    }

    bool isEmpty() const {
        return head == tail && !full;
    }

    bool isFull() const {
        return full;
    }
};
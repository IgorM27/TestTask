#include <iostream>
#include <memory>

template<typename T>
class CircularBufferLinkedList {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;
    };

    std::unique_ptr<Node> head = nullptr;
    Node* tail = nullptr;
    size_t capacity;
    size_t size = 0;

public:
    CircularBufferLinkedList(size_t size) : capacity(size) {
        if (size <= 0){
            throw std::out_of_range("Size should be positive");
        }
    }

    void push(T value) {
        if (capacity == 1){
            if (head == nullptr){
                head = std::make_unique<Node>();
            }
            head->data = value;
            tail = head.get();
            size = 1;
            return;
        }
        if (size < capacity) {
            if (head == nullptr) {
                head = std::make_unique<Node>();
                head->data = value;
                tail = head.get();
            } else {
                tail->next = std::make_unique<Node>();
                tail = tail->next.get();
                tail->data = value;
            }
            ++size;
        } else {
            head = std::move(head->next);
            tail->next = std::make_unique<Node>();
            tail = tail->next.get();
            tail->data = value;
        }
    }

    T pop() {
        if (isEmpty()) throw std::out_of_range("Empty buffer");
        T value = head->data;
        head = std::move(head->next);
        --size;
        return value;
    }

    bool isEmpty() const {
        return size == 0;
    }

    bool isFull() const {
        return size == capacity;
    }
};
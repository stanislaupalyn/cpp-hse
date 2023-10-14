#include "queue.h"

Node::Node(int32_t value, Node* next) : value{value}, next{next} {
}

Queue::Queue() : front_{nullptr}, tail_{nullptr}, size_{0} {
}

Queue::~Queue() {
    Clear();
}

void Queue::Push(int32_t value) {
    Node* new_tail = new Node(value, nullptr);
    if (size_ == 0) {
        front_ = new_tail;
    } else {
        tail_->next = new_tail;
    }
    tail_ = new_tail;
    ++size_;
}

void Queue::Pop() {
    Node* new_front = front_->next;
    delete front_;
    front_ = new_front;
    --size_;
    if (size_ == 0) {
        tail_ = nullptr;
    }
}

int32_t Queue::Front() const {
    return front_->value;
}

int32_t Queue::Size() const {
    return size_;
}

void Queue::Clear() {
    while (size_ > 0) {
        Pop();
    }
}

bool Queue::Empty() const {
    return size_ == 0;
}
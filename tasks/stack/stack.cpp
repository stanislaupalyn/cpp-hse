#include "stack.h"

Node::Node(int32_t value, Node* previous) : value{value}, previous{previous} {
}

Stack::Stack() {
    head_ = nullptr;
    size_ = 0;
}

Stack::~Stack() {
    Clear();
}

void Stack::Push(int32_t value) {
    Node* new_head = new Node(value, head_);
    head_ = new_head;
    ++size_;
}

void Stack::Pop() {
    Node* old_head = head_;
    head_ = old_head->previous;
    delete old_head;
    --size_;
}

int32_t Stack::Top() const {
    return head_->value;
}

int32_t Stack::Size() const {
    return size_;
}

void Stack::Clear() {
    while (size_ > 0) {
        Pop();
    }
}

bool Stack::Empty() const {
    return size_ == 0;
}
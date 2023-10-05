#ifndef QUEUE_H
#define QUEUE_H
#include <algorithm>
#include <cassert>
#include <iostream>
using namespace std;
template <class T>
class Queue {
   private:
    int capacity{0};
    int _front{0};
    int rear{0};
    int added_elements{0};
    T *queue;
    int get_next(int index) {
        index++;
        if (index == capacity)
            index = 0;
        return index;
    }
    void expand_capacity() {
        int _size = 2 * capacity;
        T *new_queue = new T[_size];
        for (int i = 0, cur = _front; i < added_elements; i++) {
            new_queue[i] = queue[cur];
            cur = get_next(cur);
        }
        _front = 0;
        rear = added_elements;
        capacity = _size;
        std::swap(queue, new_queue);
        delete[] new_queue;
    }

   public:
    Queue() {
        capacity = 1;
        queue = new T[capacity];
    }

    void push(T value) {
        if (added_elements == capacity)
            expand_capacity();
        assert(added_elements < capacity);
        queue[rear] = value;
        added_elements++;
        rear = get_next(rear);
    }

    T front() {
        assert(_front >= 0 && _front < capacity);
        return queue[_front];
    }

    T pop() {
        T value = queue[_front];
        _front = get_next(_front);
        return value;
    }

    bool empty() {
        return added_elements == 0;
    }

    int size() {
        return added_elements;
    }
};
#endif

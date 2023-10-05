#ifndef QUEUE_H
#define QUEUE_H

#include "../singly-linked-list/LinkedList.h"

template <class T>
class Queue {
   private:
    LinkedList<T> ls;

   public:
    void push(T value) {
        ls.insert_end(value);
    }
    T pop() {
        return ls.delete_front();
    }
    int size() {
        return ls.size();
    }
    T front() {
        return ls.get_front();
    }
    bool empty() {
        return ls.size() == 0;
    }
};
#endif
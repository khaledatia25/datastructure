
#ifndef STACK_H
#define STACK_H
#include <algorithm>
#include <iostream>
using namespace std;
template <class T> class Stack {
private:
  T *stack{nullptr};
  int _size; // reprsents the size of the stack and also points to the next empty place
  int capacity;
  void expand_capacity() {
    capacity *= 2;
    T *temp_stack = new T[capacity];
    for (int i = 0; i < _size; i++) {
      temp_stack[i] = stack[i];
    }
    swap(temp_stack, stack);
    delete[] temp_stack;
  }

public:
  Stack() {
    _size = 0;
    capacity = 1;
    stack = new T[capacity];
  }
  void push(T value) {
    if (_size == capacity) {
      expand_capacity();
    }
    stack[_size++] = value;
  }
  T pop() {
    assert(_size > 0);
    return stack[--_size];
  }
  T top() {
    assert(_size > 0);
    return stack[_size - 1];
  }
  int size() { return _size; }
  bool empty() { return _size == 0; }
};
#endif
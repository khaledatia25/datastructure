#ifndef STACK_H
#define STACK_H
#include <iostream>
using namespace std;
template <class T> struct Node {
  T data;
  Node *next;
  Node(T value) : data(value) { next = nullptr; }
};

template <class T> class Stack {
private:
  Node<T> *head;
  int _size;

public:
  Stack() {
    head = nullptr;
    _size = 0;
  }
  void push(T value) {
    Node<T> *node = new Node<T>(value);
    node->next = head;
    head = node;
    _size++;
  }
  T pop() {
    assert(_size > 0);
    _size--;
    T ret = head->data;
    Node<T> *temp = head;
    head = head->next;
    delete temp;
    return ret;
  }
  T top() {
    assert(_size > 0);
    return head->data;
  }
  int size() { return _size; }
  bool empty() { return _size == 0; }
};
#endif
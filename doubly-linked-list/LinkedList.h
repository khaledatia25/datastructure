#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <algorithm>
#include <cassert>
#include <iostream>
using namespace std;
template <class T>
struct Node {
  T data;
  Node* next{};
  Node* prev{};
  Node(T data) : data(data) { next = prev = nullptr; }
};

template <class T>
class LinkedList {
 private:
  Node<T>* head{};
  Node<T>* tail{};
  int length = 0;
  void delete_node(Node<T>* node);
  Node<T>* delete_and_link(Node<T>* cur);

 public:
  LinkedList() {}
  LinkedList(const LinkedList&) = delete;
  LinkedList& operator=(const LinkedList& another) = delete;
  ~LinkedList() {
    for (head; head != nullptr;) {
      Node<T>* cur = head;
      head = cur->next;
      delete cur;
    }
  }

  void print();

  void insert_end(T value);

  void insert_front(T value);

  void delete_front();

  Node<T>* get_nth(int n);

  int search(T value);

  int search_improved(T val);

  void delete_end();

  void link(Node<T>* first, Node<T>* second);

  void delete_nth(int order);

  void delete_with_key(T value);

  void delete_next_node(Node<T>* prev);

  void embed_after(Node<T>* prev, T val);

  void insert_sorted(T val);

  void swap_pairs();

  void reverse();

  int size();

  void swap_head_tail();

  void delete_all_with_key(T value);
  void delete_even_pos();
  Node<T>* find_the_middle();
  void swap_k_front_end(int k);
};

template <class T>
int LinkedList<T>::size() {
  return length;
}
template <class T>
void LinkedList<T>::print() {
  for (Node<T>* cur = head; cur != nullptr; cur = cur->next) {
    cout << cur->data << ' ';
  }
  cout << "\n";
}
template <class T>
Node<T>* LinkedList<T>::delete_and_link(Node<T>* cur) {
  Node<T>* ret = cur->prev;
  link(cur->prev, cur->next);
  delete_node(cur);
  return ret;
}
template <class T>
void LinkedList<T>::delete_node(Node<T>* node) {
  delete node;
  node = nullptr;
  length--;
}

template <class T>
void LinkedList<T>::link(Node<T>* first, Node<T>* second) {
  if (first != nullptr) first->next = second;
  if (second != nullptr) second->prev = first;
}
template <class T>
void LinkedList<T>::insert_end(T value) {
  Node<T>* temp = new Node<T>(value);
  if (head == nullptr) {
    head = tail = temp;
  } else {
    link(tail, temp);
    tail = temp;
  }
  length++;
}

template <class T>
void LinkedList<T>::insert_front(T value) {
  Node<T>* temp = new Node<T>(value);
  if (head == nullptr) {
    head = tail = temp;
  } else {
    link(temp, head);
    head = temp;
  }
  length++;
}
template <class T>
void LinkedList<T>::embed_after(Node<T>* first, T value) {
  Node<T>* temp = new Node<T>(value);
  Node<T>* second = first->next;
  link(first, temp);
  link(temp, second);
  length++;
}
template <class T>
void LinkedList<T>::insert_sorted(T value) {
  if (!length || value <= head->data)
    insert_front(value);
  else if (tail->data <= value)
    insert_end(value);
  else {
    for (Node<T>* cur = head; cur != nullptr; cur = cur->next) {
      if (value <= cur->data) {
        embed_after(cur, value);
        return;
      }
    }
  }
}
template <class T>
void LinkedList<T>::delete_front() {
  if (head == nullptr) return;
  Node<T>* temp = head;
  head = head->next;
  head->prev = nullptr;
  delete_node(temp);
  if (length == 0) {
    tail = nullptr;
  }
}

template <class T>
void LinkedList<T>::delete_end() {
  if (head == nullptr) return;
  Node<T>* temp = tail;
  tail = tail->prev;
  tail->next = nullptr;
  delete_node(temp);
  if (length == 0) {
    head = nullptr;
  }
}

template <class T>
void LinkedList<T>::delete_with_key(T value) {
  if (length == 0) return;
  if (head->data == value) {
    delete_front();
    return;
  }
  for (Node<T>* cur = head; cur != nullptr; cur = cur->next) {
    if (cur->data == value) {
      cur = delete_and_link(cur);
      if (cur->next == nullptr) {
        tail = cur;
      }
      return;
    }
  }
}

template <class T>
void LinkedList<T>::delete_all_with_key(T value) {
  for (Node<T>* cur = head; cur != nullptr; cur = cur->next) {
    if (cur->data == value) {
      cur = delete_and_link(cur);
      if (cur->next == nullptr) {
        tail = cur;
      }
    }
  }
}

template <class T>
void LinkedList<T>::delete_even_pos() {
  int idx = 1;
  for (Node<T>* cur = head; cur != nullptr; cur = cur->next, ++idx) {
    if (idx % 2 == 0) {
      cur = delete_and_link(cur);
      if (cur->next == nullptr) {
        tail = cur;
      }
    }
  }
}
template <class T>
Node<T>* LinkedList<T>::find_the_middle() {
  if (head == nullptr) return nullptr;
  Node<T>* front = head;
  Node<T>* back = tail;
  while (front != back && front->next != back) {
    front = front->next;
    back = back->prev;
  }
  // another implementation
  Node<T>*slow = head, *fast = head;
  while (fast != nullptr && fast->next != nullptr) {
    slow = slow->next;
    fast = fast->next->next;
  }
  return slow;
  return back;
}

template <class T>
Node<T>* LinkedList<T>::get_nth(int n) {
  if (n > length) return nullptr;
  int ord = 1;
  for (Node<T>* cur = head; cur != nullptr; cur = cur->next) {
    if (ord == n) return cur;
    ord++;
  }
  return nullptr;
}

template <class T>
void LinkedList<T>::swap_k_front_end(int k) {
  assert(k <= length);
  if (k == 1 && length == 1) return;
  if (k == 1 || k == length) {
    T h = head->data, t = tail->data;
    delete_front();
    delete_end();
    insert_front(t);
    insert_end(h);
    return;
  }
  if (length % 2 && k == length / 2 + 1) return;
  Node<T>* first = get_nth(k);
  Node<T>* second = get_nth(length - k + 1);
  first->next->prev = second;
  first->prev->next = second;
  second->prev->next = first;
  second->next->prev = first;
  swap(first->prev, second->prev);
  swap(first->next, second->next);
}

template <class T>
void LinkedList<T>::reverse() {
  for (Node<T>* cur = head; cur != nullptr; cur = cur->prev) {
    swap(cur->next, cur->prev);
  }
  swap(head, tail);
}
#endif
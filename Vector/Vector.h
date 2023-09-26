#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <cassert>
#include <iostream>

template <class T> class Vector {
private:
  T *arr{nullptr};
  int size{0};
  int capacity{};
  void expand_capacity();

public:
  explicit Vector(int size);
  Vector();
  ~Vector();

  T get(int idx);
  T &operator[](int idx);
  const T &operator[](int idx) const;
  void set(int idx, T val);
  T get_front();
  T get_back();
  void print();
  int find(T val);
  void push_back(T value);
  void insert(int idx, T value);
  void pop(int idx);
  void right_rotate();
  void left_rotate();
  void rotate(int times);
  Vector &operator=(const Vector &other);
};

template <class T> Vector<T>::Vector() {
  capacity = 1;
  arr = new T[capacity];
}

template <class T> Vector<T>::Vector(int size) : size(size) {
  if (size < 0)
    size = 1;
  capacity = size + 1;
  arr = new T[capacity];
}
template <class T> Vector<T>::~Vector() {
  delete[] arr;
  arr = nullptr;
}

template <class T> T Vector<T>::get(int idx) {
  assert(0 <= idx && idx < size);
  return arr[idx];
}

template <class T> T &Vector<T>::operator[](int idx) {
  assert(0 <= idx && idx < size);
  return arr[idx];
}

template <class T> const T &Vector<T>::operator[](int idx) const {
  assert(0 <= idx && idx < size);
  return arr[idx];
}

template <class T> void Vector<T>::set(int idx, T val) {
  assert(0 <= idx && idx < size);
  arr[idx] = val;
}

template <class T> int Vector<T>::find(T val) {
  for (int i = 0; i < size; i++) {
    if (arr[i] == val)
      return i;
  }
  return -1;
}

template <class T> void Vector<T>::print() {
  for (int i = 0; i < size; i++)
    std::cout << arr[i] << ' ';
  std::cout << "\n";
}

template <class T> T Vector<T>::get_front() { return arr[0]; }

template <class T> T Vector<T>::get_back() { return arr[size - 1]; }

template <class T> void Vector<T>::expand_capacity() {
  // 1 - Create a new array of a bigger size
  capacity *= 2;
  T *arr2 = new T[capacity]{};
  // 2 - Copy old data
  for (int i = 0; i < size; i++)
    arr2[i] = arr[i];
  // 3 - change the pointers
  std::swap(arr, arr2);
  delete[] arr2;
}

template <class T> void Vector<T>::push_back(T value) {
  if (size == capacity)
    expand_capacity();
  arr[size++] = value;
}

template <class T> void Vector<T>::insert(int idx, T value) {
  assert(0 <= idx && idx < size);
  if (size == capacity)
    expand_capacity();
  for (int i = size; i > idx; i--)
    arr[i] = arr[i - 1];
  size++;
  arr[idx] = value;
}

template <class T> void Vector<T>::right_rotate() {
  int last = arr[size - 1];
  for (int i = size - 1; i > 0; i--)
    arr[i] = arr[i - 1];
  arr[0] = last;
}

template <class T> void Vector<T>::left_rotate() {
  int first = arr[0];
  for (int i = 0; i < size - 1; i++)
    arr[i] = arr[i + 1];
  arr[size - 1] = first;
}

template <class T> void Vector<T>::rotate(int times) {
  times %= size;
  if (times == 0)
    return;
  int *arr2 = new int[times]{};
  for (int j = 0, i = size - times; i < size; i++, j++)
    arr2[j] = arr[i];
  for (int i = 0; i < size - times; i++)
    arr[i + times] = arr[i];
  for (int i = 0; i < times; i++)
    arr[i] = arr2[i];
  delete[] arr2;
}

template <class T> void Vector<T>::pop(int idx) {
  assert(0 <= idx && idx < size);
  for (int i = idx; i < size - 1; i++)
    arr[i] = arr[i + 1];
  size--;
}

template <class T> Vector<T> &Vector<T>::operator=(const Vector &other) {
  if (this == &other) {
    return *this; // Self-assignment, no action needed
  }

  // Perform deep copy
  if (other.size > capacity) {
    // Reallocate memory if necessary
    delete[] arr;
    capacity = other.size + 100;
    arr = new T[capacity];
  }

  size = other.size;
  for (int i = 0; i < size; ++i) {
    arr[i] = other.arr[i];
  }

  return *this;
}

#endif // VECTOR_H

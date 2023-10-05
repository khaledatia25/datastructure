#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <algorithm>
#include <cassert>
#include <iostream>

template <class T>
struct Node {
    T data;
    Node* next;
    Node(T data) : data(data) { next = nullptr; };
};

template <class T>
class LinkedList {
   private:
    Node<T>* head{};
    Node<T>* tail{};
    int length = 0;
    void delete_node(Node<T>* node) {
        length--;
        delete node;
        node = nullptr;
    }

   public:
    LinkedList() {}
    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList& another) = delete;
    ~LinkedList() {
        for (head; head != nullptr; head = head->next) {
            delete head;
        }
    }

    void print();

    void insert_end(T value);

    void insert_front(T value);

    T delete_front();

    Node<T>* get_nth(int n);

    int search(T value);

    int search_improved(T val);

    void delete_last();

    void delete_nth(int order);

    void delet_with_key(T value);

    void delete_next_node(Node<T>* prev);

    void embed_after(Node<T>* prev, T val);

    void insert_sorted(T val);

    void swap_pairs();

    void reverse();
    T get_front() {
        assert(head != nullptr);
        return head->data;
    }
    void swap_head_tail();
    int size() {
        return length;
    }
};

template <class T>
void LinkedList<T>::print() {
    for (Node<T>* cur = head; cur != nullptr; cur = cur->next) {
        std::cout << cur->data << ' ';
    }
    std::cout << '\n';
}

template <class T>
void LinkedList<T>::insert_end(T value) {
    Node<T>* temp = new Node<T>(value);
    length++;
    if (head == nullptr) {
        tail = head = temp;
        return;
    }
    tail->next = temp;
    tail = temp;
}

template <class T>
void LinkedList<T>::insert_front(T value) {
    Node<T>* temp = new Node<T>(value);
    length++;
    temp->next = head;
    head = temp;
    if (length == 1) tail = head;
}

template <class T>
T LinkedList<T>::delete_front() {
    assert(head != nullptr);
    Node<T>* temp = head;
    T val = head->data;
    head = head->next;
    delete_node(temp);
    if (head == nullptr) {
        tail = head;
    }
    return val;
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
int LinkedList<T>::search(T value) {
    int index = 0;
    for (Node<T>* cur = head; cur != nullptr; cur = cur->next) {
        if (value == cur->data) {
            return index;
        }
        index++;
    }
    return -1;
}

template <class T>
int LinkedList<T>::search_improved(T val) {
    int idx = 0;
    Node<T>* previous = nullptr;
    for (Node<T>* cur = head; cur != nullptr; cur = cur->next, idx++) {
        if (cur->data == val) {
            if (previous == nullptr) {
                return idx;
            }
            std::swap(previous->data, cur->data);
            return idx - 1;
        }
        previous = cur;
    }
    return -1;
}

template <class T>
void LinkedList<T>::delete_last() {
    if (length <= 1) {
        delete_front();
        return;
    }
    Node<T>* prev = get_nth(length - 1);
    delete_node(tail);
    tail = prev;
    tail->next = nullptr;
}

template <class T>
void LinkedList<T>::delete_nth(int order) {
    if (order < 1 || order > length) {
        throw "Out of boundaries";
    }
    if (order == 1) {
        delete_front();
        return;
    }
    if (order == length) {
        delete_last();
        return;
    }
    Node<T>* prev = get_nth(order - 1);
    Node<T>* cur = prev->next;
    prev->next = cur->next;
    delete_node(cur);
}

template <class T>
void LinkedList<T>::delet_with_key(T value) {
    int idx = search(value);
    if (idx != -1) {
        delete_nth(idx + 1);
    }
}

template <class T>
void LinkedList<T>::delete_next_node(Node<T>* prev) {
    Node<T>* temp = prev->next;
    prev->next = temp->next;
    bool is_tail = tail == temp;
    delete_node(temp);
    if (is_tail) tail = temp;
}

template <class T>
void LinkedList<T>::embed_after(Node<T>* prev, T val) {
    Node<T>* new_node = new Node<T>(val);
    new_node->next = prev->next;
    prev->next = new_node;
    length++;
}

template <class T>
void LinkedList<T>::insert_sorted(T val) {
    if (length == 0 || val <= head->data) {
        insert_front(val);
        return;
    }
    if (tail->data <= val) {
        insert_end(val);
        return;
    }
    Node<T>* prev = nullptr;
    for (Node<T>* cur = head; cur != nullptr; cur = cur->next) {
        if (val <= cur->data) {
            embed_after(prev, val);
            return;
        }
        prev = cur;
    }
}

template <class T>
void LinkedList<T>::swap_pairs() {
    bool exchange = 1;
    for (Node<T>* cur = head; cur != nullptr; cur = cur->next) {
        if (cur->next != nullptr && exchange) {
            T val = cur->data;
            cur->data = cur->next->data;
            cur->next->data = val;
        }
        exchange ^= 1;
    }
}

template <class T>
void LinkedList<T>::reverse() {
    Node<T>* cur_head = head;
    Node<T>* cur_tail = tail;
    Node<T>* prev = nullptr;
    for (Node<T>* cur = head; cur != nullptr;) {
        Node<T>* temp = cur->next;
        cur->next = prev;
        prev = cur;
        cur = temp;
    }
    head = tail;
    tail = cur_head;
}

template <class T>
void LinkedList<T>::swap_head_tail() {
    if (head == tail) return;
    if (!length) return;
    Node<T>* temp = get_nth(length - 1);
    temp->next = head;
    tail->next = head->next;
    head->next = nullptr;
    std::swap(head, tail);
}

// Explicit instantiation for supported types
template class LinkedList<int>;  // You can add more instantiations as needed

#endif

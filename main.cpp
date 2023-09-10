#include <bits/stdc++.h>

#include "./doubly-linked-list/LinkedList.h"

using namespace std;

signed main() {
  LinkedList<int> lt;
  int n = 8;
  for (int i = 0; i < n; i++) {
    lt.insert_end(i);
  }
  for (int i = 0; i < 3; i++) {
    lt.insert_end(7);
  }

  lt.print();
  cout << "Delete all 7s \n";
  lt.delete_all_with_key(7);
  lt.print();
  cout << "Insert Element at end\n";
  lt.insert_end(69);
  lt.print();
  cout << "Delete Even Pos \n";
  lt.delete_even_pos();
  lt.print();
  cout << lt.find_the_middle()->data << endl;
  lt.insert_end(55);
  lt.insert_end(55);
  lt.insert_end(55);
  lt.print();
  cout << lt.find_the_middle()->data << endl;
  lt.swap_k_front_end(1);
  lt.print();
  lt.swap_k_front_end(lt.size());
  lt.print();
  lt.swap_k_front_end(3);
  lt.print();
  lt.reverse();
  lt.print();
  return 0;
}
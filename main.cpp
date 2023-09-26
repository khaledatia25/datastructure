#include <bits/stdc++.h>

#include "./stack-array/Stack.h"

using namespace std;

signed main() {
  Stack<int> st;
  for (int i = 0; i < 10; i++) {
    st.push(i);
  }
  cout << st.size() << endl;
  for (int i = 0; i < 10; i++) {
    cout << st.top() << " ";
    st.pop();
  }
  cout << endl;
  cout << st.size() << endl;
  st.pop();
  return 0;
}
#include <bits/stdc++.h>

#include "./stack-array/Stack.h"

using namespace std;

class MyHashMap {
   private:
    vector<vector<pair<int, int>>> table;
    int table_size;
    int total_elements;
    double limit_load_factor;

    void rehash() {
        int current_load_factor = (double)total_elements / table_size;
        if (current_load_factor < limit_load_factor) return;
        MyHashMap new_table(2 * table_size, limit_load_factor);
        for (int hash = 0; hash < table_size; hash++) {
            if (table[hash].size() == 0) continue;

            for (int i = 0; i < table[hash].size(); ++i) {
                new_table.put(table[hash][i].first, table[hash][i].second);
            }
        }
        table_size *= 2;
        table = new_table.table;
    }

   public:
    MyHashMap(int table_size, int limit_load_factor) : table_size(table_size), limit_load_factor(limit_load_factor) {
        total_elements = 0;
        table.resize(table_size);
    }
    MyHashMap() {
        table_size = 10;
        table.resize(table_size);
        limit_load_factor = .75;
        total_elements = 0;
    }

    void put(int key, int value) {
        int idx = key % table_size;
        for (int i = 0; i < (int)table[idx].size(); ++i) {
            if (table[idx][i].first == key) {
                table[idx][i].second = value;
                return;
            }
        }
        table[idx].push_back({key, value});
        total_elements++;
    }

    int get(int key) {
        int idx = key % table_size;
        for (int i = 0; i < (int)table[idx].size(); ++i) {
            if (table[idx][i].first == key) return table[idx][i].second;
        }
        return -1;
    }

    void remove(int key) {
        int idx = key % table_size;
        for (int i = 0; i < (int)table[idx].size(); ++i) {
            if (table[idx][i].first == key) {
                swap(table[idx][i], table[idx].back());
                table[idx].pop_back();
                total_elements--;
                return;
            }
        }
    }
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */

signed main() {
    return 0;
}
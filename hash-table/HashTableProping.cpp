#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct PhoneEntry {
    const static int INTERNAL_LIMIT = 214783647;
    string name;          // key
    string phone_number;  // data
    PhoneEntry(string name, string phone_number) : name(name), phone_number(phone_number) {}
    int hash() {
        return hash_string(name, INTERNAL_LIMIT);
    }
    int get_char_value(char c) {
        if (c >= '0' && c <= '9')
            return c - '0';
        if (c >= 'a' && c <= 'z')
            return c - 'a' + 10;
        return c - 'A' + 10 + 26;
    }
    int hash_string(string &s, int mod) {
        long long m = mod;
        long long sum = 0;
        // char  0...9  a...z     A...Z
        // map   0...9  10...35   36...61
        for (int i = 0; i < (int)s.size(); i++) {
            sum = (sum * 62 + get_char_value(s[i])) % m;
        }
        return sum % m;
    }
    void print() {
        cout << "Contact name: " << name << ", number: " << phone_number << endl;
    }
};

class PhoneHashTalbe {
   private:
    int table_size;
    vector<PhoneEntry *> table;
    // to mark cell as deleted
    PhoneEntry *deleted = new PhoneEntry("", "");

   public:
    PhoneHashTalbe(int table_size) : table_size(table_size) {
        table.resize(table_size);
    }
    bool put(PhoneEntry phone) {
        int idx = phone.hash() % table_size;
        for (int step = 0; step < table_size; ++step) {
            if (table[idx] == deleted or table[idx] == nullptr) {
                table[idx] = new PhoneEntry(phone.name, phone.phone_number);
                return true;
            } else if (table[idx]->name == phone.name) {
                table[idx]->phone_number = phone.phone_number;
                return true;
            }
            idx = (idx + 1) % table_size;
        }
        return false;
    }
    bool remove(PhoneEntry phone) {
        int idx = phone.hash() % table_size;
        for (int step = 0; step < table_size; ++step) {
            if (table[idx] == nullptr) {
                break;
            }
            if (table[idx] != deleted && table[idx]->name == phone.name) {
                delete table[idx];
                table[idx] = deleted;
                return true;
            }
            idx = (idx + 1) % table_size;
        }
        return false;
    }

    bool get(PhoneEntry &phone) {
        int idx = phone.hash() % table_size;
        for (int step = 0; step < table_size; ++step) {
            if (table[idx] == nullptr) {
                break;
            }
            if (table[idx] != deleted && table[idx]->name == phone.name) {
                phone.phone_number = table[idx]->phone_number;
                return true;
            }
            idx = (idx + 1) % table_size;
        }
        return false;
    }
};

int main() {
    return 0;
}
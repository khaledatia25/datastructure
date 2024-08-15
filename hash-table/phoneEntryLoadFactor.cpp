#include <iostream>
#include <string>
#include <vector>
using namespace std;
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

struct PhoneEntry {
    const static int INTERNAL_LIMIT = 214783647;
    string name;          // key
    string phone_number;  // data
    PhoneEntry(string name, string phone_number) : name(name), phone_number(phone_number) {}
    int hash() {
        return hash_string(name, INTERNAL_LIMIT);
    }

    int hash_string(string str, int base) {
        long long b = base;
        long long sum = 0;
        for (int i = 0; i < (int)str.size(); i += 1) {
            sum = (sum * 26 + str[i] - 'a') % b;
        }
        return sum % b;
    }
    void print() {
        cout << "Contact name: " << name << ", number: " << phone_number << endl;
    }
};

class PhoneHashTalbe {
   private:
    int table_size;
    double limit_load_factor;
    int total_elements;
    vector<vector<PhoneEntry>> table;

    void rehashing() {
        double cur_load_factor = (double)total_elements / table_size;
        if (cur_load_factor < limit_load_factor) return;

        PhoneHashTalbe new_table(2 * table_size, limit_load_factor);

        for (int hash = 0; hash < table_size; ++hash) {
            if (table[hash].size() == 0) continue;

            for (int i = 0; i < table[hash].size(); ++i) {
                new_table.put(table[hash][i]);
            }
        }

        // Copy && delete
        table_size *= 2;
        table = new_table.table;
        print_all();
    }

   public:
    PhoneHashTalbe(int table_size = 10, double limit_load_factor = .75) : table_size(table_size), limit_load_factor(limit_load_factor) {
        table.resize(table_size);
        total_elements = 0;
    }
    void put(PhoneEntry phone) {
        int idx = phone.hash() % table_size;

        for (int i = 0; i < (int)table[idx].size(); i += 1) {
            if (table[idx][i].name == phone.name) {
                table[idx][i] = phone;  // exist => update
                return;
            }
        }
        table[idx].push_back(phone);
        total_elements++;
    }

    bool remove(PhoneEntry phone) {
        int idx = phone.hash() % table_size;
        for (int i = 0; i < (int)table[idx].size(); i += 1) {
            if (table[idx][i].name == phone.name) {
                swap(table[idx][i], table[idx].back());
                table[idx].pop_back();
                total_elements--;
                return true;
            }
        }
        return false;
    }

    bool get(PhoneEntry &phone) {
        int idx = phone.hash() % table_size;

        for (int i = 0; i < (int)table[idx].size(); i += 1) {
            if (table[idx][i].name == phone.name) {
                phone = table[idx][i];
                return true;
            }
        }
        return false;
    }

    void print_all() {
        for (int hash = 0; hash < table_size; ++hash) {
            if (table[hash].size() == 0)
                continue;
            cout << "Hash " << hash << ": ";
            for (PhoneEntry &phone : table[hash]) {
                phone.print();
            }
            cout << "\n";
        }
    }
};

int main() {
    PhoneHashTalbe table(3);
    table.put(PhoneEntry("mostafa", "123456"));
    table.put(PhoneEntry("mostafa", "242342344"));
    table.put(PhoneEntry("ali", "242342344"));
    table.put(PhoneEntry("ziad", "242342344"));
    table.put(PhoneEntry("hany", "242342344"));
    table.put(PhoneEntry("khaled", "242342344"));
    PhoneEntry e("mostafa", "");
    if (table.get(e)) {
        e.print();
    }

    table.print_all();
    return 0;
}
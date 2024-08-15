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

int folding_hash(string &s, int mod) {
    long long m = mod;
    long long sum = 0, temp = 0;
    for (int i = 0, j = 1; i < s.size(); i++, j++) {
        temp = (temp * 62 + get_char_value(s[i])) % m;
        if (j % 4 == 0) {
            sum += temp;
            sum %= m;
            temp = 0;
        }
    }
    return sum % m;
}

struct SomeObject {
    const static int INTERNAL_LIMIT = 214783647;
    string str1, str2;
    int number;
    int hash() {
        int hash1 = hash_string(str1, INTERNAL_LIMIT);
        int hash2 = folding_hash(str2, INTERNAL_LIMIT);
        int hash3 = number % INTERNAL_LIMIT;
        return (1ll * (hash1 + hash2 + hash3)) % INTERNAL_LIMIT;
    }
};

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
    vector<vector<PhoneEntry>> table;

   public:
    PhoneHashTalbe(int table_size) : table_size(table_size) {
        table.resize(table_size);
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
    }

    bool remove(PhoneEntry phone) {
        int idx = phone.hash() % table_size;
        for (int i = 0; i < (int)table[idx].size(); i += 1) {
            if (table[idx][i].name == phone.name) {
                swap(table[idx][i], table[idx].back());
                table[idx].pop_back();
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
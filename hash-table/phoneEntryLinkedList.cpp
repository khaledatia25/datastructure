#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct PhoneEntry {
    const static int INTERNAL_LIMIT = 214783647;
    string name;          // key
    string phone_number;  // data

    PhoneEntry(string name, string phone_number) : name(name), phone_number(phone_number) {}

    int hash() const {
        return hash_string(name, INTERNAL_LIMIT);
    }

    static int hash_string(const string& str, int base) {
        long long b = base;
        long long sum = 0;
        for (char c : str) {
            sum = (sum * 26 + c - 'a') % b;
        }
        return sum % b;
    }

    void print() const {
        cout << "Contact name: " << name << ", number: " << phone_number << endl;
    }
};

class PhoneHashTable {
   private:
    struct LinkedHashEntry {
        PhoneEntry item;
        LinkedHashEntry* next{};

        LinkedHashEntry(PhoneEntry item) : item(item), next(nullptr) {}
    };

    int table_size;
    vector<LinkedHashEntry*> table{};

    void delete_all(LinkedHashEntry* cur) {
        if (cur == nullptr) return;
        delete_all(cur->next);
        delete cur;
    }

   public:
    PhoneHashTable(int table_size = 10) : table_size(table_size) {
        table.resize(table_size, nullptr);
    }

    ~PhoneHashTable() {
        for (int hash = 0; hash < table_size; hash++) {
            delete_all(table[hash]);
        }
    }

    void put(const PhoneEntry& item) {
        int idx = item.hash() % table_size;

        if (table[idx] == nullptr) {
            table[idx] = new LinkedHashEntry(item);
            return;
        }

        LinkedHashEntry* cur = table[idx];
        while (cur->next != nullptr) {
            if (cur->item.name == item.name) {
                cur->item = item;  // Update existing entry
                return;
            }
            cur = cur->next;
        }

        if (cur->item.name == item.name) {
            cur->item = item;  // Update existing entry at the end of the chain
        } else {
            cur->next = new LinkedHashEntry(item);  // Add new entry
        }
    }

    void print_all() const {
        for (int i = 0; i < table_size; i++) {
            if (table[i] == nullptr) continue;

            cout << "Hash: " << i << ": " << endl;

            for (LinkedHashEntry* cur = table[i]; cur != nullptr; cur = cur->next) {
                cur->item.print();
            }
            cout << endl;
        }
    }
};

int main() {
    PhoneHashTable table(3);
    table.put(PhoneEntry("mostafa", "123456"));
    table.put(PhoneEntry("mostafa", "242342344"));
    table.put(PhoneEntry("ali", "242342344"));
    table.put(PhoneEntry("ziad", "242342344"));
    table.put(PhoneEntry("hany", "242342344"));
    table.put(PhoneEntry("khaled", "242342344"));

    table.print_all();
    return 0;
}

#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename Key, typename Value>
class HashTable {
    private:
        typedef vector<unsigned char> (*bytes)(Key& k);
        typedef bool (*cmp)(Key& k1, Key& k2);
        
        struct Node {
            Key key;
            Value value;
            Node *next;

            Node(Key k, Value v) {
                key = k;
                value = v;
                next = 0;
            }
        };

        unsigned hash(Key &key) {
            vector<unsigned char> p = get_bytes(key);
            unsigned h = 0;
            for (int i = 0; i < p.size(); i++)
                h ^= (h << 5) + (h >> 2) + p[i];
            return h;
        }

        unsigned hash2(Key &key) {
            vector<unsigned char> p = get_bytes(key);
            unsigned h = 0;
            for (int i = 0; i < p.size(); i++) {
                h = 33*h + p[i];
            }
            return h;
        }

        Node **table;
        size_t size;

        bytes get_bytes;
        cmp equals;

    public:
        HashTable(size_t s, bytes b, cmp c) : size(s), get_bytes(b), equals(c) {
            table = new Node*[size]();
        }
        ~HashTable() {
            //TODO: make sure all chains are free first!
            delete[] table;
        }
        
        Value find(Key &key) {
            unsigned h = hash(key) % size;
            Node *it = table[h];
            if (it == 0)
                return 0;
            while (it != 0) {
                if (equals(it->key, key))
                    return it->value;
                it = it->next;
            }
            return 0;
        }
        bool insert(Key key, Value value) {
            unsigned h = hash(key) % size;

            Node *it = table[h];
            while (it != 0) {
                if (equals(key, it->key)) {
                    it->value = value;
                    return true;
                }
                it = it->next;
            }

            it = new Node(key, value);
            it->next = table[h];
            table[h] = it;
            return true;
        }
        bool remove(Key& key) {
            unsigned h = hash(key) % size;
            if (table[h] == 0) 
                return false;
            Node *it = table[h], *p = 0;
            while (it != 0) {
                if (equals(it->key, key))
                    break;
                p = it;
                it = it->next;
            }
            if (it == 0)
                return false;

            if (p == 0)
                table[h] = table[h]->next;
            else
                p->next = it->next;
            delete it;

            return true;
        }
};
        
bool equals(string& s1, string& s2) {
    return s1 == s2;
}

vector<unsigned char> get_bytes(string& s) {
    vector<unsigned char> bytes(s.begin(), s.end());
    return bytes;
}

int main() 
{
    HashTable<string, int> ht(256, get_bytes, equals);
    string s = "abc";

    int x = 12;
    int &b = x;
    b = 13;
    cout << x  << endl;
    cout << ht.insert(s, 9) << endl;
    cout << ht.find(s) << endl;

    return 0;
}


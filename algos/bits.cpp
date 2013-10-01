#include <iostream>
using namespace std;

template <typename T>
void print_bits(T b) {
    for (int i = sizeof(b) * 8 - 1; i >= 0; i--) {
        int t = (b & (1 << i));
        cout << (t ? '1' : '0');
        if (i > 0 && i % 8 == 0)
            cout << " ";
    }
    cout << endl;
}

int main() {
    char a = 7;
    print_bits( (char)(a >> 2) );
    return 0;
}

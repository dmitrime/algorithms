#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

void reverse_aux(char *s, int first, int last) {
    while (first < last) {
        swap(s[first], s[last]);
        first++;
        last--;
    }
}

char* reverse(char *s)
{
    if (s != 0) 
        reverse_aux(s, 0, strlen(s) - 1);
    return s;
}

//TODO: read on char range
bool all_unique(const char* s)
{
    int len = strlen(s);
    bool unique[256];
    for (int i = 0; i < 256; i++)
        unique[i] = true;
    for (int i = 0; i < len; i++)
    {
        int index = int(s[i]); 
        if (unique[index])
            unique[index] = false;
        else
            return false;
    }
    return true;
}

char* rotate_v1(char *s, int rot) {
    int len = strlen(s);
    reverse_aux(s, 0, rot-1);
    reverse_aux(s, rot, len-1);
    reverse_aux(s, 0, len-1);
    return s;
}

int gcd(int a, int b) {
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

char* rotate_v2(char *s, int rot) {
    int len = strlen(s);
    rot = rot % len;
    int g = gcd(rot, len);

    for (int i = 0; i < g; i++) {
        char temp = s[i];
        int cur = i;
        int next = cur + rot;
        if (next >= len) next -= len;
        while (next != i) {
            s[cur] = s[next];
            cur = next;
            next += rot;
            if (next >= len) next -= len;
        }
        s[cur] = temp;
    }
    return s;
}

int main()
{
    char str1[] = "abcdefg";
    //char str2[] = "aaaaaaa";
    //cout << all_unique(str1) << " " << all_unique(str2) << endl;
    //cout << reverse(str1) << " " << reverse(str2) << endl;
    cout << rotate_v2(str1, 4) << endl;
    return 0;
}


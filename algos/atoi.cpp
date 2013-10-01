#include <iostream>
using namespace std;

int atoi(const char* s)
{
    const char *p = s;
    while (*p)
        p++;
    p--;

    int result = 0;
    int ten = 1;
    while (p >= s)
    {
        if (p == s && *p == '-')
            result *= -1;
        else if (*p >= '0' && *p <= '9')
            result += (*p-'0') * ten;
        else
            return 0;

        ten *= 10;
        p--;
    }
    return result;
}

int main()
{
    cout << atoi("") << endl;
    return 0;
}


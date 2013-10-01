#include <iostream>
#include <set>
#include <cstring>
using namespace std;

unsigned ways_problem2() {
    int X = 3, Y = 3;
    int mat[X][Y];
    memset(mat, 0, sizeof mat);

    for (int i = 0; i < X; i++)
        mat[i][0] = 1;
    for (int i = 1; i < Y; i++)
        mat[0][i] = 1;
    for (int i = 1; i < X; i++) {
        for (int j = 1; j < Y; j++)
            mat[i][j] += mat[i-1][j] + mat[i][j-1];
    }
    cout << mat[X-1][Y-1] << endl;
}

typedef set<int>::iterator iter;
void print_set(set<int>& remain) {
    if (remain.size() > 0)
        for (iter it = remain.begin(); it != remain.end(); it++)
            cout << *it << " ";
    else
        cout << "{}";
    cout << endl;
}
void subsets(set< set<int> >& used, set<int>& remain) {
    print_set(remain);
    used.insert(remain);
    set<int> s = remain;
    for (iter it = remain.begin(); it != remain.end(); it++) {
        int tmp = *it;
        s.erase(tmp);
        if (used.count(s) == 0)
            subsets(used, s);
        s.insert(tmp);
    }
}

set<string> parens(int n) {
    set<string> np;
    if (n == 0) {
        np.insert("");
    }
    else {
        set<string> p = parens(n-1);
        for (set<string>::iterator it = p.begin(); it != p.end(); it++) {
            np.insert('(' + *it + ')');
            np.insert("()" + *it);
            np.insert(*it + "()");
        }
    }
    return np;
}

void parens2(string cur, int n, int open, int close) {
    if (open == n && close == n) {
        //cout << cur << endl;
        return;
    }
    if (open < n)
        parens2(cur + '(', n, open+1, close);
    if (close < open)
        parens2(cur + ')', n, open, close+1);
}

set<string> permutations(const string& s) {
    if (s.empty()) {
        set<string> one;
        one.insert(s);
        return one;
    }
     
    char first = s[0];
    set<string> subperms = permutations(s.substr(1));
    set<string> perms = set<string>();
    for (set<string>::iterator it = subperms.begin(); it != subperms.end(); it++) {
        string t = *it;
        for (int i = 0; i <= t.size(); i++)
            perms.insert(t.substr(0, i) + first + t.substr(i));
    }
    return perms;
}

int ways_problem8(int sum, int coins[], int N) {
    int *dp = new int[sum+1];
    dp[0] = 1;
    for (int j = 0; j < N; j++)
        //for (int i = sum; i >= 0; i--) // each coin ONE  time
        for (int i = 1; i <= sum; i++)   // each coin MANY time
            if (coins[j] <= i)
                dp[i] += dp[i - coins[j]];
    int ret = dp[sum];
    delete[] dp;

    return ret;
}

void fill(int col, int newcol, int i, int j, int a[][5], int N, int M) {
    if (i < 0 || i >= N || j < 0 || j >= M)
        return;
    if (a[i][j] != col) 
        return;
    a[i][j] = newcol;
    fill(col, newcol, i+1, j, a, N, M);
    fill(col, newcol, i-1, j, a, N, M);
    fill(col, newcol, i, j+1, a, N, M);
    fill(col, newcol, i, j-1, a, N, M);
}
int main() {
    //set<int> elems;
    //elems.insert(1);
    //elems.insert(2);
    //elems.insert(3);
    //set<set<int> > tmp;
    //subsets(tmp, elems);

    //set<string> ps = parens(15);
    //for (set<string>::iterator it = ps.begin(); it != ps.end(); it++)
    //    cout << *it << endl;
    //cout << ps.size() << endl;
    parens2("", 25, 0, 0);

    //set<string> sset = permutations("abc");
    //for (set<string>::iterator it = sset.begin(); it != sset.end(); it++)
    //    cout << *it << endl;

    //int coins[] = {1,5,10,25};
    //cout << ways_problem8(41, coins, 4) << endl;

    //int ar[][5] = {
    //               {0, 0, 0, 0, 0},
    //               {1, 1, 1, 1, 1},
    //               {0, 2, 0, 0, 0},
    //               {0, 3, 0, 0, 0},
    //               {0, 4, 0, 0, 0}
    //              };
    //fill(0, 7, 0, 0, ar, 5, 5);
    //for (int i = 0; i < 5; i++) {
    //    for (int j = 0; j < 5; j++)
    //        cout << ar[i][j] << " ";
    //    cout << endl;
    //}

    return 0;
}


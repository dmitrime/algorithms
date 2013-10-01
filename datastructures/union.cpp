#include <iostream>
using namespace std;

class UnionFind
{
    private:
        unsigned *id;
        unsigned *sz;
        unsigned *largest;
        unsigned N;

        unsigned root(unsigned obj) {
            unsigned x = obj;
            while (x != id[x]) {
                x = id[x];
            }
            id[obj] = x;
            return x;
        }
    public:
        UnionFind(unsigned n) : N(n) {
            id = new unsigned[N];
            sz = new unsigned[N];
            largest = new unsigned[N];
            for (int i = 0; i < N; i++) {
                id[i] = i;
                sz[i] = 1;
                largest[i] = i;
            }
        }
        ~UnionFind() {
            delete[] id;
            delete[] sz;
            delete[] largest;
        }
        bool isConnected(unsigned a, unsigned b) {
            cout << "root of " << a << " is " << root(a) << endl;
            cout << "root of " << b << " is " << root(b) << endl;
            return root(a) == root(b);
        }

        void merge(unsigned a, unsigned b) {
            unsigned ra = root(a);
            unsigned rb = root(b);
            unsigned lrg = max(find(ra), find(rb));
            if (sz[ra] < sz[rb]) {
                id[ra] = rb;
                sz[rb] += sz[ra];
                largest[rb] = lrg;
            }
            else {
                id[rb] = ra;
                sz[ra] += sz[rb];
                largest[ra] = lrg;
            }
        }
        unsigned find(unsigned x) {
            return largest[root(x)];
        }
};

int main()
{
    UnionFind uf(5);
    cout << uf.isConnected(1,2) << endl;
    cout << uf.isConnected(2,3) << endl;
    uf.merge(1,2);
    uf.merge(3,4);
    cout << uf.isConnected(1,2) << endl;
    uf.merge(1,4);
    cout << uf.isConnected(1,4) << endl;

    return 0;
}


#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

class Graph2 {
    private:
        struct Node {
            int v;
            Node *next;

            Node(int vv) : v(vv) {}
        };
        Node **G; 
        int V;

        void dfs_r(int s, int *mark) {
            mark[s] = 1;
            Node *n = G[s];
            while (n != 0) {
                if (!mark[n->v]) {
                    cout << s << " is connected to " << n->v << endl;
                    dfs_r(n->v, mark);
                }
                n = n->next;
            }
        }

    public:
        Graph2(int v) :  V(v) {
            G = new Node*[V]();
        }
        ~Graph2() {
            for (int i = 0; i < V; i++) {
                Node *start = G[i];
                while (start != 0) {
                    Node *tmp = start->next;
                    delete start;
                    start = tmp;
                }
            }
            delete[] G;
        }
        void add(int s, int e) {
            Node *n = new Node(e);
            n->next = G[s];
            G[s] = n;

            n = new Node(s);
            n->next = G[e];
            G[e] = n;
        }
        void remove(int s, int e, bool rec=true) {
            Node *n = G[s], *p = 0;
            while (n != 0) {
                if (n->v == e)
                    break;
                p = n;
                n = n->next;
            }
            if (n == 0)
                return;

            if (p == 0) G[s] = G[s]->next;
            else p->next = n->next;

            delete n;

            if (rec) 
                remove(e, s, false);
        }
        void dfs(int s) {
            int *mark = new int[V]();
            dfs_r(s, mark);
            delete[] mark;
        }

        void bfs(int s) {
            queue<int> q;
            int *mark = new int[V]();
            q.push(s);
            mark[s] = 1;
            while (!q.empty()) {
                int x = q.front();
                q.pop();

                Node *cur = G[x];
                while (cur != 0) {
                    if (!mark[cur->v]) {
                        cout << x << " is connected to " << cur->v << endl;
                        q.push(cur->v);
                        mark[cur->v] = 1;
                    }
                    cur = cur->next;
                }
            }
            delete[] mark;
        }
};

class Graph {
    private:
        int **G;
        int V;

        bool dfs_r(int s, int e, int *mark, int *path) {
            mark[s] = 1;
            if (s == e) {
                cout << "path found!" << endl;
                return true;
            }
            bool ispath = false;
            for (int i = 0; i < V; i++) {
                if (G[s][i] && !mark[i]) {
                    cout << s << " is connected to " << i << endl;
                    path[i] = s;
                    ispath |= dfs_r(i, e, mark, path);
                }
            }
            return ispath;
        }
    public:
        Graph(int v) : V(v) {
            G = new int*[V];
            for (int i = 0; i < V; i++)
                G[i] = new int[V]();
        }
        ~Graph() {
            for (int i = 0; i < V; i++)
                delete[] G[i];
            delete[] G;
        }
        void add(int v, int w) {
            G[v][w] = 1;
            G[w][v] = 1;
        }
        string itoa(int i) {
           string s;
           while (1) {
               s = char(i%10+'0') + s;
               i /= 10;
               if (i == 0) break;
           }
           return s;
        }
        void dfs(int s, int e) {
            int *mark = new int[V]();
            int *path = new int[V];
            memset(path, -1, sizeof path);
            string str;
            if (dfs_r(s, e, mark, path)) {
                int i = e;
                while (i != -1) {
                    //cout << i << (i == s ? "" : " -> ");
                    str = itoa(i) + (str.empty() ? "" : " -> ") + str;
                    i = path[i];
                }
                //cout << endl;
                cout << str << endl;
            }
            delete[] mark;
            delete[] path;
        }

        void bfs(int s, int e) {
            queue<int> q;
            int *mark = new int[V]();
            int *path = new int[V];
            memset(path, -1, sizeof path);

            bool ispath = false;
            q.push(s);
            mark[s] = 1;
            while (!q.empty()) {
                int x = q.front();
                q.pop();

                for (int u = 0; u < V; u++) {
                    if (G[x][u] && !mark[u]) {
                        cout << x << " is connected to " << u << endl;
                        q.push(u);
                        mark[u] = 1;
                        path[u] = x;
                        if (u == e) {
                            ispath = true;
                            cout << "path found" << endl;
                            break;
                        }
                    }
                }
            }
            if (ispath) {
                int i = e;
                while (i != -1) {
                    cout << i << " -> ";
                    i = path[i];
                }
                cout << endl;
            }
            delete[] mark;
            delete[] path;
        }

        void dijkstra(int s) {
            int Inf = 999;
            int *mark = new int[V]();
            int *dist = new int[V]();

            for (int u = 0; u < V; u++)
                dist[u] = Inf;
            dist[s] = 0;

            while (true) {
                int v = 0, mv = Inf;
                for (int u = 0; u < V; u++) {
                    if (!mark[u] && mv > dist[u]) {
                        v = u;
                        mv = dist[u];
                    }
                }
                if (mv == Inf)
                    break;

                mark[v] = 1;
                cout << "selected " << v << endl;

                for (int u = 0; u < V; u++)
                    if (G[v][u] && dist[u] > dist[v] + 1)
                        dist[u] = dist[v] + 1;

            }
            for (int u = 0; u < V; u++)
                cout << "dist[" << u << "] from " << s << " is " << dist[u] << endl;
            delete[] mark;
            delete[] dist;
        }
};

int main() {
    Graph g(6);
    g.add(0, 4);
    g.add(0, 3);
    g.add(2, 3);
    g.add(2, 4);
    g.add(2, 5);
    //g.add(4, 5);
    //g.remove(2,4);

    //g.dfs(0, 5);
    //g.bfs(0, 5);
    g.dijkstra(0);
    g.dijkstra2(0);
    return 0;
}


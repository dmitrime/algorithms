#include <iostream>
using namespace std;

template<typename T>
class Stack
{
    private:
        struct Node
        {
            Node *next;
            T val;
            Node(T v) : val(v), next(0) {}
        };
        Node *top;

    public:
        size_t size;

        Stack() : top(0), size(0) { }

        void push(T t) {
            if (top == 0) {
                top = new Node(t);
            }
            else {
                Node *temp = new Node(t);
                temp->next = top;
                top = temp;
            }
            size++;
        }

        T pop() {
            T t = top->val;
            Node *temp = top;
            top = top->next;
            delete temp;
            size--;

            return t;
        }

        T peek() {
            return top->val;
        }
        bool empty() {
            return size == 0;
        }
};

static const char *names[] = {"source", "destination", "auxillary"};
class Tower {
    private:
        Stack<int> disks;
        int index;
    public:
        Tower(int ind) : index(ind) {}

        void add(int disk) {
            disks.push(disk);
        }

        void moveLast(Tower *dest) {
            int last = disks.pop();
            cout << "Moving disk " << last << " from " << names[index] << " to " << names[dest->index] << endl;
            dest->add(last);
        }

        void solve(int N, Tower *dest, Tower *aux) {
            if (N == 0)
                return;
            solve(N-1, aux, dest);
            moveLast(dest);
            aux->solve(N-1, dest, this);
        }
};


int main()
{
    Tower *source = new Tower(0);
    Tower *destination = new Tower(1);
    Tower *auxillary = new Tower(2);
        
    int N = 3;
    for (int d = N-1; d >= 0; d--)
        source->add(d);

    source->solve(N, destination, auxillary);

    delete source;
    delete destination;
    delete auxillary;
    return 0;
}


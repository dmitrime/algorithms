#include <iostream>
using namespace std;

template<typename T>
class Queue
{
    private:
        struct Node
        {
            Node *next;
            T val;
            Node(T v) : val(v), next(0) {}
        };
        Node *first, *last;

    public:
        // TODO: important to set to 0!
        Queue() { first = 0; last = 0; }

        void enqueue(T t) {
            if (first == 0) {
                last = new Node(t);
                first = last;
            }
            else {
                last->next = new Node(t);
                last = last->next;
            }
        }

        T dequeue() {
            if (first == 0)
                return 0;
            T t = first->val;
            Node *temp = first;
            first = first->next;
            delete temp;

            return t;
        }
};

int main()
{
    Queue<int> q;
    q.enqueue(1); q.enqueue(2); q.enqueue(3);
    cout << q.dequeue() << endl;
    cout << q.dequeue() << endl;
    cout << q.dequeue() << endl;
    q.enqueue(4);
    cout << q.dequeue() << endl;
    return 0;
}


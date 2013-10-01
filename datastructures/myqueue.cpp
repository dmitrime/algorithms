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
            Node(T v) : val(v) {}
        };
        Node *top;

    public:
        size_t size;

        Stack() : top(0), size(0) { }

        void push(T t) {
            if (top == 0) {
                top = new Node(t);
                top->next = 0;
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

template<typename T>
class MyQueue
{
    private:
        Stack<T> st1, st2;
    public:
        void enqueue(T val) {
            st1.push(val);
        }
        
        T dequeue() {
            if (!st2.empty()) 
                return st2.pop();

            while (!st1.empty()) {
                T val = st1.pop();
                st2.push(val);
            }
            return st2.pop();
        }

        T peek() {
            if (!st2.empty()) 
                return st2.peek();

            while (!st1.empty()) {
                T val = st1.pop();
                st2.push(val);
            }
            return st2.peek();
        }
        size_t size() {
            return st1.size + st2.size;
        }
};

int main()
{
    MyQueue<int> q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4);
    cout << q.size() <<  q.dequeue() << endl;
    cout << q.dequeue() << endl;
    cout << q.dequeue() << endl;
    cout << q.dequeue() << endl;
    return 0;
}


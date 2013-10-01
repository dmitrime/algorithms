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
};

template<typename T>
class MinStack
{
    private:
        Stack<T> stack;
        Stack<pair<T,int> > minstack;
    public:
        void push(T val)
        {
            stack.push(val);
            if (minstack.size == 0)
                minstack.push(make_pair(val, stack.size));
            else {
                pair<T, int> p = minstack.peek();
                if (p.first > val)
                    minstack.push(make_pair(val, stack.size));
            }
        }
        T pop()
        {
            pair<T, int> p = minstack.peek();
            if (p.second == stack.size)
                minstack.pop();
            return stack.pop();
        }
        
        T min()
        {
            pair<T, int> p = minstack.peek();
            return p.first;
        }
};

int main()
{
    MinStack<int> st;
    st.push(1); st.push(2); st.push(3);
    cout << st.min() << endl;
    cout << st.pop() << endl;

    cout << st.min() << endl;
    cout << st.pop() << endl;

    cout << st.min() << endl;
    cout << st.pop() << endl;
    return 0;
}


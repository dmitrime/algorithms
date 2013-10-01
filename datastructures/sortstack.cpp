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


int main()
{
    Stack<int> st, st2;
    st.push(4); st.push(2); st.push(3); st.push(1);

    if (st2.empty())
        st2.push(st.pop());

    while (!st.empty())
    {
        int val = st.pop();
        if (val >= st2.peek())
            st2.push(val);
        else {
            int count = 0;
            while (!st2.empty() && val < st2.peek())
            {
                st.push(st2.pop());
                count++;
            }
            st2.push(val);
            while (count--)
                st2.push(st.pop());
        }
    }
    cout << st2.pop() << endl;
    cout << st2.pop() << endl;
    cout << st2.pop() << endl;
    cout << st2.pop() << endl;

    return 0;
}


#include <iostream>
#include <set>
using namespace std;

struct Node {
    Node *next;
    int val;
    Node(int v) : val(v) {};
};

void print_list(Node *head)
{
    while (head != 0)
    {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

void delete_list(Node *head)
{
    while (head != 0)
    {
        Node *temp = head->next;
        delete head;
        head = temp;
    }
}

Node* remove_duplicates(Node* root)
{
    if (root == 0)
        return 0;

    Node *cur = root->next;
    Node *prev = root;
    while (cur != 0)
    {
        Node *run = root;
        while (run != cur)
        {
            if (run->val == cur->val)
            {
                prev->next = cur->next;
                Node *temp = cur;
                cur = cur->next;
                delete temp;
                break;
            }
            else
                run = run->next;
        }
        if (run == cur) {
            prev = cur;
            cur = cur->next;
        }
    }

    return root;
}

Node *remove_duplicates2(Node *root)
{
    if (root == 0)
        return 0;
    Node *cur = root->next;
    Node *prev = root;
    while (cur != 0)
    {
        Node *run = root;
        while (run != cur)
        {
            if (run->val == cur->val)
            {
                prev->next = cur->next;
                Node *temp = cur;
                cur = cur->next;
                delete temp;
                break;
            }
            else
                run = run->next;
        }
        if (run == cur)
        {
            prev = cur;
            cur = cur->next;
        }
    }
    return root;
}

Node *last_nth(Node *head, int n)
{
    int size = 0;
    Node *cur = head;
    while (cur != 0)
    {
        size++;
        cur = cur->next;
    }
    if (n >= size)
        return 0;

    int pos = size - n - 1;
    cur = head;
    while (pos > 0) {
        cur = cur->next;
        pos--;
    }
    return cur;
}

bool remove_middle(Node *mid)
{
    if (mid == 0 || mid->next == 0)
        return false;

    Node *nx = mid->next;
    mid->val = nx->val;
    mid->next = nx->next;
    delete nx;

    return true;
}

Node* sum_lists(Node* list1, Node* list2)
{
    if (list1 == 0)
        return list2;
    if (list2 == 0)
        return list1;

    Node* res = new Node(0);
    Node *cur1 = list1, *cur2 = list2, *rescur = res;
    int carry = 0;
    do
    {
        rescur->next = new Node(0);
        rescur = rescur->next;
        rescur->val = cur1->val + cur2->val + carry;
        carry = rescur->val / 10;
        rescur->val %= 10;

        cur1 = cur1->next;
        cur2 = cur2->next;
    }
    while (cur1 != 0 && cur2 != 0);

    Node *further = 0;
    if (cur1 != 0) further = cur1;
    else if (cur2 != 0) further = cur2;

    if (further != 0)
    {
        while (further != 0)
        {
            rescur->next = new Node(carry + further->val);
            rescur = rescur->next;
            carry = rescur->val / 10;
            rescur->val %= 10;

            further = further->next;
        }
    }
    if (carry) 
    {
        rescur->next = new Node(carry);
        rescur = rescur->next;
    }
    rescur->next = 0;
    rescur = res;
    res = res->next;
    delete rescur;

    return res;
}

Node *loop_beginning(Node *circ)
{
    set<Node*> save;
    Node *cur = circ;
    while (cur != 0) {
        if (save.count(cur) == 0)
            save.insert(cur);
        else
            break;
        cur = cur->next;
    }
    return cur;
}

Node *loop_beginning2(Node *circ)
{
    if (circ == 0)
        return 0;
    Node *n1 = circ;
    Node *n2 = circ;
    while (n2 && n2->next != 0) {
        n1 = n1->next;
        n2 = n2->next->next;
        if (n1 == n2)
            break;
    }
    if (n2 == 0 || n2->next == 0)
        return 0;
    n1 = circ;
    while (n1 != n2) {
        n1 = n1->next;
        n2 = n2->next;
    }
    return n1;
}

Node* reverse_list(Node* start) {
    if (start == 0 || start->next == 0)
        return start;

    // new head
    Node *it = 0, *cur = start;

    // walk the list
    while (cur != 0) {
        // save the current next
        Node *tmp = cur->next;
        // make current point to the reversed chain
        cur->next = it;
        // new head points to the start
        it = cur;
        // go further
        cur = tmp;
    }
    return it;
}

int main()
{
    Node *n1 = new Node(3);
    Node *n2 = new Node(1);
    Node *n3 = new Node(5);
    n1->next = n2; n2->next = n3; n3->next = 0;
    Node *v1 = new Node(9);
    Node *v2 = new Node(2);
    Node *v3 = new Node(9);
    Node *v4 = new Node(2);
    v1->next = v2; v2->next = v3; v3->next = v4; v4->next = 0;

    Node *head = reverse_list(n1);
    print_list(head);

    //Node *head1 = remove_duplicates2(v1);
    //print_list(head1);

    //Node *head = last_nth(n1, 3);
    //Node *head = n1;
    //remove_middle(n2);

    //Node *head = sum_lists(n1, v1);
    //print_list(head);
    //delete_list(head);

    //n3->next = v1;
    //v3->next = v2;
    //Node *head = loop_beginning2(n1);
    //cout << head->val << endl;

    delete n1; delete n2; delete n3;
    delete v1; delete v2; delete v3;
    return 0;
}


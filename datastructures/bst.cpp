#include <iostream>
#include <queue>
#include <list>
using namespace std;

struct Node {
    Node *link[2];
    int data;
    Node() {}
    Node(int d) : data(d) {}
};

struct Tree {
    Node *root;
};

int bst_find_r(Node *root, int data) {
    if (root == 0)
        return 0;
    else if (root->data == data)
        return 1;
    else {
        int dir = data > root->data;
        return bst_find_r(root->link[dir], data);
    }
}

int bst_find(Node *root, int data) {
    Node *it = root;
    while (it != 0) {
        if (it->data == data) 
            return 1;
        else {
            int dir = data > it->data;
            it = it->link[dir];
        }
    }
    return 0;
}

Node* bst_insert_r(Node *root, int data) {
    if (root == 0)
        return new Node(data);
    else if (root->data == data)
        return root;
    else {
        int dir = data > root->data;
        root->link[dir] = bst_insert_r(root->link[dir], data);
        return root;
    }
}

int bst_insert(Tree *tree, int data) {
    if (tree->root == 0) 
        tree->root = new Node(data);
    else {
        Node *it = tree->root;
        int dir;
        while (true) {
            if (it->data == data)
                return 0;

            dir = data > it->data;
            if (it->link[dir] == 0)
                break;
            it = it->link[dir];
        }
        it->link[dir] = new Node(data);
    }
    return 1;
}

void bst_traverse_in(Node *root) {
    if (root == 0)
        return;
    bst_traverse_in(root->link[0]);
    cout << root->data << endl;
    bst_traverse_in(root->link[1]);
}

void bst_traverse_pre(Node *root) {
    if (root == 0)
        return;
    cout << root->data << endl;
    bst_traverse_pre(root->link[0]);
    bst_traverse_pre(root->link[1]);
}

int depth(Node *root, bool is_max) {
    if (root == 0) 
        return 0;
    if (is_max)
        return 1 + max(depth(root->link[0], is_max), depth(root->link[1], is_max));
    else
        return 1 + min(depth(root->link[0], is_max), depth(root->link[1], is_max));
}

bool bst_is_balanced(Tree *tree) {
    int mx_depth = depth(tree->root, true);
    int mn_depth = depth(tree->root, false);
    return mx_depth - mn_depth <= 1;
}

bool bst_is_correct(Node *root) {
    if (root == 0)
        return true;

    if (root->link[0] == 0 && root->link[1] == 0)
        return true;

    if (root->link[0] == 0 && root->link[1] != 0) 
    {
        if (root->data < root->link[1]->data)
            return bst_is_correct(root->link[1]);
        else
            return false;
    }

    if (root->link[1] == 0 && root->link[0] != 0) 
    {
        if (root->data > root->link[0]->data)
            return bst_is_correct(root->link[0]);
        else
            return false;
    }
            
    if (root->data > root->link[0]->data && root->data < root->link[1]->data)
        return bst_is_correct(root->link[0]) && bst_is_correct(root->link[1]);
    else 
        return false;
}

Node* bst_from_array_r(int ar[], int lo, int hi) {
    if (lo > hi)
        return 0;

    int mid = lo + (hi-lo)/2;
    Node *node = new Node(ar[mid]);
    node->link[0] = bst_from_array_r(ar, lo, mid-1);
    node->link[1] = bst_from_array_r(ar, mid+1, hi);
    return node;
}

Tree* bst_from_array(int ar[], int N) {
    Tree *t = new Tree();
    t->root = bst_from_array_r(ar, 0, N-1);
    return t;
}

void bst_delete(Tree *tree, int key) {
    if (tree->root != 0) {
        Node *p = 0;
        Node *it = tree->root;

        while (true) {
            if (it == 0)
                return;
            if (it->data == key)
                break;
            int dir = key > it->data;
            p = it;
            it = it->link[dir];
        }

        if (it->link[0] != 0 && it->link[1] != 0) {
            p = it;
            Node *n = it->link[1];

            while (n->link[0] != 0) {
                p = n;
                n = n->link[0];
            }

            it->data = n->data;
            if (p->link[1] == n) 
                p->link[1] = n->link[1];
            else
                p->link[0] = n->link[1];

            delete n;
        }
        else {
            int dir = it->link[0] == 0;
            if (p == 0)
                tree->root = it->link[dir];
            else if (p->link[0] == it)
                p->link[0] = it->link[dir];
            else if (p->link[1] == it) 
                p->link[1] = it->link[dir];

            delete it;
        }
    }
}

void bst_destroy(Node *node) {
    if (node == 0)
        return;
    bst_destroy(node->link[0]);
    bst_destroy(node->link[1]);
    delete(node);
}

void bst_by_level(Tree *tree) {
    queue<Node*> q;
    q.push(tree->root);
    int level = 0;
    while (!q.empty()) {
        list<int> lst;
        queue<Node*> qq;

        while (!q.empty()) {
            Node* p = q.front();
            q.pop();
            lst.push_back(p->data);

            if (p->link[0] != 0)
                qq.push(p->link[0]);
            if (p->link[1] != 0)
                qq.push(p->link[1]);
        }
        
        cout << "level " << level << endl;
        for (list<int>::iterator it = lst.begin(); it != lst.end(); it++) {
            cout << *it << " " << endl;
        }

        level++;
        q = qq;
    }
}

Node* bst_lca(Node *root, Node* p, Node* q) {
    if (root == 0)
        return 0;
    if (root == p || root == q)
        return root;
    Node *l = bst_lca(root->link[0], p, q);
    Node *r = bst_lca(root->link[1], p, q);
    if (l && r)
        return root;
    
    return l ? l : r;
}

TreeNode *buildRec(int pre[], int in[], int n, int off) {
    if (n == 0)
        return 0;
    int elem = pre[0];
    int i    = indices[elem]-off;
    TreeNode *root = new TreeNode(elem);
    root->left = buildRec(pre+1, in, i, off);
    root->right = buildRec(pre+i+1, in+i+1, n-i-1, off+i+1);
    return root;
}

/*
 * Example args: 
 *[2,1,4,3], [1,2,3,4]	{2,1,4,#,#,3}	{2,1,4,#,#,3}	
 *[3,1,2,4], [1,2,3,4]	{3,1,4,#,2}	{3,1,4,#,2}	
 *[3,2,1,4], [1,2,3,4]	{3,2,4,1}	{3,2,4,1}
 */
TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
    int N = (int)preorder.size();
    int in[N], pre[N];
    for (int i = 0; i < inorder.size(); i++) {
        indices[ inorder[i] ] = i;
        in[i] = inorder[i];
        pre[i] = preorder[i];
    }
    return buildRec(pre, in, N, 0);
}

int main()
{
    Tree *tree = new Tree();
    bst_insert(tree, 5);
    bst_insert(tree, 4);
    bst_insert(tree, 2);
    bst_insert(tree, 0);
    bst_insert(tree, 3);
    bst_insert(tree, 6);
    bst_insert(tree, 7);

    bst_by_level(tree);
    
    //bst_traverse_in(tree->root);
    //cout << endl;
    //bst_delete(tree, 3);
    //bst_delete(tree, 5);
    //bst_delete(tree, 4);
    //bst_traverse_in(tree->root);

    bst_destroy(tree->root);
    //cout << bst_is_balanced(tree) << endl;
    delete tree;

    //int ar[] = {0,1,2,3,4,5,6,7};
    //int N = 8;
    //Tree *tr = bst_from_array(ar, N);
    //bst_traverse_pre(tr->root);
    //tr->root->link[0]->link[0]->data = 10;
    //cout << bst_is_correct(tr->root) << endl;

    return 0;
}


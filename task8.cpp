
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

struct Node {
    int val;
    Node *left = nullptr, *right = nullptr;
    Node(int v) : val(v) {}
};

void insert(Node*& root, int v) {
    if (!root) { root = new Node(v); return; }
    if (v == root->val) return;
    insert(v < root->val ? root->left : root->right, v);
}

int height(Node* r) { return r ? 1 + max(height(r->left), height(r->right)) : -1; }

bool sameShape(Node* a, Node* b) {
    if (!a && !b) return true;
    if (!a || !b) return false;
    return sameShape(a->left, b->left) && sameShape(a->right, b->right);
}


struct InIter {
    stack<Node*> st;
    InIter(Node* r) { push(r); }
    void push(Node* n) { while (n) { st.push(n); n = n->left; } }
    bool has() const { return !st.empty(); }
    int peek() const { return st.top()->val; }
    void next() { Node* n = st.top(); st.pop(); push(n->right); }
};

void show(const char* label, const vector<int>& v) {
    cout << label;
    for (size_t i = 0; i < v.size(); i++) cout << (i ? " " : "") << v[i];
    cout << "\n";
}

int main() {
    int a[] = {40, 20, 60, 10, 30, 50, 70};
    int b[] = {30, 20, 55, 10, 40, 60, 75};
    Node *A = nullptr, *B = nullptr;
    for (int x : a) insert(A, x);
    for (int x : b) insert(B, x);

    vector<int> both, onlyA, onlyB;
    InIter ia(A), ib(B);
    while (ia.has() || ib.has()) {
        if (!ib.has() || (ia.has() && ia.peek() < ib.peek())) { onlyA.push_back(ia.peek()); ia.next(); }
        else if (!ia.has() || ib.peek() < ia.peek())          { onlyB.push_back(ib.peek()); ib.next(); }
        else { both.push_back(ia.peek()); ia.next(); ib.next(); }
    }
    show("Both: ", both);
    show("Only A: ", onlyA);
    show("Only B: ", onlyB);
    cout << "Height A is " << height(A) << ", height B is " << height(B) << "\n";
    cout << "Same shape: " << (sameShape(A, B) ? "Yes" : "No") << "\n";
}

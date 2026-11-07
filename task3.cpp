
#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
    int val;
    Node *left = nullptr, *right = nullptr;
    Node(int v) : val(v) {}
};

void insert(Node*& root, int v) {
    if (!root) { root = new Node(v); return; }
    insert(v < root->val ? root->left : root->right, v);
}

int noneCnt = 0, oneCnt = 0, twoCnt = 0;

Node* removeNode(Node* r, int key) {
    if (!r) { cout << key << " Code not found\n"; return nullptr; }
    if (key < r->val) { r->left = removeNode(r->left, key); return r; }
    if (key > r->val) { r->right = removeNode(r->right, key); return r; }

    if (!r->left && !r->right) {
        cout << key << " no sub-branch\n"; noneCnt++;
        delete r; return nullptr;
    }
    if (!r->left || !r->right) {
        cout << key << " one sub-branch\n"; oneCnt++;
        Node* child = r->left ? r->left : r->right;
        delete r; return child;
    }
    Node* s = r->right;
    while (s->left) s = s->left;
    cout << key << " two sub-branches, replaced by " << s->val << "\n"; twoCnt++;
    int sv = s->val;

    int a = noneCnt, b = oneCnt;
    streambuf* old = cout.rdbuf(nullptr);
    r->right = removeNode(r->right, sv);
    cout.rdbuf(old);
    noneCnt = a; oneCnt = b;
    r->val = sv;
    return r;
}

void preorder(Node* r, bool& first) {
    if (!r) return;
    cout << (first ? "" : " ") << r->val; first = false;
    preorder(r->left, first); preorder(r->right, first);
}

int height(Node* r) { return r ? 1 + max(height(r->left), height(r->right)) : -1; }

int main() {
    int tree[] = {50, 30, 70, 20, 40, 60, 80, 35, 45, 65};
    int rem[] = {20, 70, 30, 50, 99};
    Node* root = nullptr;
    for (int x : tree) insert(root, x);
    for (int c : rem) root = removeNode(root, c);

    cout << "Remaining: ";
    bool first = true;
    preorder(root, first);
    cout << "\nHeight " << height(root) << "\n";
    cout << "Kinds: none " << noneCnt << ", one " << oneCnt << ", two " << twoCnt << "\n";
}

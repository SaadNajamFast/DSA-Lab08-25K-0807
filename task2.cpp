
#include <iostream>
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

void query(Node* root, int key) {
    Node* cur = root;
    int compared = 0;
    const Node *smaller = nullptr, *bigger = nullptr;
    bool found = false;
    while (cur) {
        compared++;
        if (key == cur->val) { found = true; break; }
        if (key < cur->val) { bigger = cur; cur = cur->left; }
        else { smaller = cur; cur = cur->right; }
    }
    cout << key << ": ";
    if (found) { cout << "Found, " << compared << " compared.\n"; return; }
    cout << "Not found, " << compared << " compared, smaller ";
    if (smaller) cout << smaller->val; else cout << "None";
    cout << ", bigger ";
    if (bigger) cout << bigger->val; else cout << "None";
    cout << ".\n";
}

int main() {
    int tree[] = {45, 20, 60, 10, 30, 50, 70, 25, 35};
    int queries[] = {35, 55, 5, 70};
    Node* root = nullptr;
    for (int x : tree) insert(root, x);
    for (int q : queries) query(root, q);
}

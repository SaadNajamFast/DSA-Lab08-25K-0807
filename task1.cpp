
#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int val;
    Node *left = nullptr, *right = nullptr;
    Node(int v) : val(v) {}
};


bool insert(Node*& root, int v) {
    if (!root) { root = new Node(v); return true; }
    if (v == root->val) return false;
    return insert(v < root->val ? root->left : root->right, v);
}

void inorder(Node* r, vector<int>& out) {
    if (!r) return;
    inorder(r->left, out); out.push_back(r->val); inorder(r->right, out);
}


void preorder(Node* r, vector<int>& out) {
    if (!r) return;
    out.push_back(r->val); preorder(r->left, out); preorder(r->right, out);
}

bool same(Node* a, Node* b) {
    if (!a && !b) return true;
    if (!a || !b) return false;
    return a->val == b->val && same(a->left, b->left) && same(a->right, b->right);
}

void print(const char* label, const vector<int>& v) {
    cout << label;
    for (size_t i = 0; i < v.size(); i++) cout << (i ? " " : "") << v[i];
    cout << "\n";
}

int main() {
    int input[] = {50, 30, 70, 20, 40, 60, 80, 30, 65};
    Node* root = nullptr;
    for (int t : input)
        if (!insert(root, t)) cout << "Already issued: " << t << "\n";

    vector<int> calling, backup;
    inorder(root, calling);
    print("Calling list: ", calling);
    preorder(root, backup);
    print("Backup list: ", backup);

    Node* second = nullptr;
    for (int t : backup) insert(second, t);
    cout << (same(root, second) ? "Backup is safe" : "Backup is wrong") << "\n";
}

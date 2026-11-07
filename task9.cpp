
#include <iostream>
#include <vector>
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

int countNodes(Node* r) { return r ? 1 + countNodes(r->left) + countNodes(r->right) : 0; }

int visited;
void range(Node* n, int lo, int hi, vector<int>& out) {
    if (!n) return;
    visited++;
    if (n->val > lo) range(n->left, lo, hi, out);
    if (n->val >= lo && n->val <= hi) out.push_back(n->val);
    if (n->val < hi) range(n->right, lo, hi, out);
}

int main() {
    int data[] = {500, 300, 800, 200, 400, 700, 900, 100, 250, 350, 450, 600};
    Node* root = nullptr;
    for (int x : data) insert(root, x);
    int total = countNodes(root);

    int ranges[][2] = {{350, 700}, {610, 650}};
    for (auto& r : ranges) {
        vector<int> out;
        visited = 0;
        range(root, r[0], r[1], out);
        cout << "for range " << r[0] << " to " << r[1] << ": ";
        if (out.empty()) cout << "no amounts";
        for (size_t i = 0; i < out.size(); i++) cout << (i ? " " : "") << out[i];
        cout << ", count " << out.size() << ", looked at " << visited << " of " << total << " nodes.\n";
    }
}

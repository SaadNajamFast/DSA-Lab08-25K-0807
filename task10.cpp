
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


int depthOf(Node* r, int key) {
    int d = 0;
    while (r) {
        if (key == r->val) return d;
        r = key < r->val ? r->left : r->right;
        d++;
    }
    return -1;
}

Node* lca(Node* r, int a, int b) {
    while (r) {
        if (a < r->val && b < r->val) r = r->left;
        else if (a > r->val && b > r->val) r = r->right;
        else return r;
    }
    return nullptr;
}

int main() {
    int data[] = {50, 30, 70, 20, 40, 60, 80, 35, 45};
    Node* root = nullptr;
    for (int x : data) insert(root, x);

    int pairs[][2] = {{35, 45}, {20, 60}, {30, 35}, {35, 99}};
    for (auto& p : pairs) {
        int a = p[0], b = p[1];
        cout << "(" << a << ", " << b << "): ";
        int da = depthOf(root, a), db = depthOf(root, b);
        if (da < 0 || db < 0) { cout << "Employee not found\n"; continue; }
        Node* boss = lca(root, a, b);
        int dl = depthOf(root, boss->val);
        cout << "boss " << boss->val << ", distance " << (da + db - 2 * dl) << "\n";
    }
}

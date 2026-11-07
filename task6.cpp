
#include <iostream>
#include <vector>
#include <map>
using namespace std;

struct Node {
    int id;
    Node *left = nullptr, *right = nullptr;
    Node(int i) : id(i) {}
};

struct Line { int p, c; char s; };



bool check(Node* n, Node* lo, Node* hi, int& badId, int& badAnc) {
    if (!n) return true;
    if (lo && n->id <= lo->id) { badId = n->id; badAnc = lo->id; return false; }
    if (hi && n->id >= hi->id) { badId = n->id; badAnc = hi->id; return false; }
    return check(n->left, lo, n, badId, badAnc) && check(n->right, n, hi, badId, badAnc);
}

void solve(int no, const vector<Line>& lines) {
    map<int, Node*> nodes;
    map<int, bool> isChild;
    auto get = [&](int id) { if (!nodes.count(id)) nodes[id] = new Node(id); return nodes[id]; };
    for (auto& l : lines) {
        Node *p = get(l.p), *c = get(l.c);
        (l.s == 'L' ? p->left : p->right) = c;
        isChild[l.c] = true;
    }
    Node* root = nullptr;
    for (auto& kv : nodes) if (!isChild[kv.first]) root = kv.second;

    int badId = 0, badAnc = 0;
    cout << "Tree " << no << ": ";
    if (check(root, nullptr, nullptr, badId, badAnc)) cout << "Valid.\n";
    else cout << "Invalid, first wrong ID " << badId << ", it disagrees with " << badAnc << ".\n";
}

int main() {
    solve(1, {{20,10,'L'},{20,30,'R'},{10,5,'L'},{10,25,'R'},{30,35,'R'}});
    solve(2, {{40,20,'L'},{40,60,'R'},{20,30,'R'},{60,50,'L'},{60,70,'R'}});
}


#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

struct Node {
    int id;
    Node *left = nullptr, *right = nullptr;
    Node(int i) : id(i) {}
};

struct Line { int p, c; char s; };

void solve(char name, const vector<Line>& lines) {
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


    bool full = true;
    vector<int> free;
    for (auto& kv : nodes) {
        int id = kv.first; Node* n = kv.second;
        if ((n->left == nullptr) != (n->right == nullptr)) { full = false; free.push_back(id); }
    }


    bool complete = true, gap = false;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* n = q.front(); q.pop();
        if (!n) { gap = true; continue; }
        if (gap) { complete = false; break; }
        q.push(n->left);
        q.push(n->right);
    }

    cout << name << ": Full " << (full ? "Yes" : "No")
         << ", Neat " << (complete ? "Yes" : "No") << ", free pass ";
    if (free.empty()) cout << "None";
    for (size_t i = 0; i < free.size(); i++) cout << (i ? " " : "") << free[i];
    cout << "\n";
}

int main() {
    solve('B', {{1,2,'L'},{1,3,'R'},{2,4,'L'},{2,5,'R'},{3,6,'L'}});
    solve('C', {{1,2,'L'},{1,3,'R'},{3,6,'L'},{3,7,'R'}});
    solve('D', {{1,2,'L'},{1,3,'R'},{2,4,'L'},{2,5,'R'},{3,7,'R'}});
}

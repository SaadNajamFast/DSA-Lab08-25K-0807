
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

struct Node {
    int id;
    Node *left = nullptr, *right = nullptr, *parent = nullptr;
    Node(int i) : id(i) {}
};

map<int, Node*> nodes;

Node* get(int id) {
    if (!nodes.count(id)) nodes[id] = new Node(id);
    return nodes[id];
}

int main() {
    struct Line { int m, e; char s; };
    vector<Line> lines = {{1,2,'L'},{1,3,'R'},{2,4,'L'},{2,5,'R'},{3,6,'R'},
                          {5,7,'L'},{6,8,'L'},{6,9,'R'},{8,10,'L'}};
    for (auto& l : lines) {
        Node *m = get(l.m), *e = get(l.e);
        (l.s == 'L' ? m->left : m->right) = e;
        e->parent = m;
    }
    Node* root = nodes[1];


    queue<pair<Node*, int>> q;
    q.push({root, 0});
    vector<vector<int>> levels;
    while (!q.empty()) {
        Node* n = q.front().first; int d = q.front().second; q.pop();
        if ((int)levels.size() <= d) levels.push_back({});
        levels[d].push_back(n->id);
        if (n->left) q.push({n->left, d + 1});
        if (n->right) q.push({n->right, d + 1});
    }
    for (size_t i = 0; i < levels.size(); i++) {
        cout << "Level " << i << ":";
        for (int x : levels[i]) cout << " " << x;
        cout << "\n";
    }
    cout << "Height " << levels.size() - 1 << "\n";


    vector<int> leaves;
    for (auto& kv : nodes) if (!kv.second->left && !kv.second->right) leaves.push_back(kv.first);
    sort(leaves.begin(), leaves.end());
    cout << "No one under them:";
    for (int x : leaves) cout << " " << x;
    cout << "\n";


    for (int target : {10, 5}) {
        Node* n = nodes[target];
        vector<int> chain;
        for (Node* c = n; c; c = c->parent) chain.push_back(c->id);
        reverse(chain.begin(), chain.end());
        cout << "For " << target << ": chain";
        for (int x : chain) cout << " " << x;
        cout << ", colleague ";
        Node* p = n->parent;
        Node* sib = p ? (p->left == n ? p->right : p->left) : nullptr;
        if (sib) cout << sib->id; else cout << "None";
        cout << "\n";
    }
}

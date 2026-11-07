
#include <iostream>
#include <vector>
#include <map>
using namespace std;

struct Node {
    int id, coins = 0;
    Node *left = nullptr, *right = nullptr;
    Node(int i) : id(i) {}
};

map<int, Node*> nodes;
Node* get(int id) {
    if (!nodes.count(id)) nodes[id] = new Node(id);
    return nodes[id];
}

int routes = 0;
long long bestSum;
bool haveBest = false;
vector<int> bestPath, cur;

void dfs(Node* n, long long sum) {
    cur.push_back(n->id);
    sum += n->coins;
    if (!n->left && !n->right) {
        routes++;
        if (!haveBest || sum > bestSum) {
            haveBest = true; bestSum = sum; bestPath = cur;
        }
    } else {
        if (n->left) dfs(n->left, sum);
        if (n->right) dfs(n->right, sum);
    }
    cur.pop_back();
}

int main() {
    struct Line { int m, e; char s; };
    vector<Line> lines = {{1,2,'L'},{1,3,'R'},{2,4,'L'},{2,5,'R'},{3,6,'R'},
                          {5,7,'L'},{6,8,'L'},{6,9,'R'},{8,10,'L'}};
    for (auto& l : lines) {
        Node *m = get(l.m), *e = get(l.e);
        (l.s == 'L' ? m->left : m->right) = e;
    }
    int coins[] = {0, 5, -3, 4, 6, 2, -2, 9, 3, 1, -1};
    for (auto& kv : nodes) kv.second->coins = coins[kv.first];

    dfs(nodes[1], 0);
    cout << routes << " routes\n";
    cout << "Best route:";
    for (int x : bestPath) cout << " " << x;
    cout << " with " << bestSum << " coins\n";
}

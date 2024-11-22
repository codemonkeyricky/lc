#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};

TreeNode* recurse(vector<int>& tree, int k) {
    if (k >= tree.size() || tree[k] == -1)
        return nullptr;

    return new TreeNode(tree[k], recurse(tree, k * 2 + 1),
                        recurse(tree, k * 2 + 2));
}

TreeNode* populate(vector<int>& tree) { return recurse(tree, 0); }

void pvi(vector<int>& v) {

    for (auto& vv : v)
        cout << vv << ", ";
    cout << endl;
}

using vi = vector<int>;
using vvi = vector<vector<int>>;
using vll = vector<long long>;
using vvll = vector<vector<long long>>;

class MyHashMap {
    struct Node {
        Node(int k, int v) : k(k), v(v), n(nullptr) {}
        int k;
        int v;
        Node* n;
    };

    vector<Node*> nodes;
    int n;

  public:
    MyHashMap() {
        n = 10000;
        nodes = vector<Node*>(n);
    }

    void put(int key, int value) {

        Node* p = nullptr;
        Node* c = nodes[key % n];
        while (c) {
            if (c->k == key) {
                c->v = value;
                return;
            }
            p = c;
            c = c->n;
        }

        if (p) {
            p->n = new Node(key, value);
        } else {
            nodes[key % n] = new Node(key, value);
        }
    }

    int get(int key) {
        Node* c = nodes[key % n];
        while (c) {
            if (c->k == key) {
                return c->v;
            }
            c = c->n;
        }
        return -1;
    }

    void remove(int key) {
        Node* p = nullptr;
        Node* c = nodes[key % n];
        while (c) {

            if (c->k == key) {
                if (p) {
                    p->n = c->n;
                    delete c;
                } else {
                    auto c = nodes[key % n];
                    nodes[key % n] = c->n;
                    delete c;
                }
                return;
            }

            p = c;
            c = c->n;
        }
    }
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */

int main() {
    // Solution sol;
    int r;

    cout << r << endl;
}

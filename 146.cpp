#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cmath>
#include <iostream>
#include <list>
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

class LRUCache {

    int cap = 0;

    list<int> lru; ///< list of keys
    unordered_map<int, pair<int, list<int>::iterator>>
        kv; ///< key / [value, it]

    void refresh(int key) {
        auto it = kv[key].second;
        lru.erase(it);
        lru.push_back(key);
        it = prev(lru.end());
        kv[key].second = it;
    }

  public:
    LRUCache(int capacity) { cap = capacity; }

    int get(int key) {
        if (kv.count(key)) {
            refresh(key);
            return kv[key].first;
        }
        return -1;
    }

    void put(int key, int value) {

        if (kv.count(key)) {
            /* key exists */
            kv[key].first = value;
            refresh(key);
        } else { ///< kv.size() == cap
            while (kv.size() >= cap) {
                auto k = lru.front();
                lru.pop_front();
                kv.erase(k);
            }

            lru.push_back(key);
            auto it = prev(lru.end());
            kv[key] = {value, it};
        }
    }
};

int main() {
    LRUCache lru(2);

    lru.put(1, 1);

    // cout << r << endl;
}

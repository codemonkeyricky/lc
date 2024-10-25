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

class LRUCache {
    int tick = 0;
    int cap = 0;

    unordered_map<int, array<int, 2>> kv; ///< key / [value, tick]
    list<array<int, 2>> age;              ///< key / tick

  public:
    LRUCache(int capacity) {
        cap = capacity;
        tick = 0;
    }

    int get(int key) {
        if (kv.count(key)) {
            kv[key][1] = tick;
            age.push_back({key, tick});
            ++tick;
            return kv[key][0];
        }
        return -1;
    }

    void put(int key, int value) {

        if (kv.count(key) || kv.size() < cap) {
            kv[key] = {value, tick};
            age.push_back({key, tick});
        } else { ///< kv.size() == cap
            while (kv.size() >= cap) {
                while (age.size()) {
                    auto [k, t] = age.front();
                    age.pop_front();
                    if (!kv.count(k)) {
                        /* key already removed - stale age entry */
                    } else /* k exists */ {
                        if (t < kv[k][1]) {
                            /* key has been accessed since - stale entry */
                        } else {
                            /* unused for a long time - make space */
                            kv.erase(k);
                            break;
                        }
                    }
                }
            }

            kv[key] = {value, tick};
            age.push_back({key, tick});
        }

        ++tick;
    }
};

int main() {
    // Solution sol;
    // int r;

    cout << r << endl;
}

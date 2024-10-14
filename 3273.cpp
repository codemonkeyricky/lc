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

class Solution {
  public:
    long long minDamage(int power, vector<int>& damage, vector<int>& health) {
        int n = damage.size();

        vector<int> order;
        for (auto i = 0; i < n; ++i) {
            order.push_back(i);
        }

        sort(order.begin(), order.end(), [&](int l, int r) {
            auto turns_left = (health[l] + power - 1) / power;
            auto turns_right = (health[r] + power - 1) / power;

            auto kill_left =
                turns_left * damage[l] + (turns_left + turns_right) * damage[r];
            auto kill_right =
                turns_right * damage[r] + (turns_left + turns_right) * damage[l];

            return kill_left < kill_right;
        });

        auto total = accumulate(damage.begin(), damage.end(), 0ll);

        long long rv = 0;
        for (auto& k : order) {
            int turns = (health[k] + power - 1) / power;
            rv += turns * total;
            total -= damage[k];
        }
        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.minDamage(62, vi() = {80, 79}, vi() = {86, 13});
    cout << r << endl;

    // r = sol.minDamage(1, vi() = {1, 1, 1, 1}, vi() = {1, 2, 3, 4});
    // cout << r << endl;

    r = sol.minDamage(4, vi() = {1, 2, 3, 4}, vi() = {4, 5, 6, 7});
    cout << r << endl;
}

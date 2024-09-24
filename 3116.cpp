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

class Solution {

    void get_set(vector<int>& coins, ///< set of coins
                 int k,              ///< current index
                 int cnt,            ///< how many more coins
                 long long limit,
                 long long mul, ///< current value
                 vector<long long>& rv) {
        if (mul > limit)
            return;

        if (cnt == 0) {
            rv.push_back(mul);
            return;
        }

        if (k >= coins.size())
            return;

        // skip current
        get_set(coins, k + 1, cnt, limit, mul, rv);

        // include current
        get_set(coins, k + 1, cnt - 1, limit, mul * coins[k], rv);
    }

    long long get_kth(vector<int>& coins, long long m) {
        long long kth = 0;
        for (auto& c : coins)
            kth += m / c;

        for (auto k = 2; k <= coins.size(); ++k) {
            vector<long long> set;
            get_set(coins, 0, k, m, 1, set);
            for (auto& c : set)
                kth -= m / c;
        }

        return kth;
    }

  public:
    long long findKthSmallest(vector<int>& coins, int k) {

        /* Find set of coins not factors of each other */
        sort(begin(coins), end(coins));
        vector<int> new_coins;
        for (int i = coins.size() - 1; i >= 0; --i) {
            int pass = true;
            for (auto k = 0; k < i; ++k)
                if (coins[i] % coins[k] == 0)
                    pass = false;
            if (pass)
                new_coins.push_back(coins[i]);
        }
        swap(coins, new_coins);

        long long l = 1, r = 1e15;
        while (l < r) {
            auto m = (l + r) / 2;
            auto kth = get_kth(coins, m);

            if (kth >= k)
                r = m;
            else
                l = m + 1;
        }

        return l;
    }
};

int main() {
    Solution sol;
    long long r;

    r = sol.findKthSmallest(vector<int>() = {5, 2}, 7);
    cout << r << endl;

    r = sol.findKthSmallest(vector<int>() = {3, 6, 9}, 3);
    cout << r << endl;
}

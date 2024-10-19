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
    int candy(vector<int>& ratings) {

        int n = ratings.size();

        priority_queue<array<int, 2>> q;
        for (auto i = 0; i < n; ++i) {
            q.push({-ratings[i], i});
        }

        vector<int> candies(n, 0);
        while (q.size()) {
            auto [r, k] = q.top();
            r *= -1;
            q.pop();

            int candy = 1;
            if (k) {
                if (candies[k - 1] && ratings[k - 1] < r)
                    candy = candies[k - 1] + 1;
            }

            if (k + 1 < n) {
                if (candies[k + 1] && r > ratings[k + 1])
                    candy = max(candy, candies[k + 1] + 1);
            }

            candies[k] = candy;
        }

        return accumulate(candies.begin(), candies.end(), 0);
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.candy(vector<int>() = {1, 2, 2});
    cout << r << endl;

    r = sol.candy(vector<int>() = {1, 0, 2});
    cout << r << endl;
}

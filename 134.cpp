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
  public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();
        vector<int> diff;
        for (auto i = 0; i < n; ++i)
            diff.push_back(gas[i] - cost[i]);

        vector<int> sum;
        for (auto i = 0; i < n; ++i)
            sum.push_back(diff[i] + (i ? sum[i - 1] : 0));

        if (sum[n - 1] < 0)
            return -1;

        auto mmin = min_element(sum.begin(), sum.end()) - sum.begin();
        return (mmin + 1) % n;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.canCompleteCircuit(vector<int>() = {1, 2, 3, 4, 5},
                               vector<int>() = {3, 4, 5, 1, 2});
    cout << r << endl;
}

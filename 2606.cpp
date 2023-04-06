#include <iostream>
#include <vector>
#include <cassert>
#include <stack>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <bitset>
#include <numeric>
#include <cmath>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

TreeNode *recurse(vector<int> &tree, int k)
{
    if (k >= tree.size() || tree[k] == -1)
        return nullptr;

    return new TreeNode(tree[k], recurse(tree, k * 2 + 1), recurse(tree, k * 2 + 2));
}

TreeNode *populate(vector<int> &tree)
{
    return recurse(tree, 0);
}

class Solution
{
public:
    int maximumCostSubstring(string s, string chars, vector<int> &vals)
    {
        vector<int> cost(26);
        for (auto i = 0; i < 26; ++i)
            cost[i] = i + 1;

        for (auto i = 0; i < chars.size(); ++i)
            cost[chars[i] - 'a'] = vals[i];

        vector<int> arr;
        for (auto &c : s)
            arr.push_back(cost[c - 'a']);

        int rv = 0, sum = 0;
        for (auto &n : arr)
        {
            sum += n;
            if (sum <= 0)
                sum = 0;
            rv = max(sum, rv);
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maximumCostSubstring("talaqlt", "tqla", vector<int>() = {4, 3, 3, -2});
    cout << r << endl;

    r = sol.maximumCostSubstring("adaa", "d", vector<int>() = {-1000});
    cout << r << endl;
}
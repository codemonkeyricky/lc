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
    vector<int> smallestTrimmedNumbers(vector<string> &nums, vector<vector<int>> &queries)
    {
        vector<array<int,3>> qrs;
        for (auto i = 0; i < queries.size(); ++i)
            qrs.push_back({queries[i][1], queries[i][0], i});
        sort(begin(qrs), end(qrs));

        int n = nums[0].size(), k = 0, mul = 1, q = 0;
        vector<string> nms(nums.size());
        vector<pair<string, int>> tmp;
        vector<int> rv(qrs.size());
        while (k < n) 
        {
            for (auto i = 0; i < nums.size(); ++i)
            {
                nms[i] = nums[i].substr(n - k - 1);
                tmp.push_back({nms[i], i});
            }

            sort(begin(tmp), end(tmp));
            while (q < qrs.size() && qrs[q][0] == k + 1)
            {
                auto [d, p, i] = qrs[q];
                rv[i] = tmp[p - 1].second;
                ++q;
            }
            tmp.clear();
            ++k, mul *= 10;
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    vector<int> r;

    r = sol.smallestTrimmedNumbers(vector<string>() = {"102", "473", "251", "814"}, vector<vector<int>>() = {{1, 1}, {2, 3}, {4, 2}, {1, 2}});
    for (auto &c : r)
        cout << c << endl;
}
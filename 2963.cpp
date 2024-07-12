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
    int numberOfGoodPartitions(vector<int> &nums)
    {
        int n = nums.size();
        map<int, set<int>> m;
        for (auto i = 0; i < n; ++i)
            m[nums[i]].insert(i);

        vector<array<int, 2>> intervals;
        for (auto &mm : m)
            if (mm.second.size() == 1)
                intervals.push_back({*mm.second.begin(), *mm.second.begin()});
            else
                intervals.push_back({*mm.second.begin(), *mm.second.rbegin()});

        sort(begin(intervals), end(intervals));

        int cnt = 0, right = intervals[0][1];
        for (auto i = 1; i < intervals.size(); ++i)
        {
            if (right < intervals[i][0])
                ++cnt;
            right = max(right, intervals[i][1]);
        }

        int rv = 1;
        while (cnt--)
            rv = (rv * 2) % 1000000007;

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.numberOfGoodPartitions(vector<int>() = {1, 2, 1, 3});
    cout << r << endl;

    r = sol.numberOfGoodPartitions(vector<int>() = {1, 1, 1, 1});
    cout << r << endl;

    r = sol.numberOfGoodPartitions(vector<int>() = {1, 2, 3, 4});
    cout << r << endl;
}
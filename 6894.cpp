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
    void insert(int k)
    {
        if (intervals.empty())
            intervals.insert({k, k});
        else 
        {
            auto c = intervals.upper_bound({k, k});
            if (c != intervals.begin())
            {
                auto p = prev(c);
                if ((*p)[0] <= k && k <= (*p)[1])
                    return;
            }
            if ((*c)[0] <= k && k <= (*c)[1])
                return;

            c = intervals.insert({k, k}).first;
            if (c != intervals.begin())
            {
                auto p = prev(c);
                if ((*p)[1] + 1 == (*c)[0])
                {
                    auto [i, j] = *p;
                    intervals.erase(p), intervals.erase(c);
                    c = intervals.insert({i, j + 1}).first;
                }
            }
            if (next(c) != intervals.end())
            {
                auto n = next(c);
                if ((*c)[1] + 1 == (*n)[0])
                {
                    intervals.insert({(*c)[0], (*n)[1]}).first;
                    intervals.erase(c), intervals.erase(n);
                }
            }
        }
    }

    set<array<int, 2>> intervals;

public:
    int sumImbalanceNumbers(vector<int> &nums)
    {
        int rv = 0;
        int n = nums.size();
        for (auto i = 0; i < n; i++)
        {
            intervals.clear();
            for (auto j = i; j < n; j++)
            {
                insert(nums[j]);
                rv += intervals.size() - 1;
            }
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.sumImbalanceNumbers(vector<int>() = {1, 2, 1});
    cout << r << endl;

    r = sol.sumImbalanceNumbers(vector<int>() = {1, 2, 2});
    cout << r << endl;

    r = sol.sumImbalanceNumbers(vector<int>() = {1, 3, 3, 3, 5});
    cout << r << endl;

    r = sol.sumImbalanceNumbers(vector<int>() = {2, 3, 1, 4});
    cout << r << endl;
}
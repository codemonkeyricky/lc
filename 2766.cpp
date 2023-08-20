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
    vector<int> relocateMarbles(vector<int> &nums, vector<int> &from, vector<int> &to)
    {
        // int mmax = *max_element(begin(nums), end(nums));
        // mmax = max(mmax, *max_element(begin(from), end(from)));
        // mmax = max(mmax, *max_element(begin(to), end(to)));
        map<int, int> pos;
        for (auto &n : nums)
            ++pos[n];

        for (auto i = 0; i < from.size(); ++i)
        {
            pos[to[i]] += pos[from[i]];
            if (from[i] != to[i])
                pos[from[i]] = 0;
        }
        
        vector<int> rv;
        for (auto &p : pos)
            if (p.second)
                rv.push_back(p.first);
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.relocateMarbles(vector<int>() = {3, 4}, vector<int>() = {4,3,1,2,2,3,2,4,1}, vector<int>() = {3,1,2,2,3,2,4,1,1});

    sol.relocateMarbles(vector<int>() = {1, 6, 7, 8}, vector<int>() = {1, 7, 2}, vector<int>() = {2, 9, 5});
}
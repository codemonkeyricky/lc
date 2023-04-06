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
    void dfs(int low, int high, long curr, vector<int> &rv)
    {
        if (low <= curr && curr <= high)
            rv.push_back(curr);

        if (curr > high)
            return;

        if (!curr)
            for (auto i = 1; i < 10; ++i)
                dfs(low, high, i, rv);
        else 
        {
            auto last = curr % 10;
            if (last > 0)
                dfs(low, high, curr * 10 + last - 1, rv);
            if (last < 9)
                dfs(low, high, curr * 10 + last + 1, rv);
        }
    }

public:
    vector<int> countSteppingNumbers(int low, int high)
    {
        vector<int> rv;
        dfs(low, high, 0, rv);
        set<int> s(begin(rv), end(rv));
        return {begin(s), end(s)};
    }
};

int main()
{
    Solution sol;
    int r;

    sol.countSteppingNumbers(0, 1000000000);
    sol.countSteppingNumbers(10, 15);
    sol.countSteppingNumbers(0, 21);
}
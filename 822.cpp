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
    int flipgame(vector<int> &fronts, vector<int> &backs)
    {
        int n = fronts.size();
        unordered_set<int> rejects; 
        int rv = 1e9;
        for (auto i = 0; i < n; ++i)
            if (fronts[i] == backs[i])
                rejects.insert(fronts[i]);

        for (auto i = 0; i < n; ++i)
        {
            if (!rejects.count(fronts[i]))
                rv = min(rv, fronts[i]);
            if (!rejects.count(backs[i]))
                rv = min(rv, backs[i]);
        }

        return rv == 1e9 ? 0 : rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.flipgame(vector<int>() = {1, 1}, vector<int>() = {2, 2});
    cout << r << endl;

    r = sol.flipgame(vector<int>() = {1, 1}, vector<int>() = {1, 2});
    cout << r << endl;
}
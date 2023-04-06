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
    vector<int> missingRolls(vector<int> &rolls, int mean, int n)
    {
        int subset = accumulate(begin(rolls), end(rolls), 0);
        auto sum = mean * (rolls.size() + n);
        auto left = sum - subset;
        vector<int> rv(n), empty;
        for (auto i = 0; left && n && rv[0] <= 6; i = (i + 1) % rv.size(), --left)
            ++rv[i];
        return rv[0] <= 6 ? rv : empty;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.missingRolls(vector<int>() = {1,2,3,4}, 6, 4);
}
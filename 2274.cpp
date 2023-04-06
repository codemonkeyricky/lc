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
    int maxConsecutive(int bottom, int top, vector<int> &special)
    {
        int n = special.size();
        sort(begin(special), end(special));
        int rv = 0;
        for (auto i = 0; i <= n; ++i)
        {
            if (i == 0)
                rv = max(rv, special[i] - bottom);
            else if (i == n)
                rv = max(rv, top - special[n - 1]);
            else
                rv = max(rv, special[i] - special[i - 1] - 1);
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maxConsecutive(6, 8, vector<int>() = {7, 6, 8});
    cout << r << endl;
}
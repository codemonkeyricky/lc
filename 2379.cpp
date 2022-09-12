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
    int minimumRecolors(string blocks, int k)
    {
        int rv = k;
        for (auto i = 0, j = 0, w = 0, b = 0; j <= blocks.size(); ++j)
        {
            if (j >= k)
                rv = min(rv, w);

            if (j < blocks.size())
            {
                w += blocks[j] == 'W';
                if (j >= k)
                    w -= blocks[i] == 'W', ++i;
            }
        }

        return rv; 
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minimumRecolors("BWWWBB", 6);
    cout << r << endl;

    r = sol.minimumRecolors("WBWBBBW", 2);
    cout << r << endl;
}
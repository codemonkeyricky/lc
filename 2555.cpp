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
    int maximizeWin(vector<int> &p, int k)
    {
        int res = 0, w1 = 0, w2 = 0, max_w2 = 0;
        for (int l1 = 0, r1 = 0, l2 = 0, r2 = 0; r1 < p.size(); ++r1)
        {
            ++w1;
            for (; p[r1] - p[l1] > k; ++l1)
                --w1;
            for (; r2 < l1; ++r2)
            {
                ++w2;
                for (; p[r2] - p[l2] > k; ++l2)
                    --w2;
                max_w2 = max(max_w2, w2);
            }
            res = max(res, w1 + max_w2);
        }
        return res;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maximizeWin(vector<int>() = {1, 1, 1, 1, 4, 6, 8}, 2);
    cout << r << endl;

    r = sol.maximizeWin(vector<int>() = {1, 1, 2, 2, 3, 3, 5}, 2);
    cout << r << endl;
}
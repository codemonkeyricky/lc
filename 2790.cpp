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
    int maxIncreasingGroups(vector<int> &usage)
    {
        sort(begin(usage), end(usage));
        int n = usage.size();
        auto l = 1, r = n;
        while (l < r)
        {
            int m = (l + r + 1) / 2, valid = true, left = 0;
            for (int k = m, v = 1; k >= 1; ++v)
            {
                int count = end(usage) - lower_bound(begin(usage), end(usage), v);
                if (count < k)
                {
                    valid = false;
                    break;
                }
                // count = max(n, count + left);
                while (k >= 1 && count - k >= 0)
                    count -= k--;
                left = count;
            }

            if (valid)
                l = m;
            else
                r = m - 1;
        }
        return l;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maxIncreasingGroups(vector<int>() = {2, 7, 6, 2, 2});
    cout << r << endl;

    r = sol.maxIncreasingGroups(vector<int>() = {2, 2, 2});
    cout << r << endl;

    r = sol.maxIncreasingGroups(vector<int>() = {1, 1});
    cout << r << endl;

    r = sol.maxIncreasingGroups(vector<int>() = {2, 1, 2});
    cout << r << endl;

    r = sol.maxIncreasingGroups(vector<int>() = {1,2,5});
    cout << r << endl;
}
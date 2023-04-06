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
    int minimumMountainRemovals(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> forward(n);
        for (auto i = 0; i < n; ++i)
            for (auto j = 0; j < i; ++j)
                if (nums[j] < nums[i])
                    forward[i] = max(forward[i], 1 + forward[j]);

        vector<int> backward(n);
        for (int i = n - 1; i >= 0; --i)
            for (int j = n - 1; j > i; --j)
                if (nums[i] > nums[j])
                    backward[i] = max(backward[i], 1 + backward[j]);
            
        int rv = 0;
        for (auto i = 0; i < n; ++i)
            if (forward[i] && backward[i])
                rv = max(rv, forward[i] + backward[i] + 1);
        return n - rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minimumMountainRemovals(vector<int>() = {9, 8, 1, 7, 6, 5, 4, 3, 2, 1});
    cout << r << endl;

    r = sol.minimumMountainRemovals(vector<int>() = {2, 1, 1, 5, 6, 2, 3, 1});
    cout << r << endl;
}
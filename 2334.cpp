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
    int validSubarraySize(vector<int> &nums, int threshold)
    {
        vector<double> dp;
        for (auto i = 0; i < nums.size(); ++i)
            dp[i] = threshold / nums[i];

        int i, j, n = nums.size(); 
        int largest = 0; 
        for (i = 0, j = 0; j < n; ++j)
        {
            if (dp[j] > n - j)
                i = j;
            else 
            {
                if (j - i + 1 > = largest)
            }
        }
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}
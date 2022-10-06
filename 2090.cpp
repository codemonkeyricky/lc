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
    vector<int> getAverages(vector<int> &nums, int k)
    {
        int n = nums.size();
        vector<int> rv(n, -1);
        for (long i = 0, j = 0, sum = 0; j < n; ++j)
        {
            sum += nums[j];
            if (j >= k * 2)
            {
                rv[j - k] = sum / (k * 2 + 1);
                sum -= nums[i++];
            }
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.getAverages(vector<int>() = {7, 4, 3, 9, 1, 8, 5, 2, 6}, 3);
    cout << r << endl;
}
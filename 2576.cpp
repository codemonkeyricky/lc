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
    int maxNumOfMarkedIndices(vector<int> &nums)
    {
        sort(begin(nums), end(nums));
        int n = nums.size();
        int l = 0, r = nums.size() / 2;
        while (l < r)
        {
            int k = (l + r + 1) / 2;

            bool possible = true;
            for(auto i = 0; i < k && possible; ++i)
                if (nums[i] * 2 > nums[n - k + i])
                    possible = false;

            if (possible)
                l = k;
            else
                r = k - 1;
        }
        return l * 2;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maxNumOfMarkedIndices(vector<int>() = {42, 83, 48, 10, 24, 55, 9, 100, 10, 17, 17, 99, 51, 32, 16, 98, 99, 31, 28, 68, 71, 14, 64, 29, 15, 40});
    cout << r << endl;

    r = sol.maxNumOfMarkedIndices(vector<int>() = {9, 2, 5, 4});
    cout << r << endl;
}
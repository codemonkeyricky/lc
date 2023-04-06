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
    vector<int> applyOperations(vector<int> &nums)
    {
        for (auto i = 0; i + 1 < nums.size(); ++i)
            if (nums[i] == nums[i + 1])
                nums[i] *= 2, nums[i + 1] = 0;
        
        int i, j; 
        for (i = 0, j = 0; j < nums.size(); ++j)
            if (nums[j])
                nums[i++] = nums[j];
        while (i < nums.size())
            nums[i++] = 0;

        return nums;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}
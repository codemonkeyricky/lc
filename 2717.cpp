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
    int semiOrderedPermutation(vector<int> &nums)
    {
        int n = nums.size();
        int first = -1, last = -1;
        for (auto i = 0; i < nums.size(); ++i)
            if (nums[i] == 1)
                first = i;
            else if (nums[i] == nums.size())
                last = i;

        if (first == 0 && last == n - 1)
            return 0;
        else if (first == 0)
            return n - last - 1;
        else if (last == n - 1)
            return first;
        else
        {
            if (first > last)
                return first + n - last - 2;
            else
                return first + n - last - 1;
        }
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.semiOrderedPermutation(vector<int>() = {2, 4, 1, 3});
    cout << r << endl;

    r = sol.semiOrderedPermutation(vector<int>() = {1, 3, 4, 2, 5});
    cout << r << endl;
}
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
    int minMaxGame(vector<int> &nums)
    {
        while (nums.size() > 1)
        {
            vector<int> newNums;
            for (auto i = 0; i < nums.size(); i += 2)
                if ((i / 2) % 2 == 0)
                    newNums.push_back(min(nums[i], nums[i + 1]));
                else 
                    newNums.push_back(max(nums[i], nums[i + 1]));
            swap(newNums, nums);
        }

        return nums[0];
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minMaxGame(vector<int>() = {810, 831, 908, 631, 554, 917, 392, 544});
    cout << r << endl;
}
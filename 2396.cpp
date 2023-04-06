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
    bool isPalindrome(vector<int> &nums)
    {
        int i = 0, j = nums.size() - 1;
        while (i < j)
            if (nums[i++] != nums[j--])
                return false;
        return true;
    }

public:
    bool isStrictlyPalindromic(int n)
    {
        for (auto i = 2; i < n - 1; ++i)
        {
            vector<int> nums;
            auto nn = n;
            while (nn)
                nums.push_back(nn % i), nn /= i;

            if (!isPalindrome(nums))
                return false;
        }

        return true;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.isStrictlyPalindromic(9);
    cout << r << endl;
}
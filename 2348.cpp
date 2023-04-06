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
    long long zeroFilledSubarray(vector<int> &nums)
    {
        long long rv = 0;
        for(long long i = -1, j = 0; j < nums.size(); ++j)
            if (nums[j] == 0)
            {
                if (i == -1)
                    i = j;
                rv += j - i + 1;
            }
            else
                i = -1;
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.zeroFilledSubarray(vector<int>() = {1, 3, 0, 0, 2, 0, 0, 4});
    cout << r << endl;
}
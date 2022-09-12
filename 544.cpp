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
    string findContestMatch(int n)
    {
        vector<string> nums;
        for (auto i = 1; i <= n; ++i)
            nums.push_back(to_string(i));

        while (nums.size() > 1)
        {
            vector<string> rv;
            int i = 0, j = nums.size() - 1;
            while (i < j)
                rv.push_back("(" + nums[i++] + "," + nums[j--] + ")");
            swap(rv, nums);
        }
        return nums[0];
    }
};

int main()
{
    Solution sol;
    string r;

    r = sol.findContestMatch(4096);
    cout << r << endl;
}
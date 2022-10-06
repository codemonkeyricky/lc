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
    bool check(vector<int> &nums)
    {
        int n = nums.size();
        auto mm = min_element(begin(nums), end(nums)) - begin(nums);

        int i;
        for (i = 0; i < n - 1; ++i)
            if (nums[(mm - i - 1 + n) % n] != nums[(mm - i + n) % n])
                break;
        mm = (mm - i + n) % n;

        for (i = 0; i < n - 1; ++i)
            if (nums[(i + mm) % n] > nums[(i + 1 + mm) % n])
                return false;
        return true;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.check(vector<int>() = {6, 10, 6});
    cout << r << endl;
}
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
    int minimumIndex(vector<int> &nums)
    {
        unordered_map<int, int> cnt;
        int max_cnt = 0, dominant = -1;
        for (auto &n : nums)
            if (++cnt[n] > max_cnt)
                max_cnt = cnt[n], dominant = n;

        int dcnt = 0, n = nums.size();
        for (auto i = 0; i < nums.size(); ++i)
            if (nums[i] == dominant)
                if (++dcnt * 2 > (i + 1) && (max_cnt - dcnt) * 2 > (n - i - 1))
                    return i;
        return -1;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minimumIndex(vector<int>() = {3, 3, 3, 3, 7, 2, 2});
    cout << r << endl;

    r = sol.minimumIndex(vector<int>() = {1, 2, 2, 2});
    cout << r << endl;
}
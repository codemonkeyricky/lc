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
    int minimumSeconds(vector<int> &nums)
    {
        auto copy = nums;
        nums.insert(end(nums), begin(copy), end(copy));
        map<int, int> steps, last;
        for (auto i = 0; i < nums.size(); ++i)
        {
            if (last.count(nums[i]))
                steps[nums[i]] = max(steps[nums[i]], i - last[nums[i]]);
            last[nums[i]] = i;
        }

        int rv = 1e9;
        for (auto &m : steps)
            rv = min(rv, m.second);
        return rv / 2;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minimumSeconds(vector<int>() = {2, 1, 3, 3, 2});
    cout << r << endl;

    r = sol.minimumSeconds(vector<int>() = {1, 2, 1, 2});
    cout << r << endl;
}
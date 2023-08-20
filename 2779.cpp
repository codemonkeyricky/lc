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
    int maximumBeauty(vector<int> &nums, int k)
    {
        sort(begin(nums), end(nums));
        multiset<int> set;
        int rv = 0;
        for (auto i = 0, j = 0; j < nums.size(); ++j)
        {
            set.insert(nums[j]);
            while (*prev(set.end()) - *set.begin() > 2 * k)
                set.erase(set.find(nums[i++]));
            rv = max(rv, j - i + 1);
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maximumBeauty(vector<int>() = {4, 6, 1, 2}, 2);
    cout << r << endl;
}
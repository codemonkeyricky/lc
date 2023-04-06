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
    int findSmallestInteger(vector<int> &nums, int value)
    {
        unordered_map<int, int> map;
        for (auto &n : nums)
        {
            n %= value;
            if (n < 0)
                n += value;
            ++map[n];
        }

        set<int> set;
        for (auto &m : map)
        {
            auto k = m.first;
            auto c = m.second;
            for (auto i = 0; i < c; ++i)
                set.insert(k + i * value);
        }

        nums.assign(begin(set), end(set));

        if (nums[0] > 0)
            return 0;

        for (auto i = 0; i + 1 < nums.size(); ++i)
            if (nums[i] + 1 >= 0 && nums[i] + 1 != nums[i + 1])
                return nums[i] + 1;

        return nums.back() + 1; 
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.findSmallestInteger(vector<int>() = {0, -3}, 4);
    cout << r << endl;

    r = sol.findSmallestInteger(vector<int>() = {3, 0, 3, 2, 4, 2, 1, 1, 0, 4}, 5);
    cout << r << endl;

    r = sol.findSmallestInteger(vector<int>() = {1, -10, 7, 13, 6, 8}, 5);
    cout << r << endl;
}
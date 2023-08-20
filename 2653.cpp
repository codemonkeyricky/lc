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
    vector<int> getSubarrayBeauty(vector<int> &nums, int k, int x)
    {
        int n = nums.size();
        map<int, int> cnt;
        vector<int> rv;
        for (auto i = 0; i <= n; ++i)
        {
            if (i >= k)
            {
                int xx = x;
                int r = 0;
                for (auto &c : cnt)
                    if (c.first < 0)
                        if (xx > c.second)
                            xx -= c.second;
                        else
                        {
                            r = c.first;
                            break;
                        }
                    else
                        break;
                
                rv.push_back(r);

            }

            if (i < n)
                ++cnt[nums[i]];

            if (i >= k)
                --cnt[nums[i - k]];
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    vector<int> r;

    r = sol.getSubarrayBeauty(vector<int>() = {1, -1, -3, -2, 3}, 3, 2);
    for (auto &c : r)
        cout << c << ", ";
    cout << endl;
}
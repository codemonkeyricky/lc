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
    int minLengthAfterRemovals(vector<int> &nums)
    {
        priority_queue<int> q;
        int n = nums.size();
        for (auto i = 1, c = 1; i <= n; ++i)
            if (i == n || nums[i - 1] != nums[i])
                q.push(c), c = 1;
            else
                ++c;

        while (q.size() > 1)
        {
            int top1 = q.top(); 
            q.pop();
            int top2 = q.top();
            q.pop();
            q.push(top1 - top2);
        }

        return q.size() ? q.top() : 0;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minLengthAfterRemovals(vector<int>() = {2, 3, 3, 3});
    cout << r << endl;

    r = sol.minLengthAfterRemovals(vector<int>() = {1, 3, 4, 9});
    cout << r << endl;

    r = sol.minLengthAfterRemovals(vector<int>() = {2, 3, 4, 4, 4});
    cout << r << endl;
}
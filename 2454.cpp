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
    vector<int> secondGreaterElement(vector<int> &nums)
    {
        int n = nums.size();
        priority_queue<array<int, 2>> heap;
        vector<int> rv(n, -1);
        vector<int> stack;
        for (auto i = 0; i < n; ++i)
        {
            while (heap.size() && nums[i] > -heap.top()[0])
            {
                auto [v, k] = heap.top();
                rv[k] = nums[i];
                heap.pop();
            }

            while (stack.size() && nums[stack.back()] < nums[i])
                heap.push({-nums[stack.back()], stack.back()}), stack.pop_back();
            stack.push_back(i);
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    vector<int> r;

    r = sol.secondGreaterElement(vector<int>() = {11, 13, 15, 12, 0, 15, 12, 11, 9});
    for (auto &c : r)
        cout << c << ", ";
    cout << endl;

    r = sol.secondGreaterElement(vector<int>() = {2, 4, 0, 9, 6});
    for (auto &c : r)
        cout << c << ", ";
    cout << endl;
}
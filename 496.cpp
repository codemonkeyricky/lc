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
    vector<int> nextGreaterElement(vector<int> &findNums, vector<int> &nums)
    {
        vector<int> s;
        unordered_map<int, int> m;
        for (int n : nums)
        {
            while (s.size() && s.back() < n)
            {
                m[s.back()] = n;
                s.pop_back();
            }
            s.push_back(n);
        }
        vector<int> ans;
        for (int n : findNums)
            ans.push_back(m.count(n) ? m[n] : -1);
        return ans;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.nextGreaterElement(vector<int>() = {4, 1, 2}, vector<int>() = {1, 3, 4, 2});
}
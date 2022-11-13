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
    void dfs(int k, int n, string &curr, vector<string> &rv)
    {
        if (k >= n)
        {
            rv.push_back(curr);
            return;
        }

        vector<int> nums = {0, 1, 6, 9, 8};
        for (auto i = k ? 0 : 1; i < nums.size(); ++i)
        {
            curr.push_back(nums[i] + '0');
            dfs(k + 1, n, curr, rv);
            curr.pop_back();
        }
    }


public:
    vector<string> findStrobogrammatic(int n)
    {
        int nn = n / 2;
        int odd = n % 2;
        vector<string> set, rv;
        dfs(0, nn, string() = {}, set);
        vector<int> nums = {0, 1, 8};
        for (auto &s : set)
        {
            string rs(rbegin(s), rend(s));
            for(auto & c : s)
                if(c == '6')
                    c = '9';
                else if (c == '9')
                    c = '6';
            if (odd)
                for (auto &n : nums)
                    rv.push_back(s + to_string(n) + rs);
            else
                rv.push_back(s + rs);
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.findStrobogrammatic(2);
}
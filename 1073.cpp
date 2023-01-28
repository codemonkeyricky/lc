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

/*
 *  negative base addition
 */ 

class Solution
{
public:
    vector<int> addNegabinary(vector<int> &a1, vector<int> &a2)
    {
        vector<int> res;
        int bit = 0, carry = 0, sz = max(a1.size(), a2.size());
        for (auto bit = 0; bit < sz || carry != 0; ++bit)
        {
            auto b1 = bit < a1.size() ? a1[a1.size() - bit - 1] : 0;
            auto b2 = bit < a2.size() ? a2[a2.size() - bit - 1] : 0;
            auto sum = b1 + b2 + carry;
            res.push_back(abs(sum) % 2);
            carry = sum < 0 ? 1 : sum > 1 ? -1
                                          : 0;
        }
        while (res.size() > 1 && res.back() == 0)
            res.pop_back();
        reverse(begin(res), end(res));
        return res;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.addNegabinary(vector<int>() = {1}, vector<int>() = {1});

    sol.addNegabinary(vector<int>() = {1, 1, 1, 1, 1}, vector<int>() = {1, 0, 1});
}
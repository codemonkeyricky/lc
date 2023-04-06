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
    vector<int> plusOne(vector<int> &digits)
    {
        reverse(begin(digits), end(digits));

        int carry = 1;
        for (auto i = 0; i < digits.size() && carry; ++i)
            if (digits[i] == 9)
                digits[i] = 0;
            else
                ++digits[i], carry = 0;

        if (carry)
            digits.push_back(carry);

        reverse(begin(digits), end(digits));

        return digits;
    }
};

int main()
{
    Solution sol;
    int r;

sol.plusOne(vector<int>'9')
    cout << r << endl;
}
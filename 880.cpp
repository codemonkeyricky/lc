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
    string decodeAtIndex(string &s, int k, long long len = 0)
    {
        for (auto i = 0; i < s.size(); ++i)
        {
            if (isalpha(s[i]))
            {
                if (++len == k)
                    return string(1, s[i]);
            }
            else
            {
                if (len * (s[i] - '0') >= k)
                    return decodeAtIndex(s, k % len == 0 ? len : k % len);
                len *= s[i] - '0';
            }
        }
    }
};

int main()
{
    Solution sol;
    string r;

    r = sol.decodeAtIndex(string() = "a1b2c3d4e5g6", 301);
    cout << r << endl;

    // r = sol.decodeAtIndex("abc", 1);
    // cout << r << endl;

    // r = sol.decodeAtIndex("a2345678999999999999999", 1);
    // cout << r << endl;

    // r = sol.decodeAtIndex("leet2code3", 34);
    // cout << r << endl;
}
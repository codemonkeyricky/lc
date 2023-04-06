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
    int newInteger(int n)
    {
        int rv = 0, base = 1; 
        while (n)
        {
            rv = rv + (n % 9) * base;
            n /= 9;
            base *= 10;
        }
        return rv;
    }
};

int main()
{

    // string s = to_string(100);
    // r = sol.count9s(s);
    // cout << r << endl;

    {
        Solution sol;
        int r;

        r = sol.newInteger(788888888);
        cout << r << endl;
    }

    // r = sol.newInteger(999999);
    // cout << r << endl;

    // r = sol.newInteger(100);
    // cout << r << endl;

    // r = sol.newInteger(9);
    // cout << r << endl;

    // r = sol.newInteger(9);
    // cout << r << endl;
}
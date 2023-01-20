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
    string convertToBase7(int n)
    {
        if (n == 0)
            return "0";

        string rv;
        int pos = n >= 0;
        n *= pos ? 1 : -1;
        while (n)
        {
            rv += '0' + n % 7;
            n /= 7;
        }

        if (!pos)
            rv += '-';

        reverse(begin(rv), end(rv));
        return rv; 
    }
};

int main()
{
    Solution sol;
    int r;

    sol.convertToBase7(-7);
    cout << r << endl;
}
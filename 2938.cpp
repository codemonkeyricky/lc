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
    long long minimumSteps(string s)
    {
        int n = s.size();
        long long l = 0, r = n - 1, rv = 0;
        while (l < r)
        {
            while (l < n && s[l] == '0')
                ++l;

            while (r >= 0 && s[r] == '1')
                --r;

            if (l < r)
                rv += r - l;
            l++, r--;
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minimumSteps("100");
    cout << r << endl;

    r = sol.minimumSteps("101");
    cout << r << endl;
}
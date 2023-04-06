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
    vector<int> diStringMatch(string s)
    {
        int mmin = -1, mmax = 1;
        vector<int> rv = {0};
        for (auto &c : s)
            if (c == 'I')
                rv.push_back(mmax++);
            else
                rv.push_back(mmin--);

        for (auto &c : rv)
            c -= mmin + 1;
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.diStringMatch("IDID");
    cout << r << endl;
}
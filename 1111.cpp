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
    vector<int> maxDepthAfterSplit(string seq)
    {
        int d = 0, md = 0, n = seq.size();
        for (auto i = 0; i < n; ++i)
        {
            if (seq[i] == '(')
                ++d;
            else
                --d;
            md = max(md, d);
        }

        auto limit = md / 2, low = 1; 
        vector<int> rv(n);
        for (auto i = 0; i < n; ++i)
        {
            if (seq[i] == '(')
                ++d;
            else 
                --d;

            if (d < limit)
                rv[i] = 0;
            else if (d > limit)
                rv[i] = 1;
            else 
                rv[i] = seq[i] == ')';

        }
        return rv;
    }
};

int main()
{
    Solution sol;
    vector<int> r;

    r = sol.maxDepthAfterSplit("(()())");
    for (auto &c : r)
        cout << c << ", ";
    cout << endl;
}
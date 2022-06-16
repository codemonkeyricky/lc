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
    int widestPairOfIndices(vector<int> &n1, vector<int> &n2, int res = 0)
    {
        partial_sum(begin(n1), end(n1), begin(n1));
        partial_sum(begin(n2), end(n2), begin(n2));
        unordered_map<int, int> m{{0, -1}};
        for (int i = 0; i < n1.size(); ++i)
        {
            if (m.count(n1[i] - n2[i]))
                res = max(res, i - m[n1[i] - n2[i]]);
            else
                m[n1[i] - n2[i]] = i;
        }
        return res;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}
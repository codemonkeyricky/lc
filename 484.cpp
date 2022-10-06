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
    vector<int> findPermutation(string s)
    {
        vector<int> rv;
        for (int i = 0, j = 0; j <= s.size(); ++j)
        {
            rv.push_back(1 + j);
            if (j == s.size() || s[j] == 'I')
            {
                reverse(begin(rv) + i, end(rv));
                i = j + 1;
            }
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.findPermutation("IIIIIDI");
    sol.findPermutation("DI");
}
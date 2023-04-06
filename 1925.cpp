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
    int countTriples(int n)
    {
        int rv = 0;
        for (auto a = 1; a < n; ++a)
            for (int b = a + 1, c = (int)sqrt(a * a + b * b); b < n; ++b, c = sqrt(a * a + b * b))
                if (c <= n && c * c == a * a + b * b)
                    rv += 2; 
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.countTriples(10);
    cout << r << endl;
}
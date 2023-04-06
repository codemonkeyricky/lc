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
    vector<string> simplifiedFractions(int n)
    {
        set<array<int, 2>> uniq;
        for (auto i = 2; i <= n; ++i)
            for (auto j = 1; j < i; ++j)
            {
                auto g = __gcd(i, j);
                uniq.insert({j / g, i / g});
        }

        vector<string> rv;
        for (auto &u : uniq)
            rv.push_back(to_string(u[0]) + "/" + to_string(u[1]));
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}
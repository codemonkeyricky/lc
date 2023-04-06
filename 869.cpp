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

unordered_set<string> powers;
class Solution
{
public:
    bool reorderedPowerOf2(int n)
    {
        if (powers.empty())
        {
            int p = 1;
            while (p < 1e9)
            {
                auto s = to_string(p);
                sort(begin(s), end(s));
                powers.insert(s);
                p <<= 1;
            }
        }

        auto s = to_string(n);
        sort(begin(s), end(s));
        return powers.count(s);
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}
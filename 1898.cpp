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
#include <climits>

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
    int maximumRemovals(string s, string p, vector<int> &rem)
    {
        int l = 0, r = rem.size();
        vector<int> map(s.size(), INT_MAX);
        for (int i = 0; i < rem.size(); ++i)
            map[rem[i]] = i;
        while (l < r)
        {
            int m = (l + r + 1) / 2;
            int j = 0;
            for (int i = 0; i < s.size() && j < p.size(); ++i)
                if (map[i] >= m && s[i] == p[j])
                    ++j;
            if (j == p.size())
                l = m;
            else
                r = m - 1;
        }
        return l;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maximumRemovals("abcacb", "ab", vector<int>() = {3, 1, 0});
    cout << r << endl;
}
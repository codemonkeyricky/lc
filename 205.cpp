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
    bool isIsomorphic(string s, string t)
    {
        if (s.size() != t.size())
            return false;

        unordered_map<int, int> map, rmap;
        for (auto i = 0; i < s.size(); ++i)
            if (!map.count(s[i]) && !rmap.count(t[i]))
                map[s[i]] = t[i], rmap[t[i]] = s[i];
            else if (map[s[i]] != t[i] || rmap[t[i]] != s[i])
                return false;
        return true;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.isIsomorphic("badc", "baba");
    cout << r << endl;
}
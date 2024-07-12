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
    long long beautifulSubstrings(string s, int k)
    {
        int n = s.length(), v = 0, l;
        for (l = 1; l * l % (k * 4); ++l)
            ;
        set<char> vowels = {'a', 'e', 'i', 'o', 'u'};
        vector<unordered_map<int, int>> seen(l);
        seen[l - 1][0] = 1;
        long long rv = 0;
        for (int i = 0; i < n; i++)
        {
            v += vowels.find(s[i]) != vowels.end() ? 1 : -1;
            rv += seen[i % l][v]++;
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.beautifulSubstrings("baeyh", 2);
    cout << r << endl;
}
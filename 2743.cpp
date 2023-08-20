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
    int numberOfSpecialSubstrings(string s)
    {
        array<int, 26> set = {};
        int rv = 0, curr = 0;
        for (auto i = 0, j = 0; j < s.size(); ++j)
        {
            if (set[s[j] - 'a']++)
                while (set[s[j] - 'a'] > 1)
                    --set[s[i++] - 'a'];
            rv += j - i + 1;
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.numberOfSpecialSubstrings("bddqc");
    cout << r << endl;

    r = sol.numberOfSpecialSubstrings("abab");
    cout << r << endl;

    r = sol.numberOfSpecialSubstrings("ooo");
    cout << r << endl;

    r = sol.numberOfSpecialSubstrings("abcd");
    cout << r << endl;
}
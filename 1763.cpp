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
    string longestNiceSubstring(string s)
    {
        int n = s.size();
        string rv, curr;
        array<int, 26> chars = {};
        for (int i = 0; i < n; ++i, chars = {}, curr.clear())
            for (auto j = i; j < n; ++j)
            {
                if (islower(s[j]))
                    chars[s[j] - 'a'] |= 1;
                else 
                    chars[s[j] - 'A'] |= 2;
                curr += s[j];

                bool isMatch = true;
                for (auto k = 0; k < 26 && isMatch; ++k)
                    if (chars[k] && chars[k] != 0x3)
                        isMatch = false;

                if (isMatch)
                    if (curr.size() > rv.size())
                        rv = curr;
            }
        return rv;
    }
};

int main()
{
    Solution sol;
    string r;

    r = sol.longestNiceSubstring("YazaAay");
    cout << r << endl;
}
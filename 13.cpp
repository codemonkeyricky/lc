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
    int romanToInt(string s)
    {
        int n = s.size();
        int rv = 0;
        for (auto i = 0; i < n; ++i)
            if (s[i] == 'I')
            {
                if (i + 1 < n && s[i + 1] == 'V')
                    rv += 4, ++i;
                else if(i + 1 < n && s[i + 1] == 'X')
                    rv += 9, ++i;
                else
                    ++rv;
            }
            else if (s[i] == 'X')
            {
                if (i + 1 < n && s[i + 1] == 'L')
                    rv += 40, ++i;
                else if(i + 1 < n && s[i + 1] == 'C')
                    rv += 90, ++i;
                else
                    rv += 10;
            }
            else if (s[i] == 'C')
            {
                if (i + 1 < n && s[i + 1] == 'D')
                    rv += 400, ++i;
                else if (i + 1 < n && s[i + 1] == 'M')
                    rv += 900, ++i;
                else
                    rv += 100;
            }
            else if (s[i] == 'V')
                rv += 5;
            else if (s[i] == 'L')
                rv += 50;
            else if (s[i] == 'D')
                rv += 500;
            else if (s[i] == 'M')
                rv += 1000;
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.romanToInt("DCXXXI");
    cout << r << endl;
}
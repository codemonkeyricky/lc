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
    int minInsertions(string s)
    {
        string ss;
        int n = s.size(), rv = 0;
        for (auto i = 0; i < n; ++i)
        {
            if (i + 1 < n && s[i] == ')' && s[i + 1] == ')')
                ss += ')', ++i;
            else 
            {
                if (s[i] == ')')
                    ++rv;
                ss += s[i];
            }
        }

        swap(ss, s);
        ss.clear();

        for (auto &c : s)
            if (ss.size() && ss.back() == '(' && c == ')')
                ss.pop_back();
            else
                ss += c;

        for (auto &c : ss)
        {
            if (c == '(')
                ++rv;
            ++rv;
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minInsertions("))())(");
    cout << r << endl;

    r = sol.minInsertions("(()))(()))()())))");
    cout << r << endl;

    r = sol.minInsertions("(()))");
    cout << r << endl;
}
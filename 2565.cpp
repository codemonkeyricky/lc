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
    int minimumScore(string s, string t)
    {
        int n = t.size();
        vector<int> left(n, 1e9);
        for (auto i = 0, k = 0; i < n && k < s.size(); ++i)
        {
            while (k < s.size() && s[k] != t[i])
                ++k;
            if (k < s.size())
                left[i] = k++;
        }

        vector<int> right(n, -1e9);
        for (int i = n - 1, k = s.size() - 1; i >= 0 && k >= 0; --i)
        {
            while (k >= 0 && s[k] != t[i])
                --k;
            if (k >= 0)
                right[i] = k--;
        }

        if (left.back() != 1e9 || right[0] != -1e9)
            return 0;

        int l = 0, r = t.size();
        while (l < r)
        {
            int m = (l + r) / 2;
            int isSub = right[m] != -1e9;
            for (auto i = 0; i + m + 1 < n && !isSub; ++i)
                if (left[i] < right[i + m + 1])
                    isSub = true;

            if (!isSub)
                isSub = left[n - m - 1] != 1e9;

            if (isSub)
                r = m;
            else
                l = m + 1;
        }

        return l;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minimumScore("eeecaeecdeeadcdbcaa", "edecabe");
    cout << r << endl;

    r = sol.minimumScore("acdedcdbabecdbebda", "bbecddb");
    cout << r << endl;

    r = sol.minimumScore("cbedceeeccd", "ed");
    cout << r << endl;

    r = sol.minimumScore("abecdebe", "eaebceae");
    cout << r << endl;

    r = sol.minimumScore("abacaba", "bzaa");
    cout << r << endl;
}
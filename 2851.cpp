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
    int MOD = 1000000007;
    long superPow(int n, int p)
    {
        if (p == 0)
            return 1;

        if (p == 1)
            return n;

        long rr = superPow(n, p / 2);
        long rv = rr * rr % MOD;
        if (p % 2)
            rv = rv * n % MOD;
        return rv;
    }

public:
    int numberOfWays(string s, string t, long long k)
    {
        // prefix
        int n = t.size();
        vector<int> p(n);
        for (int i = 1; i < n; i++)
        {
            int j = p[i - 1];
            while (j > 0 && s[i] != s[j])
                j = p[j - 1];
            if (s[i] == s[j])
                j++;
            p[i] = j;
        }

        auto s2 = s + s;
        s2.pop_back();
        int i = 0, j = 0, cnt = 0;
        while (i < s2.size()) 
        {
            if (s2[i] == t[j])
                ++i, ++j;

            if (j == t.size())
                j = p[j - 1], ++cnt;
            else if (i < s2.size() && s2[i] != t[j])
            {
                if (j)
                    j = p[j - 1];
                else 
                    ++i;
            }
        }

        int x = cnt;
        int y = s.size() - cnt;

        if (k == 0)
            return 0;
        else if (k == 1)
            return cnt - 1;
        else if (k == 2)
        {
            if (s == t)
                return y * x;
            else
                return (y - 1) * x;
        }

        long a, b, c, d;
        if (s == t)
            a = (x - 1) * y;
        else
            a = x * (y - 1);
        long m = superPow(2, k - 3);
        b = x * m + (x - 1) + m * (x - 1) + m * y + m * (y - 1);
        c = y * (y - 1);
        d = x;

        long rv = 1;
        rv = (rv * a) % MOD;
        rv = (rv * b) % MOD;
        rv = (rv * c) % MOD;
        rv = (rv * d) % MOD;

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.numberOfWays("abcd", "cdab", 3);
    cout << r << endl;

    r = sol.numberOfWays("ababab", "ababab", 1);
    cout << r << endl;

    r = sol.numberOfWays("abcd", "cdab", 2);
    cout << r << endl;
}
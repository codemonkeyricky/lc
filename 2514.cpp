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
    void addFactors(int n, map<int, int> &factors)
    {
        int i; 
        for (i = 2; i * i <= n; ++i)
            while (n % i == 0)
                ++factors[i], n /= i;
        ++factors[n];
    }

    void removeFactors(int n, map<int, int> &factors)
    {
        int i; 
        for (i = 2; i * i <= n; ++i)
            while (n % i == 0)
                --factors[i], n /= i;
        --factors[n];
    }

public:
    int countAnagrams(string s)
    {
        array<int, 26> chars = {};
        long rv = 1, len = 0, MOD = 1e9 + 7;
        map<int, int> mul, div;
        for (auto i = 0; i <= s.size(); ++i)
            if (i == s.size() || s[i] == ' ')
                chars = {}, len = 0;
            else
            {
                addFactors(++len, mul); 
                removeFactors(++chars[s[i] - 'a'], mul);
                // rv = rv * ++len;
                // rv = rv / ;
                // rv = rv % MOD;
            }

        for (auto &m : mul)
            if (m.second > 0)
                while (m.second--)
                    rv = (rv * m.first) % MOD;
            else if (m.second < 0)
                while (m.second++)
                    rv = rv / m.first;

        return rv % MOD;
    }
};

int main()
{
    Solution sol;
    int r;

    // r = sol.countAnagrams("rsrybprxlendseni");
    // cout << r << endl;

    r = sol.countAnagrams("b okzojaporykbmq tybq zrztwlolvcyumcsq jjuowpp");
    cout << r << endl;

    r = sol.countAnagrams("aaaaaaaabbbbbbb ccddd");
    cout << r << endl;

    r = sol.countAnagrams("aa");
    cout << r << endl;

    r = sol.countAnagrams("too hot");
    cout << r << endl;
}
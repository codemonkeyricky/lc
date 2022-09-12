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
    int minCharacters(string a, string b)
    {
        array<int, 26> ac = {}, bc = {};
        for (auto &c : a)
            ++ac[c - 'a'];
        for (auto &c : b)
            ++bc[c - 'a'];

        /*
         *  a strictly larger than b
         */

        int asum = 0, bsum = accumulate(begin(bc), end(bc), 0);
        int r1 = 1e9;
        for (auto i = 0; i < 25; ++i)
        {
            asum += ac[i];

            // all letter in b changes to a, ab, abc, abcd....
            bsum -= bc[i];
            r1 = min(r1, asum + bsum);
        }

        asum = accumulate(begin(ac), end(ac), 0), bsum = 0; 
        int r2 = 1e9;
        for (auto i = 0; i < 25; ++i)
        {
            bsum += bc[i];
            asum -= ac[i];
            r2 = min(r2, asum + bsum);
        }

        int rv = 1e9, bn = b.size(), an = a.size(), max_count_a = 0, max_count_b = 0;
        for (int i = 0; i < 26; ++i)
            max_count_a = max(max_count_a, ac[i]);
        for (int i = 0; i < 26; ++i)
            max_count_b = max(max_count_b, bc[i]);

        int r3 = an - max_count_a + bn - max_count_b;

        return min({r1, r2, r3});
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minCharacters("a", "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz");
    cout << r << endl;

    r = sol.minCharacters("acac", "bd");
    cout << r << endl;

    r = sol.minCharacters("aba", "caa");
    cout << r << endl;
}
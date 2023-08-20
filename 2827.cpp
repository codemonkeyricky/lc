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
    int dfs(string &num, string curr, int mod, int k = 0, int ceil = true, int ph = 10, int remainder = 0)
    {
        int n = num.size();
        if(k >= n)
            return (ph == 0) && (remainder % mod == 0);

        int rv = 0;
        for (int i = ceil ? num[k] - '0' : 9; i >= 0; --i)
        {
            int add = i % 2 ? 1 : -1;
            int new_ph = 0;
            if (i && ph != 10)
                new_ph = ph + add;
            else if (i && ph == 10)
                new_ph = add;
            else if (!i && ph != 10)
                new_ph = ph + add;
            else if (!i && ph == 10)
                new_ph = 10;

            rv += dfs(num,
                      curr + string(1, i + '0'),
                      mod,
                      k + 1,
                      ceil && i == num[k] - '0',
                      new_ph,
                      (remainder * 10 + i) % mod);
        }
        return rv;
    }

public:
    int numberOfBeautifulIntegers(int low, int high, int kk)
    {
        string num = to_string(high);
        int a, b = 0;
        a = dfs(num, "", kk);
        if (low)
        {
            string num = to_string(low - 1);
            b = dfs(num, "", kk);
        }
        return a - b;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << sol.numberOfBeautifulIntegers(1, 1100, 11) << endl;
    cout << sol.numberOfBeautifulIntegers(1, 20, 20) << endl;
    // cout << sol.numberOfBeautifulIntegers(5, 5, 2) << endl;
    // cout << sol.numberOfBeautifulIntegers(1, 10, 1) << endl;
    // cout << sol.numberOfBeautifulIntegers(10, 20, 3) << endl;

    // for (int i = 20; i >= 0; --i)
    //     cout << sol.numberOfBeautifulIntegers(0, i, i) << endl;
}
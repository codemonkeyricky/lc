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
    int dfs(string &ref, string &curr, int odd, int even, int ceil = 1)
    {
        if (!odd && !even)
            return stoi(curr);

        int r;
        for (auto i = ceil ? ref[curr.size()] - '0' : 0; i < 10; ++i)
        {
            curr.push_back(i + '0');
            if (i % 2 && odd)
                r = dfs(ref, curr, odd - 1, even, ceil && i == ref[curr.size() - 1] - '0');
            else if (i % 2 == 0 && even)
                r = dfs(ref, curr, odd, even - 1, ceil && i == ref[curr.size() - 1] - '0');
            if (r)
                return r;
            curr.pop_back();
        }

        return 0;
    }

public:
    int closestFair(int n)
    {
        int nn = n, d = 0;
        while (nn)
            ++d, nn /= 10;

        if (d % 2)
        {
            ++d;
            string ref(d, '0');
            ref[0] = '1';
            string curr;
            return dfs(ref, curr, d / 2, d / 2);
        }

        string curr, ref = to_string(n);
        auto r = dfs(ref, curr, d / 2, d / 2);
        if (r)
            return r;

        ref = string(d + 2, '0');
        ref[0] = '1';
        return dfs(ref, curr, d / 2 + 1, d / 2 + 1);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.closestFair(4608);
    cout << r << endl;

    r = sol.closestFair(99999999);
    cout << r << endl;

    r = sol.closestFair(999999);
    cout << r << endl;

    r = sol.closestFair(403);
    cout << r << endl;

    r = sol.closestFair(2);
    cout << r << endl;
}
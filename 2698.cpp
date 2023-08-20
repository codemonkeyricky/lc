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

vector<int> ans;
class Solution
{
    int dfs(int n, string &s, int k)
    {
        if (k >= s.size())
            return n == 0;

        string d;
        for (auto i = k; i < s.size(); ++i)
        {
            d += s[i];
            if (dfs(n - stoi(d), s, i + 1))
                return true;
        }
        return false;
    }

    bool isPunish(int n)
    {
        auto s = to_string(n * n);
        return dfs(n, s, 0);
    }

public:
    int punishmentNumber(int n)
    {
        if (ans.empty())
        {
            ans = vector<int>(1001);
            for (auto i = 1; i < ans.size(); ++i)
            {
                ans[i] = i ? ans[i - 1] : 0;
                if (isPunish(i))
                    ans[i] += i * i;
            }
        }

        return ans[n];
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.punishmentNumber(10);
    cout << r << endl;
}
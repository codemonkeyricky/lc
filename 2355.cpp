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
    long long ssum(long long l, int cnt)
    {
        return (l * (l + 1) - (l > cnt ? (l - cnt) * (l - cnt + 1) : 0)) / 2;
    }
    long long maximumBooks(vector<int> &b)
    {
        vector<int> stack;
        long long cur = 0, rv = 0;
        for (int i = 0; i < b.size(); ++i)
        {
            while (!stack.empty() && b[i] - b[stack.back()] < i - stack.back())
            {
                int j = stack.back();
                stack.pop_back();
                cur -= ssum(b[j], stack.empty() ? j + 1 : j - stack.back());
            }
            cur += ssum(b[i], stack.empty() ? i + 1 : i - stack.back());
            stack.push_back(i);
            rv = max(cur, rv);
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maximumBooks(vector<int>() = {1, 8, 2, 3, 7, 3, 4, 0, 1, 4, 3});
    cout << r << endl;
}
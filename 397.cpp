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
    int integerReplacement(int n)
    {
        priority_queue<array<long, 2>, vector<array<long, 2>>, greater<array<long, 2>>> q;
        q.push({0, n});
        while (q.size())
        {
            auto [c, n] = q.top();
            q.pop();
            if (n == 1)
                return c;

            if (n % 2)
                q.push({c + 1, n - 1}), q.push({c + 1, n + 1});
            else
                q.push({c + 1, n / 2});
        }

        return -1;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}
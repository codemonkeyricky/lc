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
    const static int N = 30001;
    vector<int> bit; 
    void update(int k, int v)
    {
        ++k;
        for (; k < N; k += k & -k)
            bit[k] += v;
    }

    int get(int k)
    {
        ++k;
        int rv = 0;
        for (; k; k -= k & -k)
            rv += bit[k];
        return rv;
    }

public:
    string minInteger(string num, int k)
    {
        bit = vector<int>(N);

        int n = num.size();
        for (auto i = 0; i < n; ++i)
            update(i, 1);

        priority_queue<array<int, 2>, vector<array<int, 2>>, greater<array<int, 2>>> q;
        for (auto i = 0; i < num.size(); ++i)
            q.push({num[i], i});

        string rv;
        vector<int> seen(num.size());
        while (k && q.size())
        {
            auto [v, i] = q.top();
            q.pop();
            auto moves = get(i - 1);
            if (moves <= k)
            {
                k -= moves, seen[i] = 1, rv += v;
                update(i, -1);
            }
        }

        for (auto i = 0; i < num.size(); ++i)
            if (!seen[i])
                rv += num[i];

        return rv;
    }
};

int main()
{
    Solution sol;
    string r;

    r = sol.minInteger("294984148179", 11);
    cout << r << endl;

    r = sol.minInteger("100", 1);
    cout << r << endl;

    r = sol.minInteger("4321", 4);
    cout << r << endl;
}
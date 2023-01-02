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
    int tilingRectangle(int n, int m)
    {
        if (n > m)
            swap(n, m);
        vector<int> S;
        for (int i = 0; i < n; i++)
        {
            S.push_back(m);
        }
        maxDepth = max(n, m);
        dfs(S, 0);
        return maxDepth;
    }

    int maxDepth;
    typedef long long Key;
    unordered_map<Key, int> dp;
    Key hash(vector<int> &vec)
    {
        Key r = 0;
        for (int n : vec)
        {
            r = (r << 4LL) + n;
        }
        return r;
    }

    void dfs(vector<int> &vec, int dfsDepth)
    {
        Key h = hash(vec);
        if (h == 0)
        {
            maxDepth = min(maxDepth, dfsDepth);
            return;
        }
        if (dfsDepth >= maxDepth or dp.count(h))
        {
            return;
        }

        auto topLeft = max_element(vec.begin(), vec.end());
        int width = 1;
        for (auto top = topLeft + 1; top != vec.end() and *top == *topLeft; top++)
        {
            width++;
        }

        for (int w = min(width, *topLeft); w > 0; w--)
        {
            for (int i = 0; i < w; i++)
            {
                *(topLeft + i) -= w;
            }
            dfs(vec, dfsDepth + 1);
            for (int i = 0; i < w; i++)
            {
                *(topLeft + i) += w;
            }
        }
    }
};

int main()
{
    Solution sol;
    int r;

    cout << sol.tilingRectangle(11, 13) << endl;
    cout << sol.tilingRectangle(7, 9) << endl;
    cout << sol.tilingRectangle(5, 8) << endl;
    cout << sol.tilingRectangle(2, 3) << endl;
}
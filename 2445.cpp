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
    int numberOfNodes(int n, vector<int> &queries)
    {
        unordered_set<int> set;
        for (auto &q : queries)
            if (!set.count(q))
                set.insert(q);
            else
                set.erase(q);

        sort(begin(queries), end(queries), greater<int>());

        vector<int> tree(n + 1);
        for (int i = n, k = i; i >= 0; --i, k = i)
        {
            int v = 0;
            while (k)
                v = set.count(k) ? !v : v, k /= 2;
            tree[i] = v;
        }

        return accumulate(begin(tree), end(tree), 0);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.numberOfNodes(5, vector<int>() = {1, 2, 5});
    cout << r << endl;
}
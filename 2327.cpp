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
    int peopleAwareOfSecret(int n, int d, int f)
    {
        constexpr int m = 1000000007;

        vector<long> forget(n + f);
        vector<long> active(n + f);
        vector<long> inactive(n + f);

        long sharer = 0, holder = 1;
        inactive[0] = 1;
        active[d] = 1;
        forget[f] = 1;
        for (auto i = 0; i < n; ++i)
        {
            holder = (holder - active[i]) % m;
            if (holder < 0)
                holder += m;
            sharer = (sharer + active[i] - forget[i]) % m;
            if (sharer < 0)
                sharer += m;
            holder = (holder + sharer) % m;
            active[i + d] = (active[i + d] + sharer) % m;
            forget[i + f] = (forget[i + f] + sharer) % m;
        }

        return (holder + sharer) % m; 
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.peopleAwareOfSecret(592, 1, 10);
    cout << r << endl;

    r = sol.peopleAwareOfSecret(684, 18, 496);
    cout << r << endl;

    r = sol.peopleAwareOfSecret(4, 1, 3);
    cout << r << endl;

    r = sol.peopleAwareOfSecret(6, 2, 4);
    cout << r << endl;
}
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

using v = vector<int>;
using vv = vector<vector<int>>;
class Solution
{
public:
    vector<int> productQueries(int n, vector<vector<int>> &queries)
    {
        int p = 1;
        v power;
        while (p <= n)
            power.push_back(p), p *= 2;

        reverse(begin(power), end(power));

        v num;
        int k = 0;
        while (n)
        {
            while (power[k] > n)
                ++k;
            num.push_back(power[k]);
            n -= power[k];
        }

        reverse(begin(num), end(num));

        v rv; 
        for(auto &q : queries)
        {
            long r = 1;
            for (auto i = q[0]; i <= q[1]; ++i)
                r = (num[i] * r) % 1000000007;
            rv.push_back(r);
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.productQueries(15, vector<vector<int>>() = {{0, 1}, {2, 2}, {0, 3}});
    cout << r << endl;
}
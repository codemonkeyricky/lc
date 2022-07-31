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
    vector<int> sortJumbled(vector<int> &mapping, vector<int> &nums)
    {
        vector<array<int, 3>> tmp;
        int k = 0;
        for(auto & n : nums)
        {
            int nn = n;
            int rev = 0, d = !n;
            string s;
            while (n)
                rev *= 10, rev += n % 10, n /= 10, ++d;
            int r = 0;
            while (rev || d)
                r *= 10, r += mapping[rev % 10], rev /= 10, --d;

            tmp.push_back({r, k, nn});
            ++k;
        }
        sort(begin(tmp), end(tmp));

        vector<int> rv;
        for (auto &[rev, k, n] : tmp)
            rv.push_back(n);
        return rv;
    }
};

int main()
{
    Solution sol;
    vector<int> r;

    r = sol.sortJumbled(vector<int>() = {9, 7, 0, 6, 2, 3, 1, 4, 5, 8}, vector<int>() = {49563, 13160, 242, 87356, 7905, 649399});
    for (auto &c : r)
        cout << c << endl;

    r = sol.sortJumbled(vector<int>() = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0}, vector<int>() = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    for (auto &c : r)
        cout << c << endl;
}
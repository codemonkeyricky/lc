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
    vector<int> pathInZigZagTree(int label)
    {
        int size = 1;
        int mmax = 0, rev = 0;
        while (mmax + size < label)
        {
            mmax += size;
            size *= 2;
        }
        mmax += size;

        vector<int> rv = {label};
        // if (rev)
        // {
        //     auto l = mmax - size + 1, r = mmax;
        //     auto p = label - l;
        //     rv.push_back(r - p);
        // }
        // else
        //     rv.push_back(label);

        while (rv.back() / 2)
            rv.push_back(rv.back() / 2);

        int rev = 0;
        for (auto &n : rv)
        {
            auto l = mmax - size + 1, r = mmax;
            auto p = n - l;
            if (rev)
                n = r - p;
            mmax -= size, size /= 2, rev = !rev;
        }

        reverse(begin(rv), end(rv));

        return rv;
    }
};

int main()
{
    Solution sol;
    vector<int>  r;

    r = sol.pathInZigZagTree(26);
    for (auto &c : r)
        cout << c << ", ";
    cout << endl;
}
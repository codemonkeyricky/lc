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
    vector<int> findThePrefixCommonArray(vector<int> &A, vector<int> &B)
    {
        int n = A.size();
        vector<int> rv(n);
        vector<int> cnt(n + 1);
        for (auto i = 0; i < n; ++i)
            cnt[i + 1] = 2;
        int common = n;
        for (int i = n - 1; i >= 0; --i)
        {
            rv[i] = common;
            if (A[i] == B[i])
            {
                cnt[A[i]] -= 2;
                --common;
            }
            else 
            {
                if (cnt[A[i]]-- == 2)
                    --common;
                if (cnt[B[i]]-- == 2)
                    --common;
            }
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    vector<int> r;

    r = sol.findThePrefixCommonArray(vector<int>() = {1, 3, 2, 4}, vector<int>() = {3, 1, 2, 4});
    for (auto &c : r)
        cout << c << ", ";
    cout << endl;

    r = sol.findThePrefixCommonArray(vector<int>() = {1, 2, 3}, vector<int>() = {1, 3, 2});
    for (auto &c : r)
        cout << c << ", ";
    cout << endl;
}
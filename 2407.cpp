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
    /* 
     *  Segment tree
     */ 

    const static int N = 100001;
    array<int, 2 * N> segment = {};

    void update(int k, int val)
    { 
        k += N;
        segment[k] = val;
        while (k > 1)
            k >>= 1, segment[k] = max(segment[2 * k], segment[2 * k + 1]);
    }

    int query(int l, int r)
    { 
        l += N, r += N;
        int rv = 0;

        while (l < r)
        {
            if (l & 1)
                rv = max(rv, segment[l++]);

            if (r & 1)
                rv = max(rv, segment[--r]);

            l >>= 1, r >>= 1;
        }
        return rv;
    }

public:
    int lengthOfLIS(vector<int> &A, int k)
    {
        int rv = 0;
        for (int i = 0; i < A.size(); ++i)
        {
            int l = max(0, A[i] - k), r = A[i];
            int res = query(l, r) + 1; // best res for the current element
            rv = max(rv, res);
            update(A[i], res); // and update it here
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.lengthOfLIS(vector<int>() = {4, 2, 1, 4, 3, 4, 5, 8, 15}, 3);
    cout << r << endl;
}
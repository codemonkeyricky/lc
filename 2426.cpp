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
    vector<int> bit;
    const static int N = 600001;

    void update(int k, int add)
    {
        k += N / 2;
        for (; k < N; k += k & -k)
            bit[k] += add;
    }

    int get(int k,int rv = 0)
    {
        k += N / 2;
        for (; k; k -= k & -k)
            rv += bit[k];
        return rv;
    }

public:
    long long numberOfPairs(vector<int> &nums1, vector<int> &nums2, int diff)
    {
        bit = vector<int>(N);

        int n = nums1.size();
        vector<int> nums3;
        for (auto i = 0; i < n; ++i)
        {
            nums3.push_back(nums1[i] - nums2[i]);
            update(nums3.back(), 1);
        }

        long long rv = 0;
        for (auto i = 0; i < n; ++i)
        {
            int h = get(N / 2);
            int l = get(nums3[i] - diff - 1);
            rv += h - l;
            if (diff >= 0)
                --rv;
            update(nums3[i], -1);
        }
        return rv;
    }
};

int main()
{
    {
        Solution sol;
        int r;
        r = sol.numberOfPairs(vector<int>() = {3, -1}, vector<int>() = {-2, 2}, -1);
        cout << r << endl;
    }

    {
        Solution sol;
        int r;
        r = sol.numberOfPairs(vector<int>() = {3, 2, 5}, vector<int>() = {2, 2, 1}, 1);
        cout << r << endl;
    }
}
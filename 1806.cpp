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
    int reinitializePermutation(int n)
    {
        vector<int> init;
        for (auto i = 0; i < n; ++i)
            init.push_back(i);

        int rv = 0;
        vector<int> curr = init;
        do
        {
            vector<int> arr(n);
            for (auto i = 0; i < n; ++i)
                if (i % 2 == 0)
                    arr[i] = curr[i / 2];
                else
                    arr[i] = curr[n / 2 + (i - 1) / 2];
            
            swap(arr, curr);
        } while (++rv && curr != init);

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}
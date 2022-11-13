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
    vector<int> decrypt(vector<int> &code, int k)
    {
        int n = code.size();
        vector<int> rv(n, 0);

        if (k == 0)
            return rv;
        // First window will be from index 1 to index k
        int start = 1, end = k;
        if (k < 0)
        {
            // if k is negative then the first window will be the last k elements
            k *= -1;
            start = n - k;
            end = n - 1;
        }

        int sum = 0;
        // maintaining first window
        for (int i = start; i <= end; i++)
            sum += code[i];

        for (int i = 0; i < n; i++)
        {
            rv[i] = sum;
            // sliding the window
            sum -= code[(start++) % n];
            sum += code[(++end) % n];
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}
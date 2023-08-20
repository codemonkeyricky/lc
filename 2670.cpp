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
    vector<int> distinctDifferenceArray(vector<int> &nums)
    {
        map<int, int> m1, m2;
        for (auto &n : nums)
            ++m2[n];

        vector<int> rv;
        for (auto &n : nums)
        {
            ++m1[n];
            --m2[n];
            if (m2[n] == 0)
                m2.erase(n);

            rv.push_back(m1.size() - m2.size());
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
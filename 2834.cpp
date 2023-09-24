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
    long long minimumPossibleSum(int n, int target)
    {
        set<long long> uniq;
        int k = 1;
        while (n)
        {
            while (uniq.count(target - k))
                ++k;
            uniq.insert(k++);
            --n;
        }

        long long sum = 0;
        for (auto &u : uniq)
            sum += u;
        return sum;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minimumPossibleSum(2, 3);
    cout << r << endl;
}
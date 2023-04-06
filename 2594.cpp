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
    long long repairCars(vector<int> &ranks, int cars)
    {
        long long l = 1, r = 1e15;
        while (l < r)
        {
            auto m = (l + r) / 2;
            int k = cars;
            for (auto &r : ranks)
            {
                auto kk = (int)sqrt(m / r);
                k = max(0, k - kk);
            }

            if (k == 0)
                r = m;
            else
                l = m + 1;
        }
        return l;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.repairCars(vector<int>() = {4, 2, 3, 1}, 10);
    cout << r << endl;
}
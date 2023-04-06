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
    long long minCost(vector<int> &b1, vector<int> &b2)
    {
        map<int, long long> m;
        for (auto c : b1)
            ++m[c];
        for (auto c : b2)
            --m[c];
        long long swaps = 0, res = 0;
        for (auto [c, cnt] : m)
        {
            if (cnt % 2)
                return -1;
            swaps += max(0LL, cnt / 2);
        }
        for (auto [c, cnt] : m)
        {
            long long take = min(swaps, abs(cnt) / 2);
            res += take * min(c, begin(m)->first * 2);
            swaps -= take;
        }
        return res;
    }
};

int main()
{
    Solution sol;
    int r;


    r = sol.minCost(vector<int>() = {84, 80, 43, 8, 80, 88, 43, 14, 100, 88}, vector<int>() = {32, 32, 42, 68, 68, 100, 42, 84, 14, 8});
    cout << r << endl;

    r = sol.minCost(vector<int>() = {4, 4, 4, 4, 3}, vector<int>() = {5, 5, 5, 5, 3});
    cout << r << endl;

    r = sol.minCost(vector<int>() = {4, 2, 2, 2}, vector<int>() = {1, 4, 1, 2});
    cout << r << endl;
}

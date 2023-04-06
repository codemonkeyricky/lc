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
    set<double> dfs(vector<int> &cards, int i, int j)
    {
        if (i >= j)
            return {};

        if (i + 1 == j)
            return {(double)cards[i]};

        set<double> rv;
        for (auto k = i + 1; k < j; ++k)
        {
            auto a = dfs(cards, i, k);
            auto b = dfs(cards, k, j);

            for (auto &aa : a)
                for (auto &bb : b)
                {
                    rv.insert(aa + bb);
                    rv.insert(aa - bb);
                    rv.insert(aa * bb);
                    if (bb)
                        rv.insert(aa / bb);
                }
        }
        return rv; 
    }

public:
    bool judgePoint24(vector<int> &cards)
    {
        for (auto k = 0; k < 24; ++k, next_permutation(begin(cards), end(cards)))
        {
            auto rv = dfs(cards, 0, 4);
            auto it = rv.lower_bound(24);
            if (it != rv.end() && abs(*it - 24) < 0.00001f)
                return true;
            if (it != rv.begin() && abs(*prev(it) - 24) < 0.00001f)
                return true;
        }
        return false;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.judgePoint24(vector<int>() = {1, 2, 1, 2});
    cout << r << endl;

    r = sol.judgePoint24(vector<int>() = {1, 3, 4, 6});
    cout << r << endl;

    r = sol.judgePoint24(vector<int>() = {8, 4, 7, 1});
    cout << r << endl;

    r = sol.judgePoint24(vector<int>() = {1, 2, 1, 2});
    cout << r << endl;
}
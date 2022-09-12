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
    void dfs(vector<int> &digits, int mask, int curr, vector<int> &rv)
    {
        if (__builtin_popcount(mask) >= 3)
        {
            if (curr >= 100 && curr % 2 == 0)
                rv.push_back(curr);
            return;
        }

        for (auto i = 0; i < digits.size(); ++i)
            if (!((1 << i) & mask))
                dfs(digits, mask | (1 << i), curr * 10 + digits[i], rv);
    }

public:
    vector<int> findEvenNumbers(vector<int> &digits)
    {
        vector<int> cnt(10);
        for (auto &d : digits)
            cnt[d] = min(3, cnt[d] + 1);
        
        vector<int> d;
        for (auto i = 0; i < 10; ++i)
            for (auto j = 0; j < cnt[i]; ++j)
                d.push_back(i);

        swap(d, digits);

        vector<int> rv;
        dfs(digits, 0, 0, rv);
        sort(begin(rv), end(rv));
        rv.erase(unique(rv.begin(), rv.end()), rv.end());
        return rv; 
    }
};

int main()
{
    Solution sol;
    int r;

    sol.findEvenNumbers(vector<int>() = {2, 1, 3, 0});
    cout << r << endl;

    sol.findEvenNumbers(vector<int>() = {0, 1, 2, 8, 2, 7, 5, 0, 8, 9, 5, 9, 8, 9, 0, 5, 0, 5, 8, 0, 5, 1, 8, 6, 7, 2, 2, 0, 4, 8, 2, 9, 7, 3, 8, 6, 3, 8, 5, 2, 4, 6, 2, 0, 7, 4, 2, 3, 3, 8, 1, 7, 3, 5, 3, 8, 1, 8, 4, 0, 9, 7, 1, 7, 1, 8, 9, 5, 0, 1, 5, 0, 2, 2, 2, 7, 6, 0, 2, 7, 2, 3, 9, 3, 4, 2, 5, 5});
    cout << r << endl;
}
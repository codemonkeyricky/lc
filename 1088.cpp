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
    long rotate(long n)
    {
        int rv = 0;
        while (n)
        {
            auto d = n % 10;
            n /= 10;
            if (d == 6)
                d = 9;
            else if (d == 9)
                d = 6;
            rv = rv * 10 + d;
        }
        return rv;
    }

    int dfs(long n, long k, set<int> &uniq)
    {
        if (k > n)
            return 0 ;
        
        int rv = 0;
        auto rotated = rotate(k);
        if (rotated != k)
            ++rv; 

        vector<int> valid = {0, 1, 6, 8, 9};
        for (auto i = k ? 0 : 1; i < valid.size(); ++i)
            rv += dfs(n, k * 10 + valid[i], uniq);
        return rv;
    }

public:
    int confusingNumberII(int n)
    {
        set<int> uniq; 
        return dfs(n, 0, uniq);
        // return uniq.size();
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.confusingNumberII(1000000000);
    cout << r << endl;

    r = sol.confusingNumberII(100);
    cout << r << endl;

    r = sol.confusingNumberII(20);
    cout << r << endl;
}
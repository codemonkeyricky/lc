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
    bool valid(int time)
    {
        int hh = time / 100;
        int mm = time % 100;
        return hh < 24 && mm < 60;
    }

    void dfs(vector<int> &arr, int mask, int time, int &rv)
    {
        int m = 1;
        for(auto i = 0; i < 4; ++ i)
            if (mask & (1 << i))
                m *= 10;

        if (m > 1000)
        {
            if (valid(time))
                rv = max(rv, time);
            return;
        }

        for (auto i = 0; i < 4; ++i)
            if (!(mask & (1 << i)))
                dfs(arr, mask | (1 << i), time + m * arr[i], rv);
    }

public:
    string largestTimeFromDigits(vector<int> &arr)
    {
        int rv = -1;
        dfs(arr, 0, 0, rv);
        if (rv == -1)
            return "";

        int hh = rv / 100;
        int mm = rv % 100;

        string hhs("00");
        hhs[0] = hh / 10 + '0';
        hhs[1] = hh % 10 + '0';
        string mms("00");
        mms[0] = mm / 10 + '0';
        mms[1] = mm % 10 + '0';

        return hhs + ":" + mms;
    }
};

int main()
{
    Solution sol;
    string r;

    r = sol.largestTimeFromDigits(vector<int>() = {1, 2, 3, 4});
    cout << r << endl;
}
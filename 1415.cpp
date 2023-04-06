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
    string dfs(int n, int k, int i, int &j, int l, string &curr)
    {
        if (i >= n)
            return ++j == k ? curr : "";

        string r;
        for (auto ch = 'a'; ch <= 'c'; ++ch)
            if (ch != l)
            {
                curr.push_back(ch); 
                if ((r = dfs(n, k, i + 1, j, ch, curr)) != "")
                    return r;
                curr.pop_back();
            }

        return "";
    }

public:
    string getHappyString(int n, int k)
    {
        int j = 0;
        return dfs(n, k, 0, j, -1, string() = {});
    }
};

int main()
{
    Solution sol;
    string r;

    r = sol.getHappyString(3, 9);
    cout << r << endl;

    r = sol.getHappyString(1, 3);
    cout << r << endl;
}
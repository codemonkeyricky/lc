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
    string stringShift(string s, vector<vector<int>> &shift)
    {
        int rot = 0, n = s.size();
        for (auto &sh : shift)
        {
            rot += (sh[0] ? -1 : 1) * (sh[1] % n);
            if (rot < 0)
                rot += n;
            rot %= n;
        }
        rotate(begin(s), begin(s) + rot, end(s));
        return s;
    }
};

int main()
{
    Solution sol;
    string r;

    r = sol.stringShift("abc", vector<vector<int>>() = {{0, 1}, {1, 2}});
    cout << r << endl;
}
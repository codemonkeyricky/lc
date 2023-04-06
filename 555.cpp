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
    string splitLoopedString(vector<string> &strs)
    {
        string s, rv;
        for (auto i = 0; i < strs.size(); ++i)
        {
            auto r = strs[i];
            reverse(r.begin(), r.end());
            s += max(r, strs[i]);
        }

        for (auto i = 0, l = 0; i < strs.size(); l += strs[i++].size())
        {
            string p1, p2;
            p1 = p2 = strs[i];
            reverse(begin(p2), end(p2));

            auto body = s.substr(l + p1.size()) + s.substr(0, l);

            for (auto j = 0; j < strs[i].size(); ++j)
            {
                if (p1[j] >= rv[0])
                    rv = max(rv, p1.substr(j) + body + p1.substr(0, j));

                if (p2[j] >= rv[0])
                    rv = max(rv, p2.substr(j) + body + p2.substr(0, j));
            }
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    string r;

    r = sol.splitLoopedString(vector<string>() = {"abc", "xyz"});
    cout << r << endl;
}
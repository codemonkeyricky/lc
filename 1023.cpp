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
    vector<bool> camelMatch(vector<string> &queries, string pattern)
    {
        vector<bool> rv;
        for (auto &q : queries)
        {
            int i, j;
            for (i = j = 0; i < q.size() && j < pattern.size(); ++i)
                if (q[i] == pattern[j])
                    ++j;
                else if (isupper(q[i]))
                    break;
            if (j != pattern.size())
                rv.push_back(false);
            else 
            {
                while(i < q.size())
                    if (isupper(q[i]))
                        break;
                    else 
                        ++i;
                rv.push_back(i >= q.size());
            }
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.camelMatch(vector<string>() = {"ForceFeedBack", "FooBar", "FooBarTest", "FootBall", "FrameBuffer", "ForceFeedBack"}, "FB");
}
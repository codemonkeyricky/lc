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
    vector<string> findOcurrences(string text, string first, string second)
    {
        string c, p, pp;
        vector<string> rv; 
        for (auto i = 0; i <= text.size(); ++i)
            if (i == text.size() || text[i] == ' ')
            {
                if (pp == first && p == second)
                    rv.push_back(c);
                pp = p, p = c, c.clear();
            }
            else
                c += text[i];
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.findOcurrences("alice is a good girl she is a good student", "a", "good");
}
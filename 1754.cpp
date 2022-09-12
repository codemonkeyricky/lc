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
    string largestMerge(string w1, string w2)
    {
        string rv;
        int i, j, k;
        for (i = 0, j = 0; i < w1.size() && j < w2.size();)
        {
            k = 1; 
            int found = false;
            while (i + k <= w1.size() && j + k <= w2.size())
            {
                auto s1 = w1.substr(i, k);
                auto s2 = w2.substr(j, k);
                if (s1 > s2)
                {
                    rv += s1, i += k;
                    found = true;
                    break;
                }
                else if (s1 < s2)
                {
                    rv += s2, j += k;
                    found = true;
                    break;
                }
                ++k;
            }
            if (!found)
                break;
        }

        if (i + k - 1 >= w1.size())
            rv += w1.substr(i, k - 1), i += k - 1;
        if (j + k - 1 >= w2.size())
            rv += w2.substr(j, k - 1), j += k - 1;

        if (i < w1.size())
            rv += w1.substr(i);
        if (j < w2.size())
            rv += w2.substr(j);
        return rv;
    }
};

int main()
{
    Solution sol;
    string r;

    r = sol.largestMerge("guguuuuuuuuuuuuuuguguuuuguug", "gguggggggguuggguugggggg");
    cout << r << endl;

    r = sol.largestMerge("ddwdddddddddddddwwddddddwddw", "wwwwwwwwwddwwdwwwwwwwwwwwwwww");
    cout << r << endl;

    r = sol.largestMerge("cabaa", "bcaaa");
    cout << r << endl;
}
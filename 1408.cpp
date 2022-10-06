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
    vector<string> stringMatching(vector<string> &words)
    {
        sort(begin(words), end(words), [](const string &l, const string &r)
             { return l.size() < r.size(); });

        vector<string> rv;
        for (auto i = 0; i < words.size(); ++i)
            for (int j = i + 1, k = rv.size(); j < words.size() && k == rv.size(); ++j)
                if (string::npos != words[j].find(words[i]))
                    rv.push_back(words[i]);
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}
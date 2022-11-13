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
    vector<string> splitMessage(string msg, int limit)
    {
        int i, j;
        int l = 1, r = 1e6;
        while (l < r)
        {
            auto m = (l + r) / 2;
            int fit = true, must_fit = false;
            for (i = 0, j = 0; i < m && j < msg.size() && fit; ++i)
            {
                auto tag = "<" + to_string(i + 1) + "/" + to_string(m) + ">";
                int remain = limit - tag.size();
                if (tag.size() >= limit)
                {
                    must_fit = true;
                    break;
                }
                while (remain > 0)
                    ++j, --remain;
            }
            if (!must_fit)
                fit = j >= msg.size();

            if (fit)
                r = m;
            else
                l = m + 1;
        }

        vector<string> rv;
        for (i = 0, j = 0; i < l && j < msg.size(); ++i)
        {
            auto tag = "<" + to_string(i + 1) + "/" + to_string(l) + ">";
            int remain = limit - tag.size();
            string word;
            while (remain > 0 && j < msg.size())
                word += msg[j++], --remain;
            word += tag;
            rv.push_back(word);
        }
        if (j >= msg.size())
            return rv;
        return {};
    }
};

int main()
{
    Solution sol;
    vector<string> r;

    r = sol.splitMessage("short message", 15);
    for (auto &w : r)
        cout << w << ", ";
    cout << endl;

    r = sol.splitMessage("this is really a very awesome message", 9);
    for (auto &w : r)
        cout << w << ", ";
    cout << endl;
}
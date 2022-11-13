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
    string arrangeWords(string text)
    {
        string word;
        vector<string> words;
        vector<array<int, 2>> dp;
        for (auto i = 0, k = 0; i <= text.size(); ++i)
        {
            if (i == text.size() || text[i] == ' ')
                dp.push_back({(int)word.size(), k++}), words.push_back(word), word.clear();
            else
                word += text[i]; 
        }

        sort(begin(dp), end(dp));

        string rv;
        for(auto i = 0 ; i < dp.size(); ++i)
        {
            auto [l, k] = dp[i];
            if (i == 0)
                words[k][0] = toupper(words[k][0]);
            else
                words[k][0] = tolower(words[k][0]);
            rv += words[k];
            rv += " ";
        }
        rv.pop_back();
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.arrangeWords("Leetcode is cool");
}

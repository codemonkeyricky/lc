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
    vector<string> wordsAbbreviation(vector<string> &words)
    {
        unordered_map<string, int> lookup;
        for (auto i = 0; i < words.size(); ++i)
            lookup[words[i]] = i;

        int n = words.size();
        vector<string> rv(n);
        int prefix = 1;
        while (words.size())
        {
            map<string, vector<string>> abbrev;
            for (auto &w : words)
            {
                auto len = prefix + to_string(w.size() - prefix - 1).size() + 1;
                if (w.size() <= len)
                    abbrev[w].push_back(w);
                else
                    abbrev[w.substr(0, prefix) + to_string(w.size() - prefix - 1) + w.back()].push_back(w);
            }

            words.clear();

            int rrv = rv.size();
            for (auto &abb : abbrev)
                if (abb.second.size() == 1)
                    rv[lookup[abb.second[0]]] = abb.first;
                else
                    words.insert(words.end(), begin(abb.second), end(abb.second));
                
            ++prefix;
        }

        return rv; 
    }
};

int main()
{
    Solution sol;
    int r;

    sol.wordsAbbreviation(vector<string>() = {"like", "god", "internal", "me", "internet", "interval", "intension", "face", "intrusion"});
}
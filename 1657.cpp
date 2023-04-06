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
    bool closeStrings(string word1, string word2)
    {
        if (word1.size() != word2.size())
            return false;

        vector<int> cnt1(26), cnt2(26);

        for (auto i = 0; i < word1.size(); ++i)
            ++cnt1[word1[i] - 'a'], ++cnt2[word2[i] - 'a'];

        vector<int> dist1, dist2;
        for (auto &c : cnt1)
            dist1.push_back(c);
        for (auto &c : cnt2)
            dist2.push_back(c);

        sort(begin(dist1), end(dist1));
        sort(begin(dist2), end(dist2));

        for (auto i = 0; i < 26; ++i)
            if (dist1[i] != dist2[i])
                return false;

        unordered_set<char> seen;
        for (auto i = 0; i < 26; ++i)
            if (word1[i])
                seen.insert(i);

        for (auto i = 0; i < 26; ++i)
            if (word2[i])
                if (!seen.count(i))
                    return false;

        return true;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.closeStrings("cabbba", "abbccc");
    cout << r << endl;
}
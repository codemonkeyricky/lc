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
    bool contains(vector<string> &v1, vector<string> &v2)
    {
        int i = 0, j = v1.size() - 1, k = 0, l = v2.size() - 1;
        while (i <= j && k <= l)
        {
            if (v1[i] == v2[k])
                ++i, ++k;
            else if (v1[j] == v2[l])
                --j, --l;
            else
                return false;
        }
        return i > j;
    }

public:
    bool areSentencesSimilar(string s1, string s2)
    {
        vector<string> v1, v2;
        string word;
        for (auto i = 0; i <= s1.size(); ++i)
            if (i == s1.size() || s1[i] == ' ')
                v1.push_back(word), word.clear();
            else
                word += s1[i];

        for (auto i = 0; i <= s2.size(); ++i)
            if (i == s2.size() || s2[i] == ' ')
                v2.push_back(word), word.clear();
            else
                word += s2[i];

        return contains(v1, v2) || contains(v2, v1);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.areSentencesSimilar("of", "A lot of words");
    cout << r << endl;

    r = sol.areSentencesSimilar("My name is Haley", "My Haley");
    cout << r << endl;
}
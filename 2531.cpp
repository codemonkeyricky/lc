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
    bool isItPossible(string word1, string word2)
    {
        map<int, int> m1, m2;
        for (auto &c : word1)
            ++m1[c - 'a'];
        for (auto &c : word2)
            ++m2[c - 'a'];

        auto m1b = m1, m2b = m2; 
        for (auto i = 0; i < 26; ++i)
            for (auto j = 0; j < 26; ++j)
            {
                m1 = m1b, m2 = m2b;
                if (m1[i] && m2[j])
                {
                    --m1[i], ++m1[j];
                    --m2[j], ++m2[i];
                    if (!m1[i])
                        m1.erase(i);
                    if (!m2[j])
                        m2.erase(j);
                    if(m1.size() == m2.size())
                        return true;
                }
            }
        return false;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}
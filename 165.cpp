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
    int compareVersion(string version1, string version2)
    {
        vector<int> a, b;
        string w; 
        for (auto i = 0; i <= version1.size(); ++i)
            if (i == version1.size() || version1[i] == '.')
                a.push_back(stoi(w)), w.clear();
            else 
                w += version1[i];

        for (auto i = 0; i <= version2.size(); ++i)
            if (i == version2.size() || version2[i] == '.')
                b.push_back(stoi(w)), w.clear();
            else 
                w += version2[i];

        int i;
        for (i = 0; i < a.size() && i < b.size(); ++i)
            if (a[i] < b[i])
                return -1;
            else if (a[i] > b[i])
                return 1;

        while (i < a.size())
            if (a[i++])
                return 1;

        while (i < b.size())
            if (b[i++])
                return -1;
        
        return 0;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}
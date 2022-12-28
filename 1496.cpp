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
    bool isPathCrossing(string path)
    {
        set<array<int, 2>> seen = {{0, 0}};
        int i = 0, j = 0; 
        for (auto &p : path)
        {
            switch (p)
            {
            case 'N': ++i; break;
            case 'S': --i; break;
            case 'E': ++j; break;
            case 'W': --j; break;
            }

            if (seen.count({i, j}))
                return true;
            seen.insert({i, j});
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
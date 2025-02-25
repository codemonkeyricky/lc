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
    bool findRotation(vector<vector<int>> &mat, vector<vector<int>> &target)
    {
        int n = mat.size();

        if (mat == target)
            return true;

        int deg = 4;
        while (--deg)
        {
            for (int i = 0; i < n; i++)
                for (int j = i; j < n; j++)
                    swap(mat[i][j], mat[j][i]); 

            for (int i = 0; i < n; i++)
                reverse(begin(mat[i]), end(mat[i])); 

            if (mat == target)
                return true;
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
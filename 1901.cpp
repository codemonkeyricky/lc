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
    vector<int> findPeakGrid(vector<vector<int>> &mat)
    {
        int m = mat.size(); 
        int n1 = n1 = mat[0].size() - 1;
        int j = 0;
        while (j <= n1)
        {
            int maxRow = 0; 
            int mid = j + (n1 - j) / 2;

            for (int i = 0; i < mat.size(); i++)
                maxRow = mat[i][mid] >= mat[maxRow][mid] ? i : maxRow;

            bool leftIsBig = mid - 1 >= j && mat[maxRow][mid - 1] > mat[maxRow][mid];
            bool rightIsBig = mid + 1 <= n1 && mat[maxRow][mid + 1] > mat[maxRow][mid];

            if (!leftIsBig && !rightIsBig) // we have found the peak element
                return vector<int>{maxRow, mid};
            else if (rightIsBig)       // if rightIsBig, then there is an element in 'right' that is bigger than all the elements in the 'midCol',
                j = mid + 1; // so 'midCol' cannot have a 'peakPlane'
            else // leftIsBig
                n1 = mid - 1;
        }
        return vector<int>{-1, -1};
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}
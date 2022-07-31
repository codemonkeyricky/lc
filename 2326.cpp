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

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution
{
public:
    vector<vector<int>> spiralMatrix(int m, int n, ListNode *curr)
    {
        int i = 0, j = 0;
        vector<int> dir = {0, 1, 0, -1, 0};
        int k = 0;
        vector<vector<int>> rv(m, vector<int>(n, -1));
        while (curr)
        {
            rv[i][j] = curr->val;
            curr = curr->next;

            int loop = 0, ni, nj;
            while (loop < 4)
            {
                ni = i + dir[k + 0];
                nj = j + dir[k + 1];
                if (ni < 0 || ni >= m || nj < 0 || nj >= n || rv[ni][nj] != -1)
                    k = (k + 1) % 4;
                else 
                    break;
                ++loop;
            }
            i = ni, j = nj;
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}
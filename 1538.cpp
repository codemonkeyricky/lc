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
    int guessMajority(ArrayReader &reader)
    {
        int n = reader.length();
        int groupA = 1;
        int groupB = 0;
        int idxA = -1;
        int idxB = -1;
        int r0123 = reader.query(0, 1, 2, 3);
        for (int i = 4; i < n; i++)
        {
            if (reader.query(0, 1, 2, i) == r0123)
                groupA++, idxA = i;
            else
                groupB++, idxB = i;
        }

        int r0124 = reader.query(0, 1, 2, 4);
        vector<array<int, 4>> rThree(3, array<int, 4>());
        rThree[0] = {1, 2, 3, 4};
        rThree[1] = {0, 2, 3, 4};
        rThree[2] = {0, 1, 3, 4};
        for (int i = 0; i < 3; i++)
        {
            if (reader.query(rThree[i][0], rThree[i][1], rThree[i][2], rThree[i][3]) == r0124)
                groupA++, idxA = i;
            else
                groupB++, idxB = i;
        }

        if (groupA > groupB)
            return idxA;
        else if (groupA < groupB)
            return idxB;
        else
            return -1;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}
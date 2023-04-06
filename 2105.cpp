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
    int minimumRefill(vector<int> &plants, int capA, int capB)
    {
        int i = 0, j = plants.size() - 1;
        int ca = capA, cb = capB;
        int rv = 0;
        while (i < j)
        {
            if (ca < plants[i])
                ca = capA, ++rv; 
            ca -= plants[i++];

            if (cb < plants[j])
                cb = capB, ++rv; 
            cb -= plants[j--];
        }

        if (i == j)
        {
            if (ca >= cb)
            {
                if (ca < plants[i])
                    ++rv;
            }
            else 
            {
                if(cb < plants[i])
                    ++rv;
            }
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
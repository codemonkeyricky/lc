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
    int magicalString(int n)
    {
        if (n <= 0)
            return 0;

        if (n <= 3)
            return 1;
        vector<int> a = {1, 2, 2};
        a.resize(n + 1);
        int curr = 2, tail = 3, num = 1, rv = 1;
        while (tail < n)
        {
            for (int i = 0; i < a[curr]; i++)
            {
                a[tail] = num;
                if (num == 1 && tail < n)
                    rv++;
                tail++;
            }
            num = num ^ 3;
            curr++;
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.magicalString(10);
    cout << r << endl;
}
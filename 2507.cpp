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
    int smallestValue(int n)
    {
        int psum = -1;
        while (true)
        {
            int nn = n;
            int sum = 0;
            for (auto i = 2; i <= nn; ++i)
                while (nn % i == 0)
                    sum += i, nn /= i;
            if (sum == psum)
                return sum;
            n = sum; 
            psum = sum;
        }
        return -1;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.smallestValue(4);
    cout << r << endl;

    r = sol.smallestValue(15);
    cout << r << endl;
}
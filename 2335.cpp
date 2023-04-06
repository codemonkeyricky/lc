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
    int fillCups(vector<int> &amount)
    {
        priority_queue<int> cups;
        if (amount[0])
            cups.push(amount[0]);
        if (amount[1])
            cups.push(amount[1]);
        if (amount[2])
            cups.push(amount[2]);

        int rv = 0;
        while (cups.size() >= 2)
        {
            auto first = cups.top();
            cups.pop(); 
            auto second = cups.top();
            cups.pop();

            ++rv;
            if (first > 1)
                cups.push(first - 1);
            if (second > 1)
                cups.push(second - 1);
        }

        return rv + (cups.size() ? cups.top() : 0);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.fillCups(vector<int>() = {1, 4, 2});
    cout << r << endl;

    r = sol.fillCups(vector<int>() = {0, 0, 0});
    cout << r << endl;

    r = sol.fillCups(vector<int>() = {5, 4, 4});
    cout << r << endl;
}
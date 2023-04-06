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
    vector<int> memLeak(int memory1, int memory2)
    {
        priority_queue<array<int, 2>> q;
        q.push({memory1, 1});
        q.push({memory2, 0});
        int n = 1;
        while (true)
        {
            if (q.top()[0] < n)
                break;

            auto m = q.top();
            q.pop();

            m[0] -= n++;
            q.push(m);
        }

        int r0, r1;
        if (q.top()[1] == 1)
        {
            r0 = q.top()[0];
            q.pop();
            r1 = q.top()[0];
        }
        else 
        {
            r1 = q.top()[0];
            q.pop();
            r0 = q.top()[0];
        }

        return {n, r0, r1};
    }
};

int main()
{
    Solution sol;
    int r;

    sol.memLeak(8, 11);
    cout << r << endl;

    sol.memLeak(6, 4);
    cout << r << endl;
}
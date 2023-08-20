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
    vector<int> survivedRobotsHealths(vector<int> &positions, vector<int> &healths, string directions)
    {
        vector<array<int,4>> robots; // pos / health / dir
        for (auto i = 0; i < positions.size(); ++i)
            robots.push_back({positions[i], healths[i], directions[i] == 'L' ? 0 : 1, i});
        sort(begin(robots), end(robots));
        vector<array<int, 4>> stack;
        for (auto &[p, h, d, k] : robots)
            if (stack.empty())
                stack.push_back({p, h, d, k});
            else 
            {
                if (stack.back()[2] == 0 && d == 0) // both going left
                    stack.push_back({p, h, d, k});
                else if(stack.back()[2] == 0 && d == 1) // left and right
                    stack.push_back({p, h, d, k});
                else if (stack.back()[2] == 1 && d == 0) // right and left
                {
                    int push = 0;
                    while (stack.size() && stack.back()[2] == 1)
                    {
                        push = 0;
                        auto &[sp, sh, sd, sk] = stack.back();
                        if (sh > h)
                        {
                            --sh;
                            break;
                        }
                        else if (sh < h)
                            --h, stack.pop_back(), push = 1;
                        else if (sh == h)
                        {
                            stack.pop_back();
                            break;
                        }
                    }
                    if (push)
                        stack.push_back({p, h, d, k});
                }
                else  // 1 and 1
                    stack.push_back({p, h, d, k});
            }

        vector<int> rv(positions.size(), -1);
        for (auto &[p, h, d, k] : stack)
            rv[k] = h;

        vector<int> rv2;
        for (auto &r : rv)
            if (r != -1)
                rv2.push_back(r);

        return rv2;
    }
};

int main()
{
    Solution sol;
    vector<int> rv;

    rv = sol.survivedRobotsHealths(vector<int>() = {1, 40}, vector<int>() = {10, 11}, "RL");
    for (auto &r : rv)
        cout << r << ", ";
    cout << endl;

    rv = sol.survivedRobotsHealths(vector<int>() = {5, 3, 3, 2, 1}, vector<int>() = {2, 17, 9, 15, 10}, "RRRRR");
    for (auto &r : rv)
        cout << r << ", ";
    cout << endl;

    rv = sol.survivedRobotsHealths(vector<int>() = {3, 5, 2, 6}, vector<int>() = {10, 10, 15, 12}, "RLRL");
    for (auto &r : rv)
        cout << r << ", ";
    cout << endl;
}
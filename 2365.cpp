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
    long long taskSchedulerII(vector<int> &tasks, int space)
    {
        unordered_map<int, int> last;

        long long rv = 0, curr = 0;
        for (auto i = 0; i < tasks.size(); ++i)
        {
            if (!last.count(tasks[i]) || curr - last[tasks[i]] > space)
                ;
            else
            {
                auto days = last[tasks[i]] + space + 1 - curr;
                curr += days; 
            }

            last[tasks[i]] = curr;
            ++curr;
        }
        return curr; 
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.taskSchedulerII(vector<int>() = {1, 2, 1, 2, 3, 1}, 3);
    cout << r << endl;
}
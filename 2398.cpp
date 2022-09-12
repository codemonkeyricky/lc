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
    int maximumRobots(vector<int> &charge, vector<int> &running, long long budget)
    {
        long long i = 0, j = 0;
        deque<int> mono;
        for (long long cost = 0; j < charge.size(); ++j)
        {
            cost += running[j];

            while (!mono.empty() && mono.back() <= charge[j])
                mono.pop_back();
            mono.push_back(charge[j]);

            if (cost * (j - i + 1) + mono.front() > budget)
            {
                cost -= running[i];
                if (mono.front() == charge[i])
                    mono.pop_front();
                ++i;
            }
        }
        return charge.size() - i;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maximumRobots(vector<int>() = {11, 12, 74, 67, 37, 87, 42, 34, 18, 90, 36, 28, 34, 20}, vector<int>() = {18, 98, 2, 84, 7, 57, 54, 65, 59, 91, 7, 23, 94, 20}, 937);
    cout << r << endl;

    r = sol.maximumRobots(vector<int>() = {11, 12, 19}, vector<int>() = {10, 8, 7}, 19);
    cout << r << endl;

    r = sol.maximumRobots(vector<int>() = {3, 6, 1, 3, 4}, vector<int>() = {2, 1, 3, 4, 5}, 25);
    cout << r << endl;
}

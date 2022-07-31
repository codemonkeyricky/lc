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
    int latestTimeCatchTheBus(vector<int> &buses, vector<int> &passengers, int capacity)
    {
        sort(begin(buses), end(buses));
        sort(begin(passengers), end(passengers));
        int i = 0, j = 0, waiting = 0;
        int rv = 0, slot = passengers[i] ? passengers[i] - 1 : -1;
        for (; j < buses.size() && i < passengers.size(); ++j)
        {
            while (i < passengers.size() && passengers[i] <= buses[j] && waiting < capacity)
            {
                if ((i && passengers[i - 1] != passengers[i] - 1) || (!i && passengers[i]))
                    slot = passengers[i] - 1;
                ++waiting, ++i;
            }
            if (waiting < capacity && i && buses[j] != passengers[i - 1])
                slot = buses[j];

            if (waiting == 0)
                slot = buses[j];

            rv = slot;
            waiting = 0;
        }
        if (j < buses.size() && i >= passengers.size())
            return buses.back();

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.latestTimeCatchTheBus(vector<int>() = {6, 8, 18, 17}, vector<int>() = {6, 8, 17}, 1);
    cout << r << endl;

    r = sol.latestTimeCatchTheBus(vector<int>() = {5, 15}, vector<int>() = {11, 12, 13, 14, 15}, 2);
    cout << r << endl;

    r = sol.latestTimeCatchTheBus(vector<int>() = {5}, vector<int>() = {7, 8}, 1);
    cout << r << endl;

    r = sol.latestTimeCatchTheBus(vector<int>() = {3}, vector<int>() = {4}, 1);
    cout << r << endl;

    r = sol.latestTimeCatchTheBus(vector<int>() = {2}, vector<int>() = {2}, 2);
    cout << r << endl;

    r = sol.latestTimeCatchTheBus(vector<int>() = {20, 30, 10}, vector<int>() = {19, 13, 26, 4, 25, 11, 21}, 2);
    cout << r << endl;

    r = sol.latestTimeCatchTheBus(vector<int>() = {10, 20}, vector<int>() = {2, 17, 18, 19}, 2);
    cout << r << endl;
}
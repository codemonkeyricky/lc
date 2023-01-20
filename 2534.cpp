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
    void exit(vector<int> &arrival, vector<int> &exiting, int &time, int &i, vector<int> &rv)
    {
        time = max(time, arrival[exiting[i]]);
        // do
        // {
            rv[exiting[i++]] = time++;
        // } while (i < exiting.size() && arrival[exiting[i - 1]] + 1 >= arrival[exiting[i]]);
    }

    void enter(vector<int> &arrival, vector<int> &entering, int &time, int &j, vector<int> &rv)
    {
        time = max(time, arrival[entering[j]]);
        // do
        // {
            rv[entering[j++]] = time++;
        // } while (j < entering.size() && arrival[entering[j - 1]] + 1 >= arrival[entering[j]]);
    }

public:
    vector<int> timeTaken(vector<int> &arrival, vector<int> &state)
    {
        int n = arrival.size();
        vector<int> entering, exiting;
        for (auto i = 0; i < n; ++i)
            if (state[i])
                exiting.push_back(i);
            else
                entering.push_back(i);

#define ENTERING 0
#define EXITING 1

        int i = 0, j = 0, time = arrival[0], last = -1;
        vector<int> rv(n);
        while (i < exiting.size() || j < entering.size())
        {
            if (i < exiting.size() && j < entering.size())
            {
                bool exit_first = last == -1 || last == EXITING;
                if (exit_first)
                    if (time >= arrival[exiting[i]] || arrival[exiting[i]] <= arrival[entering[j]])
                        exit(arrival, exiting, time, i, rv), last = EXITING;
                    else
                        enter(arrival, entering, time, j, rv), last = ENTERING;
                else
                {
                    if (time >= arrival[entering[j]] || arrival[entering[j]] < arrival[exiting[i]])
                        enter(arrival, entering, time, j, rv), last = ENTERING;
                    else 
                        exit(arrival, exiting, time, i, rv), last = EXITING;
                }
            }
            else if (i < exiting.size())
                while (i < exiting.size())
                    exit(arrival, exiting, time, i, rv);
            else 
                while (j < entering.size())
                    enter(arrival, entering, time, j, rv);
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    vector<int> r;

    {
        r = sol.timeTaken(vector<int>() = {0, 0, 1, 2, 8, 10, 10, 10, 10, 10}, vector<int>() = {0, 1, 0, 1, 1, 0, 0, 0, 1, 1});
        for (auto &c : r)
            cout << c << ", ";
        cout << endl;
    }

    {
        r = sol.timeTaken(vector<int>() = {3, 3, 4, 5, 5, 5}, vector<int>() = {1, 0, 1, 0, 1, 0});
        for (auto &c : r)
            cout << c << ", ";
        cout << endl;
    }

    {
        r = sol.timeTaken(vector<int>() = {0, 0, 10, 11, 11, 11, 11, 11, 12, 12, 13, 14, 14, 15, 16, 18, 19, 19, 19}, vector<int>() = {1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0});
        for (auto &c : r)
            cout << c << ", ";
        cout << endl;
    }

    {
        r = sol.timeTaken(vector<int>() = {0, 5, 6, 6, 7, 9, 9, 9, 10, 10, 10, 10, 10, 15, 16, 17, 17, 17}, vector<int>() = {1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0});
        for (auto &c : r)
            cout << c << ", ";
        cout << endl;
    }

    {
        r = sol.timeTaken(vector<int>() = {0, 1, 1, 2, 4}, vector<int>() = {0, 1, 0, 0, 1});
        for (auto &c : r)
            cout << c << ", ";
        cout << endl;
    }
}
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
    int findCrossingTime(int n, int k, vector<vector<int>> &time)
    {
        priority_queue<array<int, 2>> waiting_left, waiting_right;
        for (auto i = 0; i < k; ++i)
            waiting_left.push({time[i][0] + time[i][2], i});

        // state 0 - waiting on left
        // state 1 - crossing right
        // state 2 - picking up
        // state 3 - waiting on right
        // state 4 - crossing left
        // state 5 - drop off

        int curr_time = 0, crossing = 0, stored = 0, dispatched = 0, done = 0;
        vector<int> state(k);
        priority_queue<array<int, 2>> q; ///< time, worker

        auto cross = [&](int curr)
        {
            if (!crossing)
                if (waiting_right.size())
                {
                    auto [p, worker] = waiting_right.top();
                    waiting_right.pop();
                    q.push({curr - time[worker][2], worker});
                    state[worker] = 4;
                    crossing = 1;
                }
                else if (dispatched < n && waiting_left.size())
                {
                    auto [p, worker] = waiting_left.top();
                    waiting_left.pop();
                    q.push({curr - time[worker][0], worker});
                    state[worker] = 1;
                    crossing = 1;
                    ++dispatched;
                }
        };

        cross(0);

        while (done < n)
        {
            if (q.size())
            {
                auto latest = q.top()[0];
                while (q.size() && q.top()[0] >= latest)
                {
                    auto [t, worker] = q.top();
                    q.pop();
                    if (state[worker] == 0)
                        assert(0);
                    else if (state[worker] == 1) // crossed right
                    {
                        q.push({t - time[worker][1], worker});
                        state[worker] = 2;
                        crossing = 0;
                        // cout << "worker " << worker << " crossed right @ " << t << endl;
                    }
                    else if (state[worker] == 2) // picked up, waiting to cross
                    {
                        waiting_right.push({time[worker][0] + time[worker][2], worker});
                        state[worker] = 3;
                        // cout << "worker " << worker << " picked up, waiting to cross left @ " <<  t << endl;
                    }
                    else if (state[worker] == 3) // waiting on right
                        assert(0);
                    else if (state[worker] == 4) // crosssed left
                    {
                        // cout << "worker " << worker << " crossed left, dropping off @ " << t << endl;
                        q.push({t - time[worker][3], worker});
                        state[worker] = 5;
                        crossing = 0;
                        ++done;
                        if (done == n)
                            return -t;
                    }
                    else if (state[worker] == 5) // drop off
                    {
                        waiting_left.push({time[worker][0] + time[worker][2], worker});
                    }
                }
                // maybe bridge is free
                cross(latest);
            }
        }
        return -1;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.findCrossingTime(10, 6, vector<vector<int>>() = {{2, 10, 5, 8}, {3, 5, 2, 2}, {5, 8, 10, 10}, {7, 8, 8, 5}, {5, 6, 6, 10}, {6, 10, 6, 2}});
    cout << r << endl;

    r = sol.findCrossingTime(3, 2, vector<vector<int>>() = {{1, 9, 1, 8}, {10, 10, 10, 10}});
    cout << r << endl;

    r = sol.findCrossingTime(1, 3, vector<vector<int>>() = {{1, 1, 2, 1}, {1, 1, 3, 1}, {1, 1, 4, 1}});
    cout << r << endl;
}
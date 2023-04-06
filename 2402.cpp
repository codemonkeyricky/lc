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
    int mostBooked(int n, vector<vector<int>> &meetings)
    {
        sort(begin(meetings), end(meetings));
        vector<int> rooms(n);

        priority_queue<array<long long, 2>, vector<array<long long, 2>>, greater<array<long long, 2>>> inflight;
        priority_queue<int, vector<int>, greater<int>> free;
        for (auto i = 0; i < n; ++i)
            free.push(i);

        long long current_time = 0;
        for (auto i = 0; i < meetings.size();)
        {
            /* 
             *  Free up rooms for finished meetings. 
             */

            while (inflight.size() && inflight.top()[0] <= current_time)
            {
                auto [end, avail] = inflight.top();
                inflight.pop();
                free.push(avail);
            }

            /*
             *  Next meeting start and end.
             */

            long long start = meetings[i][0];
            long long end = meetings[i][1];

            if (current_time < start)
            {
                /*
                 *  Slowly retire inprogress meeting because next meeting is far out. 
                 */

                current_time = min(start, inflight.size() ? inflight.top()[0] : start);
            }
            else
            {
                /*
                 *  A meeting is waiting. 
                 */

                if (free.size())
                {
                    auto avail = free.top();
                    free.pop();
                    inflight.push({max((long long)meetings[i][1], current_time + meetings[i][1] - meetings[i][0]), avail});
                    ++rooms[avail];
                    ++i;
                }
                else 
                {
                    current_time = inflight.size() ? inflight.top()[0] : start;
                }
            }
        }

        int rv = 0, max_count = 0;
        for (auto i = 0; i < rooms.size(); ++i)
            if (rooms[i] > max_count)
                max_count = rooms[i], rv = i;

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.mostBooked(3, vector<vector<int>>() = {{1, 20}, {2, 10}, {3, 5}, {4, 9}, {6, 8}});
    cout << r << endl;

    r = sol.mostBooked(4, vector<vector<int>>() = {{18, 19}, {3, 12}, {17, 19}, {2, 13}, {7, 10}});
    cout << r << endl;

    r = sol.mostBooked(2, vector<vector<int>>() = {{0, 10}, {1, 5}, {2, 7}, {3, 4}});
    cout << r << endl;
}
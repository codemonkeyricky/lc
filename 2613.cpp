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

struct Point
{
    int x, y, idx;
    Point(int x = 0, int y = 0, int idx = 0) : x(x), y(y), idx(idx) {}
};

int dist(const Point &p1, const Point &p2)
{
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

bool cmp_x(const Point &p1, const Point &p2)
{
    return p1.x < p2.x || (p1.x == p2.x && (p1.y < p2.y || (p1.y == p2.y && p1.idx < p2.idx)));
}

bool cmp_y(const Point &p1, const Point &p2)
{
    return p1.y < p2.y || (p1.y == p2.y && (p1.x < p2.x || (p1.x == p2.x && p1.idx < p2.idx)));
}

class Solution
{
    int closest_pair(const vector<Point> &px, const vector<Point> &py, int from, int &idx1, int &idx2)
    {
        const int n = py.size();
        if (n <= 1)
            return INT_MAX;
        else if (n == 2)
        {
            idx1 = min(py[0].idx, py[1].idx);
            idx2 = max(py[0].idx, py[1].idx);
            return dist(py[0], py[1]);
        }
        else
        {
            const int to = from + n - 1, mid = (from + to) >> 1, num = mid - from + 1;
            vector<Point> pyl, pyr;
            for (const auto &p : py)
            {
                if (p.x < px[mid].x || (p.x == px[mid].x && (p.y < px[mid].y || (p.y == px[mid].y && p.idx < px[mid].idx))))
                {
                    pyl.push_back(p);
                }
                else
                {
                    pyr.push_back(p);
                }
            }

            int idx3, idx4;
            int d1 = closest_pair(px, pyl, from, idx1, idx2);
            int d2 = closest_pair(px, pyr, mid + 1, idx3, idx4);

            if (d2 < d1 || (d2 == d1 && make_pair(idx3, idx4) < make_pair(idx1, idx2)))
            {
                d1 = d2;
                idx1 = idx3;
                idx2 = idx4;
            }
            int d = d1;
            vector<Point> strip;
            for (const auto &p : py)
            {
                if (abs(p.x - px[mid].x) <= d)
                {
                    strip.push_back(p);
                }
            }
            const int m = strip.size();
            for (int i = 0; i < m; i++)
            {
                for (int j = i + 1; j < m && strip[j].y - strip[i].y <= d; j++)
                {
                    int dist_ij = dist(strip[i], strip[j]);
                    pair<int, int> p = make_pair(min(strip[i].idx, strip[j].idx), max(strip[i].idx, strip[j].idx));
                    if (dist_ij < d || (dist_ij == d && make_pair(idx1, idx2) > p))
                    {
                        d = dist_ij;
                        idx1 = p.first;
                        idx2 = p.second;
                    }
                }
            }
            return d;
        }
    }

public:
    vector<int> beautifulPair(vector<int> &nums1, vector<int> &nums2)
    {
        const int n = nums1.size();
        if (n == 1)
            return {0, 0};

        vector<Point> px(n), py(n);
        vector<int> ans(2, n);
        map<pair<int, int>, int> have;
        for (int i = 0; i < n; ++i)
        {
            if (have.count({nums1[i], nums2[i]}))
                ans = min(ans, {have[{nums1[i], nums2[i]}], i});

            have[{nums1[i], nums2[i]}] = i;
            py[i] = px[i] = {nums1[i], nums2[i], i};
        }

        if (ans[0] < n)
            return ans;

        int x, y;
        sort(px.begin(), px.end(), cmp_x);
        sort(py.begin(), py.end(), cmp_y);
        closest_pair(px, py, 0, x, y);
        return {x, y};
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}
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
    long long val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(long long x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(long long x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

TreeNode *recurse(vector<long long> &tree, long long k)
{
    if (k >= tree.size() || tree[k] == -1)
        return nullptr;

    return new TreeNode(tree[k], recurse(tree, k * 2 + 1), recurse(tree, k * 2 + 2));
}

TreeNode *populate(vector<long long> &tree)
{
    return recurse(tree, 0);
}

class Solution
{
public:
    long long maxPower(vector<int> &stations, int radius, int k)
    {
        long long n = stations.size();
        vector<long long> delta(n + 1);
        for (long long i = 0; i < n; ++i)
        {
            delta[max(0ll, i - radius)] += stations[i];
            delta[min(n, i + radius + 1)] -= stations[i];
        }

        vector<long long> power(n);
        for (auto i = 0, sum = 0; i < n; ++i)
        {
            sum += delta[i];
            power[i] = sum;
            if (power[i] < 0)
                assert(power[i] < 0);
        }

        long long l = 0, r = 1e12, len = radius * 2 + 1;
        while (l < r)
        {
            long long extra = 0, kk = k;
            long long m = (l + r + 1) / 2;
            vector<long long> delta(n + 1);
            long long valid = true;
            for (long long i = 0; i < n; ++i)
            {
                extra += delta[i];
                long long p = power[i] + extra;
                if (p < m)
                {
                    if (m - p > kk)
                    {
                        valid = false;
                        break;
                    }
                    else 
                    {
                        extra += m - p;
                        delta[min(n, i + len)] -= m - p;
                        kk -= m - p;
                    }
                }
            }

            if (valid)
                l = m;
            else
                r = m - 1;
        }

        return l;
    }
};


int main()
{
    Solution sol;
    long long r;

    r = sol.maxPower(vector<int>() = {1, 2, 4, 5, 0}, 1, 2);
    cout << r << endl;
}

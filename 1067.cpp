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
    int count(int digit, int n) 
    {
        if(!digit)
		{
            int cnt = 0;
            for (int num = 1; num <= n; num *= 10)
            {
                int divisor = num * 10;
                cnt += (n / divisor) * num;
                if (n / divisor > 0)
                {
                    cnt -= num;
                    cnt += min(n % divisor + 1, num);
                }
            }
            return cnt; 
        }
        else
        {
            int rv = 0, d, remain = 0;
            int mul = 1;
            while (n)
            {
                int d = n % 10;
                n /= 10;
                rv += (n * mul);
                rv += min(remain + 1, mul);

                remain = d * mul + remain;
                mul *= 10;
            }
            return rv;
        }
    }

public:
    int digitsCount(int d, int low, int high)
    {
        return count(d, high) - count(d, low - 1);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.digitsCount(0, 625, 1250);
    cout << r << endl;

    r = sol.digitsCount(0, 1, 100);
    cout << r << endl;

    r = sol.digitsCount(0, 1, 10);
    cout << r << endl;

    r = sol.digitsCount(3, 1, 1332);
    cout << r << endl;

    r = sol.digitsCount(3, 1, 1333);
    cout << r << endl;

    r = sol.digitsCount(3, 1, 45);
    cout << r << endl;

    r = sol.digitsCount(3, 1, 35);
    cout << r << endl;

    r = sol.digitsCount(1, 1, 13);
    cout << r << endl;

    r = sol.digitsCount(3, 100, 250);
    cout << r << endl;
}
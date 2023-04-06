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
    double averageWaitingTime(vector<vector<int>> &customers)
    {
        long wait = 0;
        long time = 0;
        for (auto &c : customers)
        {
            long arrival = c[0];
            long cost = c[1];
            if (time >= arrival)
                wait += time - arrival;

            time = max(time, arrival);
            wait += cost;
            time += cost;
        }
        return (double)wait / customers.size();
    }
};

class Solution
{
public:
    string gcdOfStrings(string str1, string str2)
    {
        int gcd = __gcd(str1.size(), str2.size());
        string ref = str2.substr(0, gcd);
        for (auto i = 0; i < str2.size(); i += gcd)
            if (ref != str2.substr(i, gcd))
                return "";
        for (auto i = 0; i < str1.size(); i += gcd)
            if (ref != str1.substr(i, gcd))
                return ""; 
        return ref;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}
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
    int badSensor(vector<int> &sensor1, vector<int> &sensor2)
    {
        int n = sensor1.size(), k =0;
        for (; k < n; ++k)
            if (sensor1[k] != sensor2[k])
                break;
        
       if(k + 1 >= n)
            return -1; 
        
        bool is1 = false, is2 = false;
        {
            vector<int> v1(begin(sensor1) + k, begin(sensor1) + n - 1);
            vector<int> v2(begin(sensor2) + k + 1, begin(sensor2) + n);
            if (v1.empty() || v2.empty())
                return -1;

            if (sensor2[k] != sensor1[n-1] && v1 == v2)
                is1 = true;
        }

        {
            vector<int> v1(begin(sensor1) + k + 1, begin(sensor1) + n);
            vector<int> v2(begin(sensor2) + k, begin(sensor2) + n - 1);

            if (sensor1[k] != sensor2[n - 1] && v1 == v2)
                is2 = true;
        }

        if (is1 && is2)
            return -1;

        if (is1)
            return 1;

        if (is2)
            return 2;

        return -1;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.badSensor(vector<int>() = {1, 2, 3, 2, 3, 2}, vector<int>() = {1, 2, 3, 3, 2, 3});
    cout << r << endl;
}
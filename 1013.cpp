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

// class Solution
// {
// public:
//     bool canThreePartsEqualSum(vector<int> &A, int parts = 0)
//     {
//         auto total = accumulate(begin(A), end(A), 0);
//         if (total % 3 != 0)
//             return false;
//         for (auto i = 0, sum = 0; i < A.size(); ++i)
//         {
//             sum += A[i];
//             if (sum == (parts + 1) * total / 3)
//                 ++parts;
//         }
//         return parts >= 3;
//     }
// };

class Solution
{
public:
    bool canThreePartsEqualSum(vector<int> &arr)
    {
        int n = arr.size();

        int sum = accumulate(begin(arr), end(arr), 0);
        if (sum % 3)
            return false;
        sum /= 3;
        
        vector<int> prefix(n);
        for (auto i = 0; i < n; ++i)
            prefix[i] = (i ? prefix[i - 1] : 0) + arr[i];

        unordered_multiset<int> set(begin(prefix), end(prefix));

        for (auto i = 0; i < prefix.size(); ++i)
        {
            if (prefix[i] == sum)
                if (set.count(sum * 2))
                    return true;
            set.erase(set.find(prefix[i]));
        }
        return false;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.canThreePartsEqualSum(vector<int>() = {-7, 57, -76, 5, 51, -57, 27, 83, 68, 39, -38, 43, -79, 42, -79, 72, -58, -29, -34, 23, 20, -67, -67, 74, 10, -90, -91, 41, 22, -12, -75, -3, 51, 13, 9, 58, 72, -3, 48, -28, 78, 15, 13, 22, -68, 62, 33, -18, 21, -2, 56, 41, 27, -33, -35, -36, -6, -73, -9, -45, -16, 4, 51, -54, -92, 79, -92, -12, -9, 39, 1, -60, 78, 16, -77, -45, 26, -43, 44, -21, -27, 74, -68, -58, 22, 52, 100, 37, 48, 99, 98, -34, 36, 25, -85, 83, 99, -64, -37, 20, 0, 13, 85, 18, 98, -91, 86, -94, -92, -42, -82, 89, 67, -13, 43, 11, 75, 67, -38, -79, -3, -24, 83, -1, 74, -93, 26, -69, 92, 40, -32, -89, -100, -36, 80, 9, 92, 79, -83, 90, -8, -77, 1, -60, 100, 63, 87, -51, -33, 17, 24, -73, -81, -86, 52, 59, 10, -84, -71, -12, 24, -53, -14, -44, -48, -91, -57, -82, -5, 48, -56, -92, 83, -64, -17, -46, 65, -15, 87, -61, -29, 79, -53, -81, -58, 70, 70, -12, -71, 68, -57, -44, -18, -94, -84, 7, -51, 18, 44, 96, 24, 8, 61, 36, -83, -93, 38, 82, 25, 4, 37, 93, -5, 24, -9, -31, 15, -73, -91, -36, 41, 56, -17, 3, -94, -26, 96, 5, -21, -20, 60, -53, 26, 2, -97, 41, -72, -29, -83, 32, 35, -29, 82, -38, -15, 81, -10, 50, 22, 26, 30, -31, 74, -74, 47, 66, 53, 35, -58, -68, 47, -21, 78, 12, -88, 1, 12, 53, 94, 1, -43, -36, 67, 6, -89, 44, -86, -22, 48, -12, 72, -90, -7, -92, 30, -17});
    cout << r << endl;

    r = sol.canThreePartsEqualSum(vector<int>() = {0, 2, 1, -6, 6, -7, 9, 1, 2, 0, 1});
    cout << r << endl;
}
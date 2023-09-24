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
    long choose(int n, int k)
    {
        if (k == 0)
            return 1;
        return (n * choose(n - 1, k - 1) / k) % 1000000007;
    }

public:
    int countKSubsequencesWithMaxBeauty(string s, int k)
    {
        vector<int> cnt(26);
        for (auto &c : s)
            ++cnt[c - 'a'];
        
        map<int,int> map;
        for (auto &c : cnt)
            ++map[c];

        long rv = 1;
        for (auto it = map.rbegin(); k && it != map.rend(); ++it)
        {
            auto cnt = it->first;      ///< cnt
            auto letters = it->second; ///< num letters with this count
            if (k >= letters)
            {
                k -= letters;
                while (letters--)
                    rv = (rv * cnt) % 1000000007;
            }
            else
            {
                rv = (rv * choose(letters, k)) % 1000000007;
                while (k--)
                    rv = (rv * cnt) % 1000000007;
                k = 0;
            }
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.countKSubsequencesWithMaxBeauty("jyuhiyzjuk", 2);
    cout << r << endl;

    r = sol.countKSubsequencesWithMaxBeauty("dpdemprzvz", 1);
    cout << r << endl;

    r = sol.countKSubsequencesWithMaxBeauty("bccakadfkjdhafksdjhfkjhkshdfsdfdfdfsdfsssssss", 10);
    cout << r << endl;

    r = sol.countKSubsequencesWithMaxBeauty("abcd", 2);
    cout << r << endl;

    r = sol.countKSubsequencesWithMaxBeauty("abbcd", 4);
    cout << r << endl;

    r = sol.countKSubsequencesWithMaxBeauty("bcca", 2);
    cout << r << endl;
}
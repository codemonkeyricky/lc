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
    bool ver(vector<vector<char>> &b, int i, int j, string &w, int k)
    {
        int m = b.size(); 
        int n = b[0].size();
        if (k == 0 && i && b[i - 1][j] != '#')
            return false;

        if (k >= w.size())
            return i >= m ? true : b[i][j] == '#';

        if (i >= m || j >= n)
            return false;

        if (b[i][j] == w[k] || b[i][j] == ' ')
            return ver(b, i + 1, j, w, k + 1);
        
        return false;
    }

    bool hor(vector<vector<char>> &b, int i, int j, string &w, int k)
    {
        int m = b.size(); 
        int n = b[0].size();
        if (k == 0 && j && b[i][j - 1] != '#')
            return false;

        if (k >= w.size())
            return j >= n ? true : b[i][j] == '#';

        if (i >= m || j >= n)
            return false;

        if (b[i][j] == w[k] || b[i][j] == ' ')
            return hor(b, i, j + 1, w, k + 1);
        
        return false;
    }

public:
    bool placeWordInCrossword(vector<vector<char>> &b, string w)
    {
        int m = b.size(); 
        int n = b[0].size();
        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < n; ++j)
            {
                if (ver(b, i, j, w, 0))
                    return true;
                if (hor(b, i, j, w, 0))
                    return true;
            }

        reverse(begin(w), end(w));
        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < n; ++j)
            {
                if (ver(b, i, j, w, 0))
                    return true;
                if (hor(b, i, j, w, 0))
                    return true;
            }

        return false;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.placeWordInCrossword(vector<vector<char>>() = {
                                     {' ', 'c', 'z'}}, 
                                 "cz");
    cout << r << endl;


    r = sol.placeWordInCrossword(vector<vector<char>>() = {
                                     {' ', ' ', '#'},
                                     {' ', ' ', '#'},
                                     {' ', ' ', 'c'}},
                                 "ca");
    cout << r << endl;

    r = sol.placeWordInCrossword(vector<vector<char>>() = {
                                     {' ', '#', 'a'},
                                     {' ', '#', 'c'},
                                     {' ', '#', 'a'}},
                                 "ac");
    cout << r << endl;

    r = sol.placeWordInCrossword(vector<vector<char>>() = {
                                     {'#', ' ', '#'},
                                     {' ', ' ', '#'},
                                     {'#', 'c', ' '}},
                                 "abc");
    cout << r << endl;
}
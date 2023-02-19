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
    bool validTicTacToe(vector<string> &board)
    {
        int x = 0, o = 0;
        for (auto i = 0; i < 3; ++i)
            for (auto j = 0; j < 3; ++j)
                if (board[i][j] == 'O')
                    ++o;
                else if (board[i][j] == 'X')
                    ++x;

        if (x - o < 0 || x - o > 1)
            return false;

        int winner[2] = {};
        for (auto k = 0; k < 2; ++k)
        {
            int rows[3] = {}, cols[3] = {};
            unordered_map<int, int> diag, adiag;
            for (auto i = 0; i < 3; ++i)
                for (auto j = 0; j < 3; ++j)
                    if (board[i][j] == (k == 0 ? 'X' : 'O'))
                        ++rows[i], ++cols[j], ++diag[i + j], ++adiag[i - j];

            for (auto i = 0; i < 3; ++i)
                if (rows[i] == 3 || cols[i] == 3)
                    ++winner[k];

            for (auto &d : diag)
                if (d.second == 3)
                    ++winner[k];

            for (auto &d : adiag)
                if (d.second == 3)
                    ++winner[k];
        }

        if (winner[0] && winner[1])
            return false;

        if (winner[0] && x - o == 0)
            return false;

        if (winner[1] && x - o > 0)
            return false;

        return true; 
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}
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
    bool checkMove(vector<vector<char>> &board, int rMove, int cMove, char color)
    {
        int m = board.size(), n = board[0].size();

        {
            if (rMove + 2 < m && board[rMove + 1][cMove] == ((color == 'B') ? 'W' : 'B'))
                for (int i = rMove + 1; i < m; ++i)
                    if (board[i][cMove] == color)
                        return true;
                    else if (board[i][cMove] == '.')
                        break;

            if (rMove - 2 >= 0 && board[rMove - 1][cMove] == ((color == 'B') ? 'W' : 'B'))
                for (int i = rMove - 2; i >= 0; --i)
                    if (board[i][cMove] == color)
                        return true;
                    else if (board[i][cMove] == '.')
                        break;

            if (cMove + 2 < n && board[rMove][cMove + 1] == ((color == 'B') ? 'W' : 'B'))
                for (int j = cMove + 2; j < n; ++j)
                    if (board[rMove][j] == color)
                        return true;
                    else if (board[rMove][j] == '.')
                        break;

            if (cMove - 2 >= 0 && board[rMove][cMove - 1] == ((color == 'B') ? 'W' : 'B'))
                for (int j = cMove - 2; j >= 0; --j)
                    if (board[rMove][j] == color)
                        return true;
                    else if (board[rMove][j] == '.')
                        break;
        }

        {
            if (rMove + 2 < m && cMove + 2 < n && board[rMove + 1][cMove + 1] == ((color == 'B') ? 'W' : 'B'))
                for (int i = rMove + 1, j = cMove + 1; i < m && j < n; ++i, ++j)
                    if (board[i][j] == color)
                        return true;
                    else if (board[i][j] == '.')
                        break;

            if (rMove + 2 < m && cMove - 2 >= 0 && board[rMove + 1][cMove - 1] == ((color == 'B') ? 'W' : 'B'))
                for (int i = rMove + 2, j = cMove - 2; i < m && j >= 0; ++i, --j)
                    if (board[i][j] == color)
                        return true;
                    else if (board[i][j] == '.')
                        break;

            if (rMove - 2 >= 0 && cMove + 2 < n && board[rMove - 1][cMove + 1] == ((color == 'B') ? 'W' : 'B'))
                for (int i = rMove - 2, j = cMove + 2; i >= 0 && j < n; --i, ++j)
                    if (board[i][j] == color)
                        return true;
                    else if (board[i][j] == '.')
                        break;

            if (rMove - 2 >= 0 && cMove - 2 >= 0 && board[rMove - 1][cMove - 1] == ((color == 'B') ? 'W' : 'B'))
                for (int i = rMove - 2, j = cMove - 2; i >= 0 && j >= 0; --i, --j)
                    if (board[i][j] == color)
                        return true;
                    else if (board[i][j] == '.')
                        break;
        }

        return false;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.checkMove(vector<vector<char>>() = {{'.','.','.','.','W','B','B','B'},{'.','.','.','.','.','.','.','B'},{'W','.','.','W','.','.','W','.'},{'B','.','B','B','B','.','.','W'},{'W','.','.','B','W','B','B','.'},{'W','B','.','.','W','B','B','.'},{'.','W','B','B','W','B','.','W'},{'B','.','W','B','W','.','W','.'}}, 0, 0, 'B');
    cout << r << endl;

    vector<vector<char>> board = {{'.', '.', '.', '.', '.', '.', '.', '.'}, {'.', 'B', '.', '.', 'W', '.', '.', '.'}, {'.', '.', 'W', '.', '.', '.', '.', '.'}, {'.', '.', '.', 'W', 'B', '.', '.', '.'}, {'.', '.', '.', '.', '.', '.', '.', '.'}, {'.', '.', '.', '.', 'B', 'W', '.', '.'}, {'.', '.', '.', '.', '.', '.', 'W', '.'}, {'.', '.', '.', '.', '.', '.', '.', 'B'}};
    r = sol.checkMove(board, 4, 4, 'W');
    cout << r << endl;
}
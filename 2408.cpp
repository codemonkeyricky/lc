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

class SQL
{
    unordered_map<string, vector<vector<string>>> tables;

public:
    SQL(vector<string> &names, vector<int> &columns)
    {
    }

    void insertRow(string name, vector<string> row)
    {
        tables[name].push_back(row);
    }

    void deleteRow(string name, int rowId)
    {
        tables[name][rowId - 1].clear();
    }

    string selectCell(string name, int rowId, int columnId)
    {
        return tables[name][rowId - 1][columnId - 1];
    }
};

/**
 * Your SQL object will be instantiated and called as such:
 * SQL* obj = new SQL(names, columns);
 * obj->insertRow(name,row);
 * obj->deleteRow(name,rowId);
 * string param_3 = obj->selectCell(name,rowId,columnId);
 */

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}
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

class FileSharing
{
    priority_queue<int> free;
    int last = 1;
    vector<set<int>> chunks;              ///< chunks -> list of user
    unordered_map<int, vector<int>> user; ///< user -> list of chunks

public:
    FileSharing(int m)
    {
        chunks = vector<set<int>>(m + 1);
    }

    int join(vector<int> ownedChunks)
    {
        int rv = -1;
        if (free.size())
            rv = -free.top(), free.pop();
        else
            rv = last++;

        for (auto &chunk : ownedChunks)
        {
            user[rv].push_back(chunk);
            chunks[chunk].insert(rv);
        }

        return rv;
    }

    void leave(int userID)
    {
        for (auto &chunk : user[userID])
            chunks[chunk].erase(userID);
        user.erase(userID);
        free.push(-userID);
    }

    vector<int> request(int userID, int chunkID)
    {
        user[userID].push_back(chunkID);
        if (chunks[chunkID].empty())
            return {};

        vector<int> rv(begin(chunks[chunkID]), end(chunks[chunkID]));
        chunks[chunkID].insert(userID);
        return rv;
    }
};

/**
 * Your FileSharing object will be instantiated and called as such:
 * FileSharing* obj = new FileSharing(m);
 * int param_1 = obj->join(ownedChunks);
 * obj->leave(userID);
 * vector<int> param_3 = obj->request(userID,chunkID);
 */

int main()
{
    FileSharing fs(9);
    cout << fs.join(vector<int>() = {9, 1, 8, 2, 4, 5, 7, 3, 6}) << endl;
    cout << fs.join(vector<int>() = {7, 8, 9}) << endl;
    cout << fs.join(vector<int>() = {7, 8, 3, 9, 5, 1, 2, 4, 6}) << endl;
    cout << fs.join(vector<int>() = {2, 9}) << endl;
    cout << fs.join(vector<int>() = {}) << endl;
    fs.request(2, 7);
    fs.request(2, 7);
}
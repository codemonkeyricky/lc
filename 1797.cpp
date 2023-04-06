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

class AuthenticationManager
{
    int ttl;
    deque<pair<int, string>> queue;
    unordered_map<string, int> timestamp;

    void retire(int time)
    {
        while (queue.size() && queue.front().first <= time)
        {
            if (timestamp[queue.front().second] <= time)
                timestamp.erase(queue.front().second);
            queue.pop_front();
        }
    }

public:
    AuthenticationManager(int timeToLive) : ttl(timeToLive)
    {
    }

    void generate(string tokenId, int currentTime)
    {
        retire(currentTime);
        queue.push_back({currentTime + ttl, tokenId});
        timestamp[tokenId] = currentTime + ttl;
    }

    void renew(string tokenId, int currentTime)
    {
        retire(currentTime);
        if (timestamp.count(tokenId))
            generate(tokenId, currentTime);
    }

    int countUnexpiredTokens(int currentTime)
    {
        retire(currentTime);
        return timestamp.size();
    }
};

/**
 * Your AuthenticationManager object will be instantiated and called as such:
 * AuthenticationManager* obj = new AuthenticationManager(timeToLive);
 * obj->generate(tokenId,currentTime);
 * obj->renew(tokenId,currentTime);
 * int param_3 = obj->countUnexpiredTokens(currentTime);
 */

int main()
{
    // [[13],["ajvy",1],[3],[4],["fuzxq",5],["izmry",7],["puv",12],["ybiqb",13],["gm",14],[15],[18],[19],["ybiqb",21],[23],[25],[26],["aqdm",28],[29],["puv",30]]

    AuthenticationManager am(13);
    am.renew("ajvy", 1);
    cout << am.countUnexpiredTokens(3) << endl; 
    cout << am.countUnexpiredTokens(4) << endl; 
    am.generate("fuzxq", 5);
    am.generate("izmry", 7);
    am.renew("puv", 12);
    am.generate("ybiqb", 13);
    am.generate("gm", 14);
    cout << am.countUnexpiredTokens(15) << endl; 
    cout << am.countUnexpiredTokens(18) << endl; 
    cout << am.countUnexpiredTokens(19) << endl; 
    am.renew("ybiqb", 21);
    cout << am.countUnexpiredTokens(23) << endl; 
    cout << am.countUnexpiredTokens(25) << endl; 
    cout << am.countUnexpiredTokens(26) << endl; 
    am.generate("aqdm", 28);
    cout << am.countUnexpiredTokens(29) << endl; 
    am.renew("puv", 30);
}
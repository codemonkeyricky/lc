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

class TopVotedCandidate
{
    map<int, int> winner; ///< winner at time
public:
    TopVotedCandidate(vector<int> &persons, vector<int> &times)
    {
        int n = persons.size();

        map<int,int> voting;
        for (auto i = 0; i < n; ++i)
            voting[times[i]] = persons[i];

        map<int, unordered_multiset<int>> votes; ///< votes
        unordered_map<int, int> latest;          ///< votes to latest
        map<int, int> candidate;                 ///< how many votes each candidate have
        for (auto &v : voting)
        {
            auto time = v.first;
            auto vote_for = v.second;
            if (candidate.count(vote_for))
            {
                int received_so_far = candidate[vote_for];
                votes[received_so_far].erase(vote_for);
            }

            votes[--candidate[vote_for]].insert(vote_for);
            latest[candidate[vote_for]] = vote_for;

            winner[time] = latest[begin(votes)->first];
        }
    }

    int q(int t)
    {
        auto it = winner.upper_bound(t);
        if (it == begin(winner))
            return -1;
        return prev(it)->second;
    }
};

/**
 * Your TopVotedCandidate object will be instantiated and called as such:
 * TopVotedCandidate* obj = new TopVotedCandidate(persons, times);
 * int param_1 = obj->q(t);
 */

int main()
{
    {
        vector<int> p = {0, 0, 0, 0, 1};
        vector<int> t = {0, 6, 39, 52, 75};
        TopVotedCandidate top(p, t);
        cout << top.q(99) << endl; 
        cout << top.q(78) << endl; 
    }

    {
        vector<int> p = {0, 1, 1, 0, 0, 1, 0};
        vector<int> t = {0, 5, 10, 15, 20, 25, 30};
        TopVotedCandidate top(p, t);
    }
}
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

class TweetCounts
{
    unordered_map<string, multiset<int>> tweets;

public:
    TweetCounts()
    {
    }

    void recordTweet(string tweetName, int time)
    {
        tweets[tweetName].insert(time);
    }

    vector<int> getTweetCountsPerFrequency(string freq, string tweetName, int startTime, int endTime)
    {
        int f;
        if (freq == "minute")
            f = 60;
        else if (freq == "hour")
            f = 3600;
        else if (freq == "day")
            f = 86400;
        vector<int> rv((endTime - startTime + f ) / f);
        int curr = 0, ticks = 0;
        for (auto it = lower_bound(begin(tweets[tweetName]), end(tweets[tweetName]), startTime);
             it != end(tweets[tweetName]) && *it <= endTime;
             ++it)
            ++rv[((*it - startTime)) / f];

        return rv;
    }
};

/**
 * Your TweetCounts object will be instantiated and called as such:
 * TweetCounts* obj = new TweetCounts();
 * obj->recordTweet(tweetName,time);
 * vector<int> param_2 = obj->getTweetCountsPerFrequency(freq,tweetName,startTime,endTime);
 */

int main()
{
    TweetCounts tc;

et3",10],["tweet3",10],["minute","tweet3",0,59],["minute","tweet3",0,60],["tweet3",120],["hour","tweet3",0,210]]

tc.recordTweet("tweet3",0);
tc.recordTweet("tweet3",60);
tc.recordTweet("tweet3",10);

    // tc.recordTweet("tweet0", 13);
    // tc.recordTweet("tweet1", 16);
    // tc.recordTweet("tweet2", 12);
    // tc.recordTweet("tweet3", 18);
    // tc.recordTweet("tweet4", 82);
    // tc.recordTweet("tweet3", 89);
    // tc.getTweetCountsPerFrequency("hour", "tweet3", 13, 4024);
}
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

class VideoSharingPlatform
{
    unordered_map<int, string> videos;
    unordered_map<int, array<int, 2>> likes;
    unordered_map<int, int> views;
    priority_queue<int, vector<int>, greater<int>> q;

public:
    VideoSharingPlatform()
    {
        for (auto i = 0; i <= 1e5; ++i)
            q.push(i);
    }

    int upload(string video)
    {
        int id = q.top();
        q.pop();
        videos[id] = video;
        return id;
    }

    void remove(int id)
    {
        if (videos.count(id))
        {
            videos.erase(id);
            likes.erase(id);
            views.erase(id);
            q.push(id);
        }
    }

    string watch(int id, int startMinute, int endMinute)
    {
        if (videos.count(id))
        {
            ++views[id];
            return videos[id].substr(startMinute, endMinute - startMinute + 1);
        }
        return "-1";
    }

    void like(int id)
    {
        if (videos.count(id))
            ++likes[id][0];
    }

    void dislike(int id)
    {
        if (videos.count(id))
            ++likes[id][1];
    }

    vector<int> getLikesAndDislikes(int id)
    {
        if (videos.count(id))
            return {likes[id][0], likes[id][1]};
        return {-1};
    }

    int getViews(int id)
    {
        if (videos.count(id))
            return views[id];
        return -1;
    }
};

/**
 * Your VideoSharingPlatform object will be instantiated and called as such:
 * VideoSharingPlatform* obj = new VideoSharingPlatform();
 * int param_1 = obj->upload(video);
 * obj->remove(videoId);
 * string param_3 = obj->watch(videoId,startMinute,endMinute);
 * obj->like(videoId);
 * obj->dislike(videoId);
 * vector<int> param_6 = obj->getLikesAndDislikes(videoId);
 * int param_7 = obj->getViews(videoId);
 */

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}
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

class TodoList
{
    unordered_map<int, pair<int, string>> tasks;    // taskId, [id, description]
    int index = 1;

    unordered_map<int, unordered_map<string, set<array<int, 2>>>> users;
    ///< user, tags, task, timestamp

public:
    TodoList()
    {
    }

    int addTask(int id, string taskDescription, int dueDate, vector<string> tags)
    {
        auto k = index++;
        tasks[k] = {id, taskDescription};
        for (auto &tag : tags)
            users[id][tag].insert({dueDate, k});
        users[id]["#"].insert({dueDate, k});
        return k;
    }

    vector<string> getAllTasks(int id)
    {
        return getTasksForTag(id, "#");
    }

    vector<string> getTasksForTag(int userId, string tag)
    {
        vector<string> rv;
        for (auto it = begin(users[userId][tag]); it != end(users[userId][tag]);)
        {
            if (!tasks.count((*it)[1]))
                users[userId][tag].erase(it++);
            else
                rv.push_back(tasks[(*it)[1]].second), ++it;
        }
        return rv;
    }

    void completeTask(int userId, int taskId)
    {
        if (tasks.count(taskId) && tasks[taskId].first == userId)
            tasks.erase(taskId);
    }
};

/**
 * Your TodoList object will be instantiated and called as such:
 * TodoList* obj = new TodoList();
 * int param_1 = obj->addTask(userId,taskDescription,dueDate,tags);
 * vector<string> param_2 = obj->getAllTasks(userId);
 * vector<string> param_3 = obj->getTasksForTag(userId,tag);
 * obj->completeTask(userId,taskId);
 */

int main()
{
    {
        TodoList todos;
        todos.addTask(46, "Xj3k0zuC2FLoJRe30h5sjRYrhD2bUxsPYnkaEdaxFVOZ3wjGS", 74, vector<string>() = {"7j5Zc2jTQkuR5SeQC4s", "YyxY40NWmp6Cm", "Hhake33MDbwQoUitta", "gjKR", "cGNqeMitvuYIcK"});
        todos.completeTask(46, 1);
        todos.completeTask(46, 1);
        todos.getAllTasks(46);
    }

    {
        TodoList todos;
        cout << todos.addTask(1, "Task1", 50, vector<string>() = {}) << endl;
        cout << todos.addTask(1, "Task2", 100, vector<string>() = {"P1"}) << endl;
        todos.getAllTasks(1);
        todos.getAllTasks(5);
        cout << todos.addTask(1, "Task3", 30, vector<string>() = {"P1"}) << endl;
        todos.getTasksForTag(1, "P1");
        todos.completeTask(5, 1);
        todos.completeTask(1, 2);
        todos.getTasksForTag(1, "P1");
        todos.getAllTasks(1);
    }
}
class Solution
{
    void add(int n, int l, int r, int i, int j)
    {
        if (lazy[n])
        {
            // node is within invert range
            tree[n] = (r - l + 1) - tree[n];

            // every node below need to be inverted because already in range.
            if (l != r)
            {
                lazy[n * 2] = !lazy[n * 2];
                lazy[n * 2 + 1] = !lazy[n * 2 + 1];
            }

            lazy[n] = 0;
        }

        // case 1: skip if region not of interest
        if (j < l || i > r)
            return;

        // case 2: in range
        if (i <= l && r <= j)
        {
            // node is within invert range
            tree[n] = (r - l + 1) - tree[n];

            // every node below need to be inverted because already in range.
            if (l != r)
            {
                lazy[n * 2] = !lazy[n * 2];
                lazy[n * 2 + 1] = !lazy[n * 2 + 1];
            }

            return;
        }

        // case 3:
        int m = (l + r) / 2;

        add(n * 2, l, m, i, j);
        add(n * 2 + 1, m + 1, r, i, j);

        tree[n] = tree[n * 2] + tree[n * 2 + 1];
    }

    int query(int n, int l, int r, int i, int j)
    {
        if (lazy[n])
        {
            // node is within invert range
            tree[n] = (r - l + 1) - tree[n];

            // every node below need to be inverted because already in range.
            if (l != r)
            {
                lazy[n * 2] = !lazy[n * 2];
                lazy[n * 2 + 1] = !lazy[n * 2 + 1];
            }

            lazy[n] = 0;
        }

        if (j < l || i > r)
            return 0 ;

        // node in range
        if (i <= l && r <= j)
            return tree[n];

        // case 3
        int m = (l + r) / 2;
        int p1 = query(n * 2, l, m, i, j);
        int p2 = query(n * 2 + 1, m + 1, r, i, j);
        return p1 + p2;
    }

    vector<int> tree, lazy;

public:
    vector<long long> handleQuery(vector<int> &n1, vector<int> &n2, vector<vector<int>> &queries)
    {
        int n = n1.size();
        tree = vector<int>(n * 3);
        lazy = vector<int>(n * 3);

        for (auto i = 0; i < n; ++i)
            if (n1[i])
                add(1, 0, n - 1, i, i);

        long long sum = accumulate(begin(n2), end(n2), 0ll);
        vector<long long> rv; 
        for (auto &q : queries)
        {
            int type = q[0], l = q[1], r = q[2];
            if (type == 1)
                add(1, 0, n - 1, l, r);
            else if (type == 2)
            {
                long long = query(1, 0, n - 1, 0, n - 1);
                sum += l * ones; 
            }
            else
                rv.push_back(sum);
        }
        return rv; 
    }
};


class Solution 
{
    vector<int> tree, lazy;

    void push(int v)
    {
        tree[v * 2] += lazy[v];
        lazy[v * 2] += lazy[v];
        tree[v * 2 + 1] += lazy[v];
        lazy[v * 2 + 1] += lazy[v];
        lazy[v] = 0;
    }

    void update(int v, int tl, int tr, int l, int r, int addend)
    {
        if (l > r)
            return;
        if (l == tl && tr == r)
        {
            tree[v] += addend;
            lazy[v] += addend;
        }
        else
        {
            push(v);
            int tm = (tl + tr) / 2;
            update(v * 2, tl, tm, l, min(r, tm), addend);
            update(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, addend);
            tree[v] = min(tree[v * 2], tree[v * 2 + 1]);
        }
    }

    int query(int v, int tl, int tr, int l, int r)
    {
        if (l > r)
            return 1e9;
        if (l == tl && tr == r)
            return tree[v];
        push(v);
        int tm = (tl + tr) / 2;
        return min(query(v * 2, tl, tm, l, min(r, tm)),
                   query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
    }

public:
    int maxIncreasingGroups(vector<int> &usage)
    {
        int n = usage.size();
        sort(begin(usage), end(usage), greater<int>());

        tree = vector<int>(n * 4);
        lazy = vector<int>(n * 4);

        for (auto i = 0; i < n; ++i)
            update(1, 0, n - 1, i, i, usage[i]);

        int limit = usage.back(), rv = 0;
        for (auto k = 1, i = 0; k <= n; ++k, ++rv)
        {
            int mmin = 1e9;
            while (i + k - 1 < n && (mmin = query(1, 0, n - 1, i, i + k - 1)) == 0)
                ++i;
            if (mmin == 0)
                break;
            update(1, 0, n - 1, i, i + k - 1, -1);
        }
        return rv;
    }
};

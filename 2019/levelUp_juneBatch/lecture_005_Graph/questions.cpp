#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

//Leetcode 200.=========================================================================
vector<vector<int>> dir{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
void numIslands_(vector<vector<char>> &grid, int sr, int sc)
{
    grid[sr][sc] = 0;
    for (int d = 0; d < 4; d++)
    {
        int r = sr + dir[d][0];
        int c = sc + dir[d][1];

        if (r >= 0 && c >= 0 && r < grid.size() && c < grid[0].size() && grid[r][c] == '1')
            numIslands_(grid, r, c);
    }
}

int numIslands(vector<vector<char>> &grid)
{
    if (grid.size() == 0 || grid[0].size() == 0)
        return 0;
    int count = 0;
    for (int i = 0; i < grid.size(); i++)
        for (int j = 0; j < grid[0].size(); j++)
        {
            if (grid[i][j] == '1')
            {
                count++;
                numIslands_(grid, i, j);
            }
        }

    return count;
}

//Leetcode 695
int maxAreaOfIsland_(vector<vector<int>> &grid, int sr, int sc)
{
    grid[sr][sc] = 0;
    int count = 0;
    for (int d = 0; d < 4; d++)
    {
        int r = sr + dir[d][0];
        int c = sc + dir[d][1];

        if (r >= 0 && c >= 0 && r < grid.size() && c < grid[0].size() && grid[r][c] == 1)
            count += maxAreaOfIsland_(grid, r, c);
    }
    return count + 1;
}

int maxAreaOfIsland(vector<vector<int>> &grid)
{
    if (grid.size() == 0 || grid[0].size() == 0)
        return 0;
    int maxArea = 0;
    for (int i = 0; i < grid.size(); i++)
        for (int j = 0; j < grid[0].size(); j++)
        {
            if (grid[i][j] == 1)
            {
                maxArea = max(maxArea, maxAreaOfIsland_(grid, i, j));
            }
        }

    return maxArea;
}

//Leetcode 463
int islandPerimeter(vector<vector<int>> &grid)
{
    int count = 0;
    int nbrs = 0;
    for (int i = 0; i < grid.size(); i++)
        for (int j = 0; j < grid[0].size(); j++)
        {
            if (grid[i][j] == 1)
            {
                count++;
                for (int d = 0; d < 4; d++)
                {
                    int r = i + dir[d][0];
                    int c = j + dir[d][1];

                    if (r >= 0 && c >= 0 && r < grid.size() && c < grid[0].size() && grid[r][c] == 1)
                        nbrs++;
                }
            }
        }

    return 4 * count - nbrs;
}

//Leetcode 130.

void solve_(vector<vector<char>> &grid, int sr, int sc)
{

    grid[sr][sc] = '#';
    for (int d = 0; d < 4; d++)
    {
        int r = sr + dir[d][0];
        int c = sc + dir[d][1];

        if (r >= 0 && c >= 0 && r < grid.size() && c < grid[0].size() && grid[r][c] == 'O')
            solve_(grid, r, c);
    }
}

void solve(vector<vector<char>> &grid)
{
    if (grid.size() == 0 || grid[0].size() == 0)
        return;
    int n = grid.size();
    int m = grid[0].size();

    for (int i = 0; i < grid.size(); i++)
    {
        if (grid[i][0] == 'O')
            solve_(grid, i, 0);
        if (grid[i][m - 1] == 'O')
            solve_(grid, i, m - 1);
    }

    for (int i = 0; i < grid[0].size(); i++)
    {
        if (grid[0][i] == 'O')
            solve_(grid, 0, i);
        if (grid[n - 1][i] == 'O')
            solve_(grid, n - 1, i);
    }

    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[0].size(); j++)
        {
            if (grid[i][j] == 'O')
                grid[i][j] = 'X';
            else if (grid[i][j] == '#')
                grid[i][j] = 'O';
        }
    }
}

//leetcode 785.
bool isBipartite(vector<vector<int>> &graph)
{
    int N = graph.size();
    vector<int> vis(N, -1);

    for (int i = 0; i < N; i++)
    {
        if (vis[i] == -1) // for my All components
        {

            queue<pair<int, int>> que;
            que.push({i, 0}); // vtx, color

            while (que.size() != 0)
            {
                int size = que.size();
                while (size-- > 0)
                {
                    pair<int, int> rvtx = que.front();
                    que.pop();

                    if (vis[rvtx.first] != -1) // cycle.
                    {
                        if (rvtx.second != vis[rvtx.first]) // conflict
                            return false;
                        continue;
                    }

                    vis[rvtx.first] = rvtx.second;
                    for (int e : graph[rvtx.first])
                    {
                        if (vis[e] == -1)
                            que.push({e, (rvtx.second + 1) % 2});
                    }
                }
            }
        }
    }
    return true;
}

//Leetcode 994

int orangesRotting(vector<vector<int>> &grid)
{
    int n = grid.size();
    int m = grid[0].size();

    queue<pair<int, int>> que;
    int Freshoranges = 0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (grid[i][j] == 2)
                que.push({i, j});
            else if (grid[i][j] == 1)
                Freshoranges++;

    if (Freshoranges == 0)
        return 0;

    vector<vector<int>> dirA{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    int time = 0;
    while (que.size() != 0)
    {
        int size = que.size();
        while (size-- > 0)
        {
            pair<int, int> rvtx = que.front();
            que.pop();

            for (int d = 0; d < 4; d++)
            {
                int r = rvtx.first + dirA[d][0];
                int c = rvtx.second + dirA[d][1];

                if (r >= 0 && c >= 0 && r < n && c < m && grid[r][c] == 1)
                {
                    grid[r][c] = 2;
                    que.push({r, c});
                    Freshoranges--;
                }
            }
        }
        time++;
    }

    return Freshoranges != 0 ? -1 : time - 1;
}

//Leetcode 1091
int shortestPathBinaryMatrix(vector<vector<int>> &grid)
{
    if (grid.size() == 0 || grid[0].size() == 0)
        return -1;
    int n = grid.size();
    int m = grid[0].size();

    if (grid[0][0] == 1 || grid[n - 1][m - 1] == 1)
        return -1;

    int dirA[8][2] = {{-1, -1}, {-1, 0}, {0, -1}, {-1, 1}, {1, -1}, {0, 1}, {1, 0}, {1, 1}};
    queue<int> que;
    que.push(0);

    int level = 1;
    while (que.size() != 0)
    {
        int size = que.size();
        while (size-- > 0)
        {
            int rvtx = que.front();
            que.pop();

            int R = (rvtx / m);
            int C = (rvtx % m);

            if (R == n - 1 && C == m - 1)
                return level;

            for (int d = 0; d < 8; d++)
            {
                int r = R + dirA[d][0];
                int c = C + dirA[d][1];

                if (r >= 0 && c >= 0 && r < n && c < m && grid[r][c] == 0)
                {
                    grid[r][c] = 1;
                    que.push((r * m + c));
                }
            }
        }
        level++;
    }

    return -1;
}

//Leetcode 207.

bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
{
    int N = numCourses;
    vector<vector<int>> graph(N, vector<int>());

    vector<int> indegree(N, 0);
    for (vector<int> &ar : prerequisites)
    {
        graph[ar[0]].push_back(ar[1]);
        indegree[ar[1]]++;
    }

    queue<int> que;
    int count = 0;
    for (int i = 0; i < N; i++)
        if (indegree[i] == 0)
            que.push(i);

    while (que.size() != 0)
    {
        int rvtx = que.front();
        que.pop();

        count++;
        for (int e : graph[rvtx])
        {
            if (--indegree[e] == 0)
                que.push(e);
        }
    }

    return count == N;
}

vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
{

    int N = numCourses;
    vector<vector<int>> graph(N, vector<int>());

    vector<int> indegree(N, 0);
    for (vector<int> &ar : prerequisites)
    {
        graph[ar[0]].push_back(ar[1]);
        indegree[ar[1]]++;
    }

    queue<int> que;
    vector<int> ans;
    for (int i = 0; i < N; i++)
        if (indegree[i] == 0)
            que.push(i);

    while (que.size() != 0)
    {
        int rvtx = que.front();
        que.pop();

        ans.push_back(rvtx);
        for (int e : graph[rvtx])
        {
            if (--indegree[e] == 0)
                que.push(e);
        }
    }
    if (ans.size() != N)
        ans.clear();
    reverse(ans.begin(), ans.end());
    return ans;
}
//===============================================================================

bool topoCycle(int src, vector<vector<int>> &graph, vector<bool> &vis, vector<bool> &myPath, vector<int> &ans)
{
    vis[src] = myPath[src] = true;
    bool isCycle = false;
    for (int e : graph[src])
    {
        if (!vis[e])
            isCycle = isCycle || topoCycle(e, graph, vis, myPath, ans);
        else if (myPath[e])
            return true;
    }

    myPath[src] = false;
    ans.push_back(src);
    return isCycle;
}

vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
{

    int N = numCourses;
    vector<vector<int>> graph(N, vector<int>());

    for (vector<int> &ar : prerequisites)
        graph[ar[0]].push_back(ar[1]);

    vector<bool> vis(N, false);
    vector<bool> myPath(N, false);
    vector<int> ans;

    bool isCycle = false;
    for (int i = 0; i < N; i++)
        if (!vis[i])
            isCycle = isCycle || topoCycle(i, graph, vis, myPath, ans);

    if (isCycle)
        ans.clear();

    return ans;
}

// Leetcode 329

int longestIncreasingPath(vector<vector<int>> &matrix)
{
    if (matrix.empty() || matrix[0].empty())
        return 0;

    int n = matrix.size();
    int m = matrix[0].size();

    int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    vector<vector<int>> indegree(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int d = 0; d < 4; d++)
            {
                int x = i + dir[d][0];
                int y = j + dir[d][1];

                if (x >= 0 && y >= 0 && x < n && y < m && matrix[x][y] > matrix[i][j])
                    indegree[x][y]++;
            }

    queue<pair<int, int>> que;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (indegree[i][j] == 0)
                que.push({i, j});

    int len = 0;
    while (que.size() != 0)
    {
        int size = que.size();
        while (size-- > 0)
        {
            pair<int, int> rvtx = que.front();
            que.pop();

            for (int d = 0; d < 4; d++)
            {
                int x = rvtx.first + dir[d][0];
                int y = rvtx.second + dir[d][1];

                if (x >= 0 && y >= 0 && x < n && y < m && matrix[x][y] > matrix[rvtx.first][rvtx.second] && --indegree[x][y] == 0)
                    que.push({x, y});
            }
        }
        len++;
    }

    return len == 0 ? -1 : len;
}

#include "planning.h"
#include <cmath>
#include <vector>

using namespace std;

Planner::Planner(const vector<vector<bool>> &grid) : grid(grid) {
  rows = grid.size();
  cols = grid[0].size();
}

bool Planner::isvalid(int x, int y) const {
  return (x >= 0 && x < rows && y >= 0 && y < cols && !grid[x][y]);
}

double Planner::heuristic(int x1, int y1, int x2, int y2) const {
  return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

vector<pair<int, int>> Planner::pathplanning(pair<int, int> start,
                                             pair<int, int> goal) {
  vector<pair<int, int>> path; // store final path 
			       
  int dx[4] = {1, -1, 0, 0};
  int dy[4] = {0, 0, 1, -1};

  // Cost maps
  vector<vector<double>> g(rows, vector<double>(cols, 1e9));
  vector<vector<pair<int,int>>> parent(rows, vector<pair<int,int>>(cols, {-1,-1}));

  // Min-heap: {f-score, {x,y}}
  priority_queue<
      pair<double, pair<int,int>>,
      vector<pair<double, pair<int,int>>>,
      greater<pair<double, pair<int,int>>> > pq;

  g[start.first][start.second] = 0.0;
  pq.push({heuristic(start.first, start.second, goal.first, goal.second), start});

  while (!pq.empty()) {
      auto curr = pq.top(); pq.pop();
      int x = curr.second.first;
      int y = curr.second.second;

      if (x == goal.first && y == goal.second) {
          // reconstruct path
          pair<int,int> node = goal;
          while (!(node.first == start.first && node.second == start.second)) {
              path.push_back(node);
              node = parent[node.first][node.second];
          }
          path.push_back(start);
          reverse(path.begin(), path.end());
          return path;
      }

      for (int i=0; i<4; i++) {
          int nx = x + dx[i];
          int ny = y + dy[i];

          if (!isvalid(nx, ny)) continue;

          double newCost = g[x][y] + 1.0; // cost per move
          if (newCost < g[nx][ny]) {
              g[nx][ny] = newCost;
              parent[nx][ny] = {x,y};
              double f = newCost + heuristic(nx, ny, goal.first, goal.second);
              pq.push({f, {nx, ny}});
          }
      }
  }

  /* Implement Path Planning logic here */

  return path;
}

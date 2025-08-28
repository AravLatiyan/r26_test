#include "odometry.h"
#include <cmath>
#include <ctime>
#include <iterator>
#include <numeric>

using namespace std;

Odometry::Odometry(double wheel_radius, double rpm)
    : radius(wheel_radius), rpm(rpm) {
  // Linear velocity (m/s) =(wheel circumference * revolutions per second)
  double rps = rpm / 60.0;
  linear_vel = 2 * M_PI * radius * rps;
}

double Odometry::distance(int x1, int y1, int x2, int y2) {
  return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

double Odometry::angle(int x1, int y1, int x2, int y2) {
  // atan2 returns radians, convert to degrees
  return atan2(y2 - y1, x2 - x1) * 180.0 / M_PI;
}

MotionCommand Odometry::computeCommands(vector<pair<int, int>> &path) {

  MotionCommand res = {0.0, 0.0}; // store total time and angle traversed
  if (path.size() < 2) return res; // no motion

  double total_time = 0.0;
  double total_angle = 0.0;

  double prev_angle = 0.0;
  bool first = true;

  for (size_t i=1; i<path.size(); i++) {
      int x1 = path[i-1].first, y1 = path[i-1].second;
      int x2 = path[i].first, y2 = path[i].second;

      double dist = distance(x1,y1,x2,y2);
      double ang = angle(x1,y1,x2,y2);

      total_time += dist / linear_vel;

      if (!first) {
          double diff = fabs(ang - prev_angle);
          if (diff > 180.0) diff = 360.0 - diff;
          total_angle += diff;
      }
      prev_angle = ang;
      first = false;
  }

  res.time_sec = total_time;
  res.angle_deg = total_angle;
 /* Implement you odometry logic here */ 

  return res;
}

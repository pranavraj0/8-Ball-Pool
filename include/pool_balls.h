#pragma once

#include "vector"
#include "ball.h"

namespace pool {

using std::vector;

class PoolBalls {
 public:
  PoolBalls(const vector<Ball>& balls, const double& width,
            const double& height, const double& margin, const double& window_width,
            const double& window_length);

  /**
   * Takes racking position, and assigns position on table accordingly.
   * @param ball; ball to be assigned
   */
  void AssignPositionByRack(Ball& ball);

  //Getter
  vector<Ball> GetProcessed() const;
 private:
  //Balls processed by class
  vector<Ball> processed_;
  //Window width, length, and margin
  double width_;
  double length_;
  double margin_;
  double window_width_;
  double window_length_;
  //Number of balls
  int num_balls_;
  //Position of ball at in first row of rack
  vec2 top_rack_position_;
};

} //namespace pool
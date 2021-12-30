#pragma once

#include <glm/vec2.hpp>

#include "cinder/gl/gl.h"
#include "ball.h"

namespace pool {

using glm::vec2;


class BallDisplay {
 public:
  BallDisplay();
  
  BallDisplay(const vec2& first_ball_position, const int& num_balls, 
              const double& ball_radius);

  /**
   * Displays ball display;
   */
  void Display();
  
  /**
   * Updates ball display
   * @param ball 
   */
  void Update(const Ball& ball);
  
 private:
  //First position of ball
  vec2 first_position_;
  //Number of balls in display
  int num_balls_;
  double radius_;
  //Number of balls displayed
  int num_displayed_;
  //Scored balls
  vector<Ball> scored_;
};

} //namespace pool
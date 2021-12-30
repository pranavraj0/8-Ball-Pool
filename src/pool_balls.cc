#include "pool_balls.h"

#include <iostream>

namespace pool {

PoolBalls::PoolBalls(const vector<Ball>& balls,
                     const double& width, const double& height,
                     const double& margin, const double& window_width,
                     const double& window_length) {
  width_ = width;
  length_ = height;
  margin_ = margin;
  window_width_ = window_width;
  window_length_ = window_length;
  //Not including cue
  num_balls_ = balls.size() - 1;
  processed_ = balls;
  //Sets radius of all balls
  for (Ball& ball: processed_) {
    ball.SetRadius(margin_ / 5);
  }
  //Finds ball in front of rack and sets and saves position
  for (Ball& ball: processed_) {
    if (vec2(ball.GetXRack(), ball.GetYRack()) == vec2(0, 0)) {
      double x_distance_to_table = (window_width_ - width_) / 2;
      top_rack_position_ = vec2(x_distance_to_table + width_ - margin_ -
                                ((width_ - (2 * margin_)) / 4), window_length_ / 2);
      ball.SetPosition(vec2(x_distance_to_table + width_ - margin_ -
                            ((width_ - (2 * margin_)) / 4), window_length / 2));
    }
  }
  //Assigns position for every ball
  for (Ball& ball: processed_) {
    AssignPositionByRack(ball);
  }
}

void PoolBalls::AssignPositionByRack(Ball& ball) {
  //Finds height of center of rack, per each level of the rack
  double height_per_level = 2 * ball.GetRadius() / (2 * tan(M_PI / 6));
  //If ball is cue ball, sets location
  if (ball.IsCue()) {
    double x_distance_to_table = (window_width_ - width_) / 2;
    ball.SetPosition(vec2(x_distance_to_table + margin_ + (width_ - 2 * margin_) / 4, window_length_ / 2));
  } else {
    //Goes through each level of the rack
    for (int i = 1; i < num_balls_ / 3; i++) {
      //If level matches...
      if (i == ball.GetXRack()) {
        //If y of rack is 0, y is equal to y of top ball
        if (ball.GetYRack() == 0) {
          vec2 position(top_rack_position_.x + (i * height_per_level),
                        top_rack_position_.y);
          ball.SetPosition(position);
        } else {
          //If level has even index, has odd number of elements
          if (i % 2 == 0) {
            vec2 position(top_rack_position_.x + (i * height_per_level),
                          top_rack_position_.y + (ball.GetYRack() * 2 * ball.GetRadius()));
            ball.SetPosition(position);
          } else {
            //If level has odd index and has to move out more than one ball
            //If positive, adds
            if (ball.GetYRack() > 0) {
              vec2 position(top_rack_position_.x + (i * height_per_level),
                            top_rack_position_.y + (ball.GetRadius()) +
                            ((ball.GetYRack() - 1) * 2 * ball.GetRadius()));
              ball.SetPosition(position);
            } else {
              //If negative, subtracts
              vec2 position(top_rack_position_.x + (i * height_per_level),
                            top_rack_position_.y - (ball.GetRadius()) +
                            ((ball.GetYRack() + 1) * 2 * ball.GetRadius()));
              ball.SetPosition(position);
            }
          }
        }
      }
    }
  }
}

std::vector<pool::Ball> PoolBalls::GetProcessed() const {
  return processed_;
}

} //namespace pool

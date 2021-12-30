#include "cue.h"

using glm::vec2;

namespace pool {

pool::Cue::Cue() {
  width_ = 0;
  length_ = 0;
  current_angle_ = 0;
  velocity_ = {0, 0};
}

pool::Cue::Cue(const double& width, const double& length) {
  width_ = width;
  length_ = length;
  current_angle_ = 0;
  velocity_ = {0, 0};
}

void pool::Cue::Display() const {
  //Displays cue using lines
  ci::gl::color(ci::Color("orange"));
  ci::gl::drawLine(bottom_left_, bottom_right_);
  ci::gl::drawLine(top_left_, top_right_);
  ci::gl::drawLine(bottom_left_, top_left_);
  ci::gl::drawLine(bottom_right_, top_right_);
}

void pool::Cue::SetStartingPosition(const vec2& cue_position,
                                    const double& radius) {
  //Sets starting position behind cue ball
  bottom_right_ = vec2(cue_position.x - radius - 5, cue_position.y + (length_ / 2));
  top_right_ = vec2(bottom_right_.x, bottom_right_.y - length_);
  top_left_ = vec2(top_right_.x - width_, top_right_.y);
  bottom_left_ = vec2(bottom_right_.x - width_, bottom_right_.y);
}

void pool::Cue::SetPosition(const vec2& rotation_point, const double& angle) {
  //Sets position of each corner based on difference between current and given 
  //angle
  bottom_right_ = RotatePoint(bottom_right_, rotation_point, angle - current_angle_);
  top_left_ = RotatePoint(top_left_, rotation_point, angle - current_angle_);
  bottom_left_ = RotatePoint(bottom_left_, rotation_point, angle - current_angle_);
  top_right_ = RotatePoint(top_right_, rotation_point, angle - current_angle_);
  current_angle_ = angle;
}

vec2 pool::Cue::RotatePoint(vec2 point,
                            vec2 rotation_point,
                            const double& angle) {
  double sine = sin(angle);
  double cosine = cos(angle);
  //Translate point back to origin
  point.x -= rotation_point.x;
  point.y -= rotation_point.y;
  //Rotates point
  double x_new = point.x * cosine - point.y * sine;
  double y_new = point.x * sine + point.y * cosine;
  // Translate point back
  vec2 new_point = vec2(x_new + rotation_point.x, y_new + rotation_point.y);
  return new_point;
}

void pool::Cue::PullBack(const double& pixels) {
  //If not resetting cue, adds to velocity of the cue.
  if (pixels > 0) {
    velocity_ += vec2(pixels * cos(-current_angle_), pixels * sin(-current_angle_));
  }
  //Finds new coordinates after being pulled back
  bottom_right_ = FindNewCoordinatesWithAngle(bottom_right_, pixels);
  bottom_left_ = FindNewCoordinatesWithAngle(bottom_left_, pixels);
  top_right_ = FindNewCoordinatesWithAngle(top_right_, pixels);
  top_left_ = FindNewCoordinatesWithAngle(top_left_, pixels);
}

vec2 pool::Cue::FindNewCoordinatesWithAngle(const vec2& point, const double& pixels) const{
  //Uses opposite angle and some trig to find point to pull cue back to
  double angle = -current_angle_;
  double new_x = point.x - (pixels * sin((M_PI / 2) - angle));
  double new_y = point.y + (pixels * sin(angle));
  return vec2(new_x, new_y);
}


void pool::Cue::SetCuePositionWithAngle(const vec2& cue_position, const double& radius, const double& angle) {
  SetStartingPosition(cue_position, radius);
  //Resets angle so cue follows properly
  current_angle_ = 0;
}

//Getters and setters
void pool::Cue::SetVelocity(const vec2& to_set) {
  velocity_ = to_set;
}

double pool::Cue::GetXVelocity() const {
  return velocity_.x;
}

double pool::Cue::GetYVelocity() const {
  return velocity_.y;
}

} //namespace pool